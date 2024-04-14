/**
 * @file dynamic_library_error.hpp
 * @brief Defines the mi::exception::dynamic_library_error class.
 *
 * This header file extends the custom exception types provided by the MI library
 * to include an exception specifically for dynamic library-related errors.
 *
 * It leverages a macro to declare the new error class,
 * ensuring it has all the necessary functionality
 * inherited from mi::exception::runtime_error.
 */

#ifndef MI_DYNAMIC_LIBRARY_ERROR_HPP
#define MI_DYNAMIC_LIBRARY_ERROR_HPP

#include "runtime_error.hpp"

/**
 * @namespace mi::exception
 * @brief The mi::exception namespace contains exception
 *        handling classes and utilities for the MI library.
 */
namespace mi::exception
{

/**
 * @brief Declare a new error class for dynamic library errors.
 * @details Utilizes the MI_DECLARE_NEW_ERROR_CLASS macro from "runtime_error.hpp"
 *          to define a new exception class that inherits
 *          from mi::exception::runtime_error.
 */
MI_DECLARE_NEW_ERROR_CLASS(dynamic_library_error);

} // namespace mi::exception

#endif /* MI_DYNAMIC_LIBRARY_ERROR_HPP */
