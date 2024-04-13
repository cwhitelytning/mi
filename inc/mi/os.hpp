/**
 * @file os.hpp
 * @brief This file is part of the mi library, focusing on providing a unified
 *        interface for cross-platform OS-level operations.
 *
 * It serves as the foundation for building applications that require
 * interaction with the operating system in a way that is transparent to the
 * underlying platform.
 *
 * The aim is to enable developers to write code once and have it run on any
 * supported OS without requiring platform-specific conditionals or code paths.
 *
 * Initially, this file introduces abstractions for error handling
 * within the context of OS operations.
 *
 * However, it is designed to be expanded with further cross-platform
 * functionalities such as file system access, process management,
 * system information queries, and more, adhering to the principle
 * of platform independence.
 *
 * Components and functionalities encapsulated in this file will encompass:
 * - Type definitions and utilities that abstract away platform-specific types
 *   and constants (such as error codes).
 *
 * - Functions for retrieving OS-level information and performing common tasks
 *   in a way that does not expose the caller to the intricacies of the
 *   operating system.
 *
 * - Abstractions for more complex OS interactions that may vary significantly
 *   between platforms, with a focus on offering a common interface that aligns
 *   with idiomatic usage in C++.
 *
 * While initial versions may focus on error handling due to its ubiquitous need
 * across OS-level operations, future updates are expected to broaden the scope,
 * turning mi::os into a comprehensive toolset for cross-platform development.
 */

#ifndef MI_OS_HPP
#define MI_OS_HPP

#include "unicode.hpp"

#ifdef MI_OS_WINDOWS
#    include <windows.h>
#elif defined(MI_OS_UNIX_LIKE)
#    include <unistd.h>
#endif

namespace mi::os
{

#ifdef MI_OS_UNIX_LIKE

#    if defined MI_OS_LINUX
/**
 * @def dynamic_library_extension
 * @brief Defines the file extension for dynamic libraries on Linux.
 *
 * The .so (shared object) file format is the standard for dynamic libraries on
 * Linux. This extension is used when loading libraries at runtime using dlopen
 * or similar mechanisms.
 */
constexpr const auto DYNAMIC_LIBRARY_EXTENSION = ".so";
#    elif defined MI_OS_APPLE
/**
 * @def dynamic_library_extension
 * @brief Defines the file extension for dynamic libraries on macOS.
 *
 * macOS uses the .dylib (dynamic library) file format for its dynamic
 * libraries. This extension is used when loading libraries at runtime using
 * dlopen or similar mechanisms.
 */
constexpr const auto DYNAMIC_LIBRARY_EXTENSION = ".dylib";
#    endif

/**
 * @typedef error_code_t
 * @brief Represents error codes returned
 *        by dynamic library functions on Unix-like systems.
 *
 * This type is an alias for int. In Unix-like environments, dynamic
 * library-related functions, such as dlopen and dlerror,
 * use integers to represent error codes or statuses.
 */
using error_code_t = int;

/**
 * @typedef dynamic_library_handle_t
 * @brief Type definition for dynamic library handles in Unix-like systems.
 *
 * In Unix-like systems, dynamic library handles are represented using void *.
 */
typedef void *dynamic_library_handle_t;

/**
 * @typedef dynamic_library_func_t
 * @brief Defines a type for dynamic library function pointers
 *        in Unix-like systems.
 *
 * On Unix-like systems, dynamic library functions are represented using void*.
 */
typedef void *dynamic_library_func_t;

/**
 * @typedef process_id_t
 * @brief Defines a type alias for process identifiers on UNIX-like platforms.
 *
 * This typedef creates an alias for the pid_t type, which is defined in
 * POSIX-compliant systems for representing process IDs.
 *
 * The pid_t type is typically an alias for a signed integer.
 * By using this alias, the code can be more portable and agnostic to the
 * underlying operating system, thus hiding the complexity and differences
 * between how process IDs are managed across different platforms.
 *
 * @note This definition is specific to UNIX-like platforms,
 *       including Linux and macOS.
 */
typedef pid_t process_id_t;

#else

/**
 * @def dynamic_library_extension
 * @brief Defines the file extension for dynamic libraries on Windows.
 *
 * The .dll (dynamic-link library) file format is used for dynamic libraries on
 * Windows. This extension is required when loading libraries at runtime using
 * LoadLibrary or similar mechanisms.
 */
constexpr const auto DYNAMIC_LIBRARY_EXTENSION = ".dll";

/**
 * @typedef error_code_t
 * @brief Represents error codes returned
 *        by dynamic library functions on Windows.
 *
 * This type is an alias for unsigned long. Windows functions related to dynamic
 * library management, such as LoadLibrary and GetLastError, use this type for
 * representing error codes or statuses.
 */
using error_code_t = unsigned long;

/**
 * @typedef dynamic_library_handle_t
 * @brief Type definition for dynamic library handles in Windows.
 *
 * In Windows, dynamic library handles are represented using HINSTANCE,
 * as defined in <windows.h>.
 */
typedef HINSTANCE dynamic_library_handle_t;

/**
 * @typedef dynamic_library_func_t
 * @brief Defines a type for dynamic library function pointers in Windows.
 *
 * In Windows, dynamic library functions are represented using FARPROC,
 * as defined in <windows.h>.
 */
typedef FARPROC dynamic_library_func_t;

/**
 * @typedef process_id_t
 * @brief Defines a type alias for process identifiers on Windows platforms.
 *
 * This typedef creates an alias for the DWORD type, which is used to represent
 * process identifiers in the Windows API. The DWORD type is a 32-bit unsigned
 * integer. By using this alias, the code can maintain platform-agnosticism to
 * some extent by abstracting away the specific type used to represent process
 * IDs on different operating systems.
 *
 * @note This definition is specific to Windows platforms.
 */
typedef DWORD process_id_t;

#endif

/**
 * @brief Retrieves the last error code
 *        in a platform-independent manner.
 *
 * @return error_code_t The last error code encountered.
 *                      On Windows, this returns the result of GetLastError().
 *                      On UNIX-like systems, it returns the value of errno.
 */
error_code_t
last_error_code();

/**
 * @brief Retrieves a human-readable error message
 *        corresponding to a given error code.
 *
 * @param code The error code for which the error message is to be retrieved.
 * @return A string containing the error message.
 *
 * @note On Windows, this function utilizes FormatMessage
 *       to convert the error code into a readable string.
 *
 *       On UNIX-like systems, it uses strerror.
 */
std::string
error_message(error_code_t code);

/**
 * @brief Retrieves the last error message in a platform-independent manner.
 * @return A string containing the last error message.
 *
 *         The format and type of the string returned
 *         are the same as those described in error_message().
 */
std::string
last_error_message();

/**
 * @brief Retrieves the current process identifier.
 *
 * This function provides a platform-independent way to retrieve the current
 * process's unique identifier. Depending on the operating system on which the
 * application is running, it may use different system calls or APIs to obtain
 * this information.
 *
 * @return process_id_t The process identifier of the current process.
 *
 * @note This function has different implementations based
 *       on the operating system:
 *       - On Windows, it uses GetCurrentProcessId from the Windows API.
 *       - On UNIX-like systems, it uses getpid from the POSIX standard.
 */
process_id_t
current_process_id();

} // namespace mi::os

#endif /* MI_OS_HPP */
