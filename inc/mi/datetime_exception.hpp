/**
 * @file datetime_exception.hpp
 * @brief Defines the datetime_exception class in the mi::exception namespace.
 *
 * This header defines an exception type specific to date and time operations
 * within the mi library. It is meant to be used for exceptions that are
 * specific to date and time processing and cannot be adequately represented by
 * standard runtime exceptions.
 */

#ifndef MI_DATETIME_EXCEPTION_HPP
#define MI_DATETIME_EXCEPTION_HPP

#include "runtime_exception.hpp"

namespace mi
{

/**
 * @class datetime_exception
 * @brief Exception type for date and time operation exceptions.
 *
 * datetime exception extends the standard runtime exception to provide more
 * context specific to exceptions encountered during date and time processing in
 * the mi library. It can be thrown in scenarios where there is a specific type
 * of failure related to date and time handling that warrants distinction from
 * general runtime exceptions.
 */
MI_DECLARE_NEW_EXCEPTION_CLASS(datetime_exception);

} // namespace mi

#endif /* MI_DATETIME_EXCEPTION_HPP */
