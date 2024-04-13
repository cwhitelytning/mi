/**
 * @file exception_handler.hpp
 * @brief Defines exception handling utilities for the mi namespace.
 *
 * Provides type aliases for exception handling functions within the mi namespace,
 * allowing for customizable responses to exceptions.
 */

#ifndef MI_EXCEPTION_HANDLER_HPP
#define MI_EXCEPTION_HANDLER_HPP

#include <exception>
#include <functional>

namespace mi
{

/**
 * @typedef exception_handler_t
 * @brief A function type that handles exceptions without returning a value.
 *
 * This type alias represents a function that takes a constant reference to an
 * std::exception object and does not return a value, allowing for custom
 * processing of exceptions.
 *
 * @param exception A constant reference to the caught std::exception.
 */
using exception_handler_t = std::function<void(const std::exception &exception)>;

} // namespace mi

#endif /* MI_EXCEPTION_HANDLER_HPP */
