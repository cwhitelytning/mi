/**
 * @file out_of_range_exception.hpp
 * @brief Defines the out of range exception exception class for the mi library.
 */

#ifndef MI_OUT_OF_RANGE_EXCEPTION_HPP
#define MI_OUT_OF_RANGE_EXCEPTION_HPP

#include "runtime_exception.hpp"

namespace mi
{

/**
 * @brief Macro to declare a new exception class named out_of_range_exception.
 *
 * DECLARE_NEW_ERROR_CLASS is a macro that simplifies the creation
 * of new exception classes. It ensures consistency and reduces boilerplate code
 * required for declaring new types of exceptions.
 *
 * The out_of_range_exception class extends a base exception type
 * (runtime_exception in this context) and is customized for exceptions that
 * occur when an operation tries to access an element outside the valid range
 * of an object, similar to std::out_of_range.
 */
MI_DECLARE_NEW_EXCEPTION_CLASS(out_of_range_exception);

} // namespace mi

#endif /* MI_OUT_OF_RANGE_EXCEPTION_HPP */