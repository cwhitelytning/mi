/**
 * @file compiler_def.h
 * @brief Definitions related to the compiler and system architecture.
 *
 * This header file contains macro definitions to identify the bitness of the
 * target system architecture and the compiler that is used to compile the code.
 *
 * Definitions help adapt a program to the characteristics
 * of different platforms and compilers.
 */

#ifndef MI_COMPILER_DEF_H
#define MI_COMPILER_DEF_H

/**
 * @def MI_COMPILER_BIT_DEPTH
 * @brief Defines the bit depth of the target architecture.
 *
 * Depending on the target architecture, sets the value to 64 for 64-bit systems
 * and 32 for 32-bit systems. If the architecture is not known, a preprocessor
 * error is generated.
 */

#if defined(__LP64__) || defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__) || \
    defined(__aarch64__) || defined(_M_X64) || defined(_M_ARM64) ||                      \
    defined(__sparc64__) || defined(__mips64)
#    define MI_COMPILER_BIT_DEPTH 64

#elif defined(__ILP32__) || defined(_WIN32) || defined(__i386__) || defined(__ppc__) ||  \
    defined(_M_IX86) || defined(_M_ARM) || defined(__sparc__) || defined(__mips__)
#    define MI_COMPILER_BIT_DEPTH 32

#else
#    error "Unknown architecture"
#endif

/**
 * @def MI_COMPILER_*
 * @brief Specifies the compiler used to compile the program.
 *
 * For each known compiler, a unique macro is defined, which allows,
 * if necessary, to adapt the code to the features
 * or limitations of a particular compiler.
 */

#if defined(__TI_COMPILER_VERSION__)
#    define MI_COMPILER_TI

#elif defined(__TURBOC__)
#    define MI_COMPILER_TURBO

#elif defined(__BORLANDC__)
#    define MI_COMPILER_BORLAND

#elif defined(__WATCOMC__)
#    define MI_COMPILER_WATCOM

#elif defined(__PGI)
#    define MI_COMPILER_PGI

#elif defined(_CRAYC)
#    define MI_COMPILER_CRAY

#elif defined(__ADSPBLACKFIN__) || defined(__ADSPTS__) || defined(__ADSP21000__)
#    define MI_COMPILER_ADSP

#elif defined(__IAR_SYSTEMS_ICC__)
#    define MI_COMPILER_IAR

#elif defined(__SDCC_VERSION_MAJOR)
#    define MI_COMPILER_SDCC

#elif defined(__DCC__)
#    define MI_COMPILER_DIAB

#elif defined(__EMSCRIPTEN__)
#    define MI_COMPILER_EMSCRIPTEN

#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#    define MI_COMPILER_ARM

#elif defined(__KEIL__)
#    define MI_COMPILER_KEIL

#elif defined(__CYGWIN__)
#    define MI_COMPILER_CYGWIN

#elif defined(__INTEL_COMPILER) || defined(__ICC)
#    define MI_COMPILER_INTEL

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#    define MI_COMPILER_SOLARIS

#elif defined(__HP_cc) || defined(__HP_aCC)
#    define MI_COMPILER_HP

#elif defined(__IBMCPP__)
#    define MI_COMPILER_IBM

#elif defined(__APPLE_CC__)
#    define MI_COMPILER_APPLE

#elif defined(_MSC_VER)
#    define MI_COMPILER_MSVC

#elif defined(__clang__)
#    define MI_COMPILER_CLANG

#elif defined(__GNUC__) || defined(__GNUG__)
#    define MI_COMPILER_GCC

#else
#    error "Unknown compiler"
#endif

#endif /* MI_COMPILER_DEF_H */
