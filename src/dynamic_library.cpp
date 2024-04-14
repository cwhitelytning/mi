#include <mi/dynamic_library.hpp>

#ifdef MI_OS_UNIX_LIKE
#    include <dlfcn.h>
#    include <mi/str.hpp>
#endif

using namespace mi;
using namespace mi::dl;

bool
dynamic_library::is_unloaded() const noexcept
{
    return m_handle == nullptr;
}

bool
dynamic_library::is_loaded() const noexcept
{
    return !is_unloaded();
}

os::dynamic_library_func_t
dynamic_library::sym_unsafe(std::string_view name) const
{
#ifdef MI_OS_UNIX_LIKE
    return dlsym(m_handle, name.data());
#else
    return GetProcAddress(m_handle, name.data());
#endif
}

os::dynamic_library_func_t
dynamic_library::sym(std::string_view name) const
{
    if (is_unloaded())
    {
        throw dynamic_library_exception(
            "failed to get symbol, dynamic library is not loaded "
            "(symbol: {}, path: {})",
            name,
            m_path);
    }
    return sym_unsafe(name);
}

void
dynamic_library::load()
{
    if (!fs::is_readable(m_path))
    {
        throw dynamic_library_exception("no read access (path: {})", m_path);
    }
    else if (path().extension() != os::DYNAMIC_LIBRARY_EXTENSION)
    {
        throw dynamic_library_exception("invalid extension (path: {})", m_path);
    }
    else if (is_loaded())
    {
        throw dynamic_library_exception("already loaded (path: {})", m_path);
    }

#ifdef MI_OS_UNIX_LIKE
    m_handle = dlopen(m_path.c_str(), RTLD_LAZY);
#elif defined(MI_OS_WINDOWS)
    m_handle = LoadLibraryW(m_path.c_str());
#endif

    if (is_unloaded())
    {
        throw dynamic_library_exception(last_error_message());
    }
}

void
dynamic_library::unload()
{
    if (is_loaded())
    {
#ifdef MI_OS_UNIX_LIKE
        if (!dlclose(m_handle))
        {
#else
        if (FreeLibrary(m_handle))
        {
#endif
            m_handle = nullptr;
        }
    }

    if (is_loaded())
    {
        throw dynamic_library_exception(last_error_message());
    }
}

dynamic_library::dynamic_library(fs::path_t path)
    : m_path(std::move(path)),
      m_handle(nullptr)
{
}

dynamic_library::~dynamic_library()
{
    exception::invoke_noexcept(&dynamic_library::unload, this);
}

std::string
dl::last_error_message()
{
#ifdef MI_OS_WINDOWS
    return os::last_error_message();

#elif defined MI_OS_UNIX_LIKE
    return str::cstring_to_string(dlerror());
#endif
}