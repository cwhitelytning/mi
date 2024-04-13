#include <mi/os.hpp>

#if defined(MI_OS_UNIX_LIKE)
#    include <cstring>
#    include <mi/str.hpp>
#endif

using namespace mi;
using namespace mi::os;

error_code_t
os::last_error_code()
{
#ifdef MI_OS_WINDOWS
    return GetLastError();
#elif defined(MI_OS_UNIX_LIKE)
    return errno;
#endif
}

ustring
os::error_message(error_code_t code)
{
#ifdef MI_OS_WINDOWS
    ustring message;
    uchar  *buffer = nullptr;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                      FORMAT_MESSAGE_IGNORE_INSERTS,
                  nullptr,
                  code,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  reinterpret_cast<uchar *>(&buffer),
                  0,
                  nullptr);

    if (buffer)
    {
        message = buffer;
        LocalFree(buffer);
    }

    return message;
#elif defined(MI_OS_UNIX_LIKE)
    return cstring_to_string(std::strerror(code));
#endif
}

ustring
os::last_error_message()
{
    return error_message(last_error_code());
}

process_id_t
os::current_process_id()
{
#ifdef MI_OS_WINDOWS
    return GetCurrentProcessId();
#elif defined(MI_OS_UNIX_LIKE)
    return getpid();
#endif
}