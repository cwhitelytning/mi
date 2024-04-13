/**
 * @file anchor_exception.hpp
 * @brief Defines the anchor_exception class.
 *
 * This header introduces the anchor_exception, an exception class tailored for
 * scenarios specific to anchor operations within the MI framework.
 *
 * It is derived from the runtime_exception class, inheriting its functionality
 * but is specifically designed to represent exceptions related to anchor
 * operations.
 */

#ifndef MI_ANCHOR_EXCEPTION_HPP
#define MI_ANCHOR_EXCEPTION_HPP

#include "runtime_exception.hpp"

namespace mi
{

/**
 * @brief Declares a new exception class named anchor_exception.
 *
 * The anchor_exception class is designed to represent exceptions that occur
 * within the anchor handling functionality of the MI framework.
 *
 * It extends the custom runtime_exception class, providing a specialized
 * exception class that can be used to signal anchor-specific issues.
 */
MI_DECLARE_NEW_EXCEPTION_CLASS(anchor_exception);

} // namespace mi

#endif /* MI_ANCHOR_EXCEPTION_HPP */
