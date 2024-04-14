/**
 * @file datetime_error.hpp
 * @brief Defines the mi::exception::datetime_error class
 *        for date-time related exceptions.
 *
 * This header file introduces a specialized exception class for handling errors related
 * to date-time operations. It leverages the MI_DECLARE_NEW_ERROR_CLASS macro to define
 * the class, allowing it to inherit from mi::exception::runtime_error and utilize its
 * formatted error message capabilities.
 */

#ifndef MI_DATETIME_ERROR_HPP
#define MI_DATETIME_ERROR_HPP

#include "runtime_error.hpp"

/**
 * @namespace mi::exception
 * @brief The mi::exception namespace encapsulates exception handling classes
 *        and functionalities specific to the MI library.
 *
 *        It provides a structured way to handle errors
 *        that are unique to the library's operations and use-cases.
 */
namespace mi::exception
{

/**
 * @brief Declare a new error class for date-time related exceptions.
 *
 * The datetime_error class is intended for use in scenarios where errors occur during
 * date-time processing. It extends the mi::exception::runtime_error class,
 * which allows it to provide detailed, formatted error messages.
 */
MI_DECLARE_NEW_ERROR_CLASS(datetime_error);

} // namespace mi::exception

#endif /* MI_DATETIME_ERROR_HPP */
