/**
 * @file builtin.hpp
 * @brief Defines the MI_BUILTIN macro for forcing inline functions
 *        across different compilers.
 *
 * This header file defines the MI_BUILTIN macro, which is used to force the
 * inlining of functions across a variety of compilers. This is particularly
 * useful for critical performance paths where function call overhead should
 * be minimized.
 */

#ifndef MI_BUILTIN_HPP
#define MI_BUILTIN_HPP

#include "compiler_def.h"

/**
 * @def MI_BUILTIN
 * @brief Compiler-specific attribute to force function inlining.
 *
 * The macro is defined differently depending on the compiler being used to
 * compile the code. It leverages the specific compiler's attribute or keyword
 * that forces a function to be inlined, overriding the compiler's own
 * heuristics.
 */

#ifdef MI_COMPILER_MSVC
#    define MI_BUILTIN __forceinline

#elif defined(MI_COMPILER_GCC) || defined(MI_COMPILER_CLANG)
#    define MI_BUILTIN __attribute__((always_inline)) inline

#elif defined(MI_COMPILER_INTEL)
#    define MI_BUILTIN __attribute__((always_inline)) inline

#elif defined(MI_COMPILER_IBM)
#    define MI_BUILTIN __attribute__((always_inline)) inline

#elif defined(MI_COMPILER_SOLARIS)
#    define MI_BUILTIN __attribute__((always_inline)) inline

#elif defined(MI_COMPILER_BORLAND)
#    define MI_BUILTIN __inline

#elif defined(MI_COMPILER_IAR)
#    define MI_BUILTIN __ramfunc

#elif defined(MI_COMPILER_ARM)
#    define MI_BUILTIN __attribute__((always_inline)) inline

#elif defined(MI_COMPILER_PGI)
#    define MI_BUILTIN __attribute__((always_inline)) inline

#elif defined(MI_COMPILER_TI)
#    define MI_BUILTIN __attribute__((always_inline)) inline

#else
#    error "Forced function inlining is not supported by this compiler"
#endif

#endif /* MI_BUILTIN_HPP */