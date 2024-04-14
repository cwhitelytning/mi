/**
 * @file dynamic_library.hpp
 * @brief Header file for the dynamic_library class in the mi namespace,
 *        providing an interface for handling dynamic library loading
 *        and symbol resolution.
 */

#ifndef MI_DYNAMIC_LIBRARY_HPP
#define MI_DYNAMIC_LIBRARY_HPP

#include "builtin.hpp"
#include "dynamic_library_error.hpp"
#include "exception.hpp"
#include "fs.hpp"
#include "noncopyable.hpp"
#include "nonmovable.hpp"
#include "os.hpp"

namespace mi::dl
{

/**
 * @class dynamic_library
 * @brief A class for loading dynamic libraries and resolving symbols.
 *
 * This class provides functionalities to load and unload dynamic libraries
 * and to resolve symbols to function pointers within these libraries.
 */
class dynamic_library : private mixin::noncopyable, private mixin::nonmovable
{
public:
    /**
     * @brief Get the path of the dynamic library.
     * @return The filesystem path to the dynamic library.
     */
    [[nodiscard]]
    const fs::path_t &
    path() const noexcept
    {
        return m_path;
    }

    /**
     * @brief Check if the library is unloaded.
     * @return `true` if the library is unloaded, `false` otherwise.
     */
    [[nodiscard]]
    virtual bool
    is_unloaded() const noexcept;

    /**
     * @brief Check if the library is loaded.
     * @return `true` if the library is loaded, `false` otherwise.
     */
    [[nodiscard]]
    virtual bool
    is_loaded() const noexcept;

    /**
     * @brief Loads a symbol from the dynamic library in an unsafe manner.
     *
     * This function retrieves a symbol address from the loaded dynamic library
     * using a platform-specific approach.
     *
     * On UNIX-like systems, it uses dlsym, while on Windows systems,
     * it employs GetProcAddress.
     *
     * As the method name suggests, this operation is considered unsafe
     * as it bypasses type safety, and it's up to the caller to ensure
     * that the usage of the symbol is correct.
     *
     * Care should be taken when using
     * this method due to the potential risks of runtime errors.
     *
     * @note This method is platform dependent.
     *
     *       On UNIX-like systems (including Linux and macOS),
     *       it relies on dlsym.
     *
     *       On Windows, it uses GetProcAddress.
     *
     * @param name The name of the symbol to load from the dynamic library.
     *             The symbol must exist in the library.
     *
     * @return Returns a pointer to the symbol if found;
     *         otherwise, returns nullptr.
     *
     *         The actual type of the symbol must be cast by the caller.
     *
     * @warning The method does not perform any type checking on the retrieved
     *          symbol. It is the caller's responsibility to ensure the correct
     *          type is used when casting the returned pointer.
     *
     * @see dynamic_library::load() for safely loading symbols with type safety.
     */
    [[nodiscard]]
    virtual os::dynamic_library_func_t
    sym_unsafe(std::string_view name) const;

    /**
     * @brief Retrieves a symbol from the dynamic library.
     *
     * @param name The name of the symbol to retrieve.
     * @return A function pointer to the symbol.
     *
     * @throw dynamic_library_error If the library is not loaded.
     */
    [[nodiscard]]
    os::dynamic_library_func_t
    sym(std::string_view name) const;

    /**
     * @brief Template method to resolve a symbol to a specific function type.
     *
     * @param name The name of the symbol to resolve.
     * @return Pointer to the resolved function cast to the specified type.
     *
     * @throw dynamic_library_error If the library is not loaded.
     */
    template <typename FunctionType>
    FunctionType *
    sym(std::string_view name) const
    {
        return (FunctionType *)sym(name.data());
    }

    /**
     * @brief Calls a function from the dynamic library by name.
     *
     * @param name The name of the function to call.
     * @param args Arguments to be passed to the function.
     * @return The result of invoking the function.
     *
     * @throw dynamic_library_error If the library is not loaded.
     * @throw dynamic_library_error If the function is not found.
     */
    template <typename FunctionType, typename... Args>
    std::invoke_result_t<FunctionType, Args...>
    call(std::string_view name, Args &&...args) const
    {
        if (auto func = sym<FunctionType>(name))
        {
            return std::invoke(*func, std::forward<Args>(args)...);
        }
        throw exception::dynamic_library_error("no function from dynamic library "
                                               "(function: {}, path: {})",
                                               name,
                                               m_path);
    }

    /**
     * @brief Loads the dynamic library into memory.
     *
     * Attempts to load the dynamic library file specified by the path set in
     * the dynamic_library instance. It checks for readability of the file,
     * correct file extension, and whether the library is already loaded.
     *
     * If any of these checks fail,
     * a dynamic_library_exception is thrown.
     *
     * @throws dynamic_library_exception if the file is not readable, has an invalid
     *                                   extension, or is already loaded.
     *
     * @note This method is platform-dependent and uses different APIs
     *       to load the library on UNIX-like systems and Windows.
     */
    virtual void
    load();

    /**
     * @brief Unloads the dynamic library from memory.
     *
     * Attempts to unload the dynamic library
     * that is currently loaded into memory.
     *
     * If the library is loaded, it uses platform-specific API to unload it.
     * If the unloading process fails, a dynamic_library_exception is thrown.
     *
     * @throws dynamic_library_exception if the library could not be unloaded.
     * @note This method is platform-dependent and uses dlclose on UNIX-like systems
     *       and FreeLibrary on Windows to unload the dynamic library.
     */
    virtual void
    unload();

    /**
     * @brief Construct a new dynamic library object.
     * @param path The filesystem path to the dynamic library.
     */
    explicit dynamic_library(fs::path_t path);

    /**
     * @brief Destroy the dynamic library object.
     *        Unloads the dynamic library if it is loaded.
     *
     * @throw dynamic_library_error if the library could not be unloaded.
     */
    ~dynamic_library() override;

private:
    fs::path_t                   m_path;
    os::dynamic_library_handle_t m_handle;
};

/**
 * @brief Retrieves the last error message
 *        depending on the operating system.
 *
 * @return The last error message as a Unicode string.
 */
std::string
last_error_message();

} // namespace mi::dl

#endif /* MI_DYNAMIC_LIBRARY_HPP */
