/**
 * @file unicode.hpp
 * @brief Defines type aliases for character stream classes
 *        based on the compilation environment.
 *
 * This header file defines type aliases
 * for handling character streams and strings.
 *
 * It adapts to Unicode or multi-byte environments by providing appropriate type
 * aliases for fundamental string and stream types in the C++ Standard Library.
 *
 * The adaptation is based on the compilation environment, especially targeting
 * differences between Windows with Unicode defined and other platforms.
 */

#ifndef MI_UNICODE_HPP
#define MI_UNICODE_HPP

#include "os_def.hpp"
#include <iostream>
#include <regex>

#if defined(MI_OS_WINDOWS) && defined(UNICODE)
/**
 * @def USTRING(str)
 * @brief Converts a normal string literal into a wide character string literal
 *        on Windows when UNICODE is defined.
 *
 * @param str The string literal to be converted.
 * @return A wide character string literal if UNICODE is defined,
 *         allowing for Unicode support.
 */
#    define USTRING(str) L##str
#else
/**
 * @def USTRING(str)
 * @brief Leaves the string literal unchanged on Unix-like systems.
 * @param str The string literal.
 * @return The original string literal, as Unix-like systems typically
 *         do not differentiate between Unicode and non-Unicode strings
 *         at this level.
 */
#    define USTRING(str) str
#endif

/**
 * @brief Defines macros for universal character input and output streams.
 *
 * This provides macros for input and output stream objects that automatically
 * select the wide character versions on Windows when UNICODE is defined,
 * and the regular character versions otherwise.
 */
#if defined(MI_OS_WINDOWS) && defined(UNICODE)

/**
 * @def ucin
 * @brief Alias for the standard wide character input stream object.
 *
 * Defines ucin as an alias for std::wcin,
 * which is the wide character version of std::cin used for standard input operations.
 *
 * It allows for input of wide characters,
 * which is essential for supporting international character sets.
 */
#    define ucin std::wcin

/**
 * @def ucout
 * @brief Alias for the standard wide character output stream object.
 *
 * Defines ucout as an alias for std::wcout,
 * which is the wide character version of std::cout used for standard output operations.
 *
 * It supports output of wide characters,
 * accommodating international character sets.
 */
#    define ucout std::wcout

/**
 * @def uclog
 * @brief Alias for the standard wide character logging stream object.
 *
 * Defines uclog as an alias for std::wclog,
 * which is the wide character version of std::clog used for logging operations.
 *
 * It facilitates logging of wide characters,
 * which can be necessary for internationalization.
 */
#    define uclog std::wclog

/**
 * @def ucerr
 * @brief Alias for the standard wide character error stream object.
 *
 * Defines ucerr as an alias for std::wcerr, which is the wide character version of
 * std::cerr used for error output operations. It ensures that error messages can
 * include wide characters, suitable for a variety of languages.
 */
#    define ucerr std::wcerr

#else

/**
 * @def ucin
 * @brief Alias for the standard input stream object.
 *
 * Defines ucin as an alias for std::cin, which is used for standard input operations.
 * This alias standardizes the way input is taken in the application, facilitating
 * potential future transitions to different character types.
 */

#    define ucin std::cin

/**
 * @def ucout
 * @brief Alias for the standard output stream object.
 *
 * Defines ucout as an alias for std::cout, which is used for standard output operations.
 * This alias serves to standardize output operations across the application.
 */

#    define ucout std::cout

/**
 * @def uclog
 * @brief Alias for the standard logging stream object.
 *
 * Defines uclog as an alias for std::clog, which is used for logging operations.
 * This alias is used to maintain consistency in how logging is performed throughout
 * the application.
 */
#    define uclog std::clog

/**
 * @def ucerr
 * @brief Alias for the standard error stream object.
 *
 * Defines ucerr as an alias for std::cerr, which is used for error output operations.
 * This alias ensures that error messages are handled uniformly across the application.
 */
#    define ucerr std::cerr

#endif

namespace mi
{

#if defined(MI_OS_WINDOWS) && defined(UNICODE)

/**
 * @brief Type alias for Unicode input string stream.
 */
using uistringstream = std::wistringstream;

/**
 * @brief Type alias for Unicode output string stream.
 */
using uostringstream = std::wostringstream;

/**
 * @brief Type alias for Unicode input/output string stream.
 */
using ustringstream = std::wstringstream;

/**
 * @brief Type alias for Unicode string view.
 */
using ustring_view = std::wstring_view;

/**
 * @brief Type alias for Unicode string buffer.
 */
using ustringbuf = std::wstringbuf;

/**
 * @brief Type alias for Unicode file input stream.
 */
using uifstream = std::wifstream;

/**
 * @brief Type alias for Unicode file output stream.
 */
using uofstream = std::wostream;

/**
 * @brief Type alias for Unicode file buffer.
 */
using ufilebuf = std::wfilebuf;

/**
 * @brief Type alias for Unicode output stream.
 */
using uostream = std::wostream;

/**
 * @brief Type alias for Unicode file input/output stream.
 */
using ufstream = std::wfstream;

/**
 * @brief Type alias for Unicode input stream
 *        (currently mapped to non-wide variant, potentially an error).
 */
using uistream = std::istream;

/**
 * @brief Type alias for Unicode string.
 */
using ustring = std::wstring;

/**
 * @brief Type alias for Unicode regular expression.
 */
using uregex = std::wregex;

/**
 * @brief Type alias for Unicode character.
 */
using uchar = wchar_t;

/**
 * @brief Type alias for Unicode base for input/output operations.
 */
using uos = std::wios;

#else

/**
 * @brief Type alias for multi-byte input string stream.
 */
using uistringstream = std::istringstream;

/**
 * @brief Type alias for multi-byte output string stream.
 */
using uostringstream = std::ostringstream;

/**
 * @brief Type alias for multi-byte input/output string stream.
 */
using ustringstream = std::stringstream;

/**
 * @brief Type alias for Unicode string view.
 */
using ustring_view = std::string_view;

/**
 * @brief Type alias for multi-byte string buffer.
 */
using ustringbuf = std::stringbuf;

/**
 * @brief Type alias for multi-byte file input stream.
 */
using uifstream = std::ifstream;

/**
 * @brief Type alias for multi-byte file output stream.
 */
using uofstream = std::ofstream;

/**
 * @brief Type alias for multi-byte file buffer.
 */
using ufilebuf = std::filebuf;

/**
 * @brief Type alias for multi-byte output stream.
 */
using uostream = std::ostream;

/**
 * @brief Type alias for multi-byte file input/output stream.
 */
using ufstream = std::fstream;

/**
 * @brief Type alias for multi-byte input stream.
 */
using uistream = std::istream;

/**
 * @brief Type alias for multi-byte string.
 */
using ustring = std::string;

/**
 * @brief Type alias for multi-byte regular expression.
 */
using uregex = std::regex;

/**
 * @brief Type alias for multi-byte character.
 */
using uchar = char;

/**
 * @brief Type alias for multi-byte base for input/output operations.
 */
using uos = std::ios;

#endif

} // namespace mi

#endif /* MI_UNICODE_HPP */
