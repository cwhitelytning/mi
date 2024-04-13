/**
 * @file null_pointer_exception.hpp
 * @brief Defines the null pointer exception class.
 *
 * Provides the definition of the null pointer exception class,
 * which is used to represent exceptions related to null pointer dereferencing.
 */

#ifndef NULL_POINTER_ERROR_HPP
#define NULL_POINTER_ERROR_HPP

#include "runtime_exception.hpp"

namespace mi
{
/**
 * @class null_pointer_exception
 * @brief Exception class for null pointer exceptions.
 *
 * null pointer exception is a specialized exception that is thrown when an
 * attempt is made to dereference a null pointer within the mi framework.
 *
 * It inherits from runtime exception,
 * providing additional context specific to null pointer issues.
 */
MI_DECLARE_NEW_EXCEPTION_CLASS(null_pointer_exception);

} // namespace mi

#endif /* NULL_POINTER_ERROR_HPP */
