/**
 * @file NULL_POINTER_ERROR_HPP
 * @brief Defines the mi::exception::null_pointer_error class
 *        for null pointer related exceptions.
 *
 * This header encapsulates the declaration of a specific exception class
 * for handling null pointer related errors within the MI library.
 *
 * It makes use of the MI_DECLARE_NEW_ERROR_CLASS macro to ensure the new error class
 * is properly set up with inheritance from mi::exception::runtime_error.
 *
 * Dependencies:
 * - "runtime_error.hpp" for the base mi::exception::runtime_error class
 *                       that provides custom runtime error functionality.
 */

#ifndef NULL_POINTER_ERROR_HPP
#define NULL_POINTER_ERROR_HPP

#include "runtime_error.hpp"

/**
 * @namespace mi::exception
 * @brief The mi::exception namespace is used to encapsulate
 *         all exception classes specific to the MI library.
 */
namespace mi::exception
{

/**
 * @brief Declare a new error class for null pointer exceptions.
 *
 * This class is intended for use when null pointer
 * related errors are encountered.
 *
 * It inherits from mi::exception::runtime_error,
 * which allows for the use of formatted error messages.
 */
MI_DECLARE_NEW_ERROR_CLASS(null_pointer_error);

} // namespace mi::exception

#endif /* NULL_POINTER_ERROR_HPP */
