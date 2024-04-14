/**
 * @file runtime_error.hpp
 * @brief Defines the mi::exception::runtime_error class
 *        and a macro for declaring custom error classes.
 *
 * This header file provides a custom exception class that extends
 * the standard std::exception with formatted error message capabilities.
 *
 * Additionally, it defines a macro that simplifies the creation
 * of new exception classes derived from mi::exception::runtime_error.
 *
 * Dependencies:
 * - <exception> for the base std::exception class
 * - "format.hpp" for string formatting utilities
 *
 * Usage example:
 * @code
 * throw mi::exception::runtime_error("Error code: {}", errorCode);
 * @endcode
 *
 * @note This file requires C++17 or above due to usage of std::string_view
 *       and template argument deduction.
 */

#ifndef MI_RUNTIME_ERROR_HPP
#define MI_RUNTIME_ERROR_HPP

#include "format.hpp"
#include <exception>
#include <string>

/**
 * @def MI_DECLARE_NEW_ERROR_CLASS(classname)
 * @brief Macro to declare a new error class
 *        that inherits from mi::exception::runtime_error.
 *
 * This macro simplifies the creation of new error classes within the mi::exception
 * namespace. Classes created with this macro will directly inherit constructors
 * from runtime_error, allowing them to be constructed with the same argument types.
 *
 * @param classname The name of the class to declare,
 *                  which will become a subclass of runtime_error.
 */
#define MI_DECLARE_NEW_ERROR_CLASS(classname)                                            \
    class classname : public mi::exception::runtime_error                                \
    {                                                                                    \
    public:                                                                              \
        using runtime_error::runtime_error;                                              \
    }

/**
 * @namespace mi::exception
 * @brief Namespace for exception classes used within the MI library.
 */
namespace mi::exception
{

/**
 * @class runtime_error
 * @brief An exception class that represents errors that can occur at runtime.
 * @details Inherits from std::exception
 *          and provides a constructor that formats the error message.
 */
class runtime_error : public std::exception
{
public:
    /**
     * @brief Constructs a new runtime error with a formatted message.
     *
     * @param format A string view representing the format of the error message.
     * @param args   Arguments that are passed to format the error message.
     */
    template <typename... Args>
    explicit runtime_error(std::string_view format, Args &&...args)
        : m_message(format::interpolate_string(format, std::forward<Args>(args)...))
    {
    }

    /**
     * @brief Retrieves the error message.
     * @return A pointer to the error message as a C-style string.
     */
    [[nodiscard]]
    const char *
    what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    std::string m_message; ///< The formatted error message stored as a string.
};

} // namespace mi::exception

#endif /* MI_RUNTIME_ERROR_HPP */
