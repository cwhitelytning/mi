/**
 * @file range_error.hpp
 * @brief Defines the mi::exception::range_error class
 *        for range-related exceptions.
 *
 * This header file declares an exception class specifically
 * for errors that occur when a value does not fall within an expected range.
 *
 * It uses the MI_DECLARE_NEW_ERROR_CLASS macro to create a new error class that inherits
 * from mi::exception::runtime_error, thus benefiting from its formatted error message
 * capabilities.
 */

#ifndef MI_RANGE_ERROR_HPP
#define MI_RANGE_ERROR_HPP

#include "runtime_error.hpp"

/**
 * @namespace mi::exception
 * @brief The mi::exception namespace is designated for all exception classes related
 *        to the MI library, providing structured exception handling specific to the
 *        library's needs.
 */
namespace mi::exception
{

/**
 * @brief Declare a new error class for range errors.
 *
 * This class is designed to report errors regarding values that are outside the expected
 * range. Inherits from mi::exception::runtime_error to allow for custom error messages
 * formatted with additional context information.
 */
MI_DECLARE_NEW_ERROR_CLASS(range_error);

} // namespace mi::exception

#endif /* MI_RANGE_ERROR_HPP */
