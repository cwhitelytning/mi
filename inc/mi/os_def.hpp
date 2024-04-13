/**
 * @file os_def.hpp
 * @brief Definitions for identifying operating systems.
 *
 * This header file contains macro definitions that help in identifying
 * the operating system on which the code will run.
 *
 * Definitions allow portions of code specific to each supported
 * operating system to be conditionally compiled.
 */

#ifndef MI_OS_DEF_HPP
#define MI_OS_DEF_HPP

#if defined(_WIN32) || defined(_WIN64)
/**
 * @def MI_OS_WINDOWS
 * @brief A macro that is defined if the application
 *        is being compiled on Windows.
 *
 * If the compiler defines either _WIN32 or _WIN64, indicating that the
 * application is being compiled on a Windows system, this macro is defined.
 * This can be used to wrap Windows-specific code.
 */
#    define MI_OS_WINDOWS

#elif defined(__linux__)
/**
 * @def MI_OS_LINUX
 * @brief A macro that is defined if the application
 *        is being compiled on a Linux system.
 *
 * If the compiler defines __linux__, indicating that the application is being
 * compiled on a Linux system, this macro is defined. This can be used to wrap
 * Linux-specific code.
 */
#    define MI_OS_LINUX

/**
 * @def MI_OS_APPLE
 * @brief A macro that is defined if the application
 *        is being compiled on an Apple system.
 *
 * If the compiler defines __APPLE__, indicating that the application is being
 * compiled on an Apple system (macOS, iOS, tvOS, watchOS), this macro is
 * defined. This can be used to wrap Apple-specific code.
 */
#elif defined(__APPLE__)
#    define MI_OS_APPLE

#else
/**
 * @error "Failed to identify operating system"
 * @brief An error directive that is issued if none of the above macros could be
 * defined.
 *
 * If the application is being compiled on a system that is not recognized (not
 * Windows, Linux, or Apple), the compiler emits an error directive, halting
 * compilation. This is to ensure that the application does not get compiled on
 * an unsupported operating system.
 */
#    error "Failed to identify operating system"

#endif

#if defined(__unix__) || defined(__unix)
/**
 * @def MI_OS_UNIX_LIKE
 * @brief Definition for UNIX-like OS.
 *
 * If the current OS is UNIX-like, defines MI_OS_UNIX_LIKE.
 */
#    define MI_OS_UNIX_LIKE
#endif

#endif /* MI_OS_DEF_HPP */
