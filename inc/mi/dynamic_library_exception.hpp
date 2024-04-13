/**
 * @file dynamic_library_exception.hpp
 * @brief Defines the dynamic library exception class
 *        for handling dynamic library loading exceptions.
 *
 * This header file provides the definition of the dynamic library exception
 * class, which is specifically used to report exceptions related to the loading
 * of dynamic libraries. It inherits from runtime exception, providing more
 * specific context related to dynamic library operations.
 */

#ifndef MI_DYNAMIC_LIBRARY_EXCEPTION_HPP
#define MI_DYNAMIC_LIBRARY_EXCEPTION_HPP

#include "runtime_exception.hpp"

namespace mi
{

/**
 * @class dynamic_library_exception
 * @brief Exception class for dynamic library related exceptions.
 *
 * The dynamic library exception class is a specialization of the runtime
 * exception class. It is thrown when an exception occurs during the loading,
 * linking, or usage of a dynamic library.
 *
 * This includes, but is not limited to, situations where the dynamic library
 * cannot be found, the required symbols are missing, or the library is not
 * compatible with the current platform.
 */
MI_DECLARE_NEW_EXCEPTION_CLASS(dynamic_library_exception);

} // namespace mi

#endif /* MI_DYNAMIC_LIBRARY_EXCEPTION_HPP */
