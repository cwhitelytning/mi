/**
 * @file runtime_exception.hpp
 * @brief Contains the definition of the runtime exception class.
 */

#ifndef MI_RUNTIME_EXCEPTION_HPP
#define MI_RUNTIME_EXCEPTION_HPP

#include "str.hpp"
#include "unicode.hpp"
#include <exception>

/**
 * @brief Declares a new exception class that inherits from runtime_exception.
 *
 * This macro is used to quickly define new exception classes that are derived
 * from a common base, in this case, runtime_exception.
 *
 * It allows for the inheritance of constructors from runtime_exception,
 * enabling the new exception class to be thrown with various messages
 * or error codes, just like its base class.
 *
 * @param classname The name of the new exception class to be defined.
 *
 * @note This will define a class named MyCustomException that inherits from
 *       runtime_exception. It can then be used in try-catch blocks or thrown
 *       using the throw keyword.
 */
#define MI_DECLARE_NEW_EXCEPTION_CLASS(classname)                                        \
    class classname : public runtime_exception                                           \
    {                                                                                    \
    public:                                                                              \
        using runtime_exception::runtime_exception;                                      \
    }

namespace mi
{

/**
 * @class runtime_exception
 * @brief An exception class that extends std::exception,
 *        providing message formatting capabilities.
 *
 * runtime_exception facilitates creating exception messages using string
 * interpolation, making it easier to include dynamic data in exception
 * messages.
 */
class runtime_exception : public std::exception
{
public:
    /**
     * @brief Constructs the runtime exception with a formatted message.
     *
     * Uses a template to allow for string interpolation based on provided
     * arguments. This constructor will format the message string using
     * the provided arguments before storing it internally.
     *
     * @tparam Args Variadic template arguments for the message formatting.
     * @param message The base message string that defines the format.
     *                This should include placeholders matching
     *                the formatting arguments.

     * @param args Arguments to be formatted into the base message string
     *             according to standard string formatting rules.
     */
    template <typename... Args>
    explicit runtime_exception(std::string_view message, Args &&...args)
        : m_message(interpolate_string(message, std::forward<Args>(args)...))
    {
    }

    /**
     * @brief Overrides the standard what() function
     *        to return the exception message.
     *
     * Provides access to the exception message formatted at construction.
     * This message is returned as a C-string.
     *
     * @return The formatted exception message as a constant C-string.
     */
    [[nodiscard]]
    const char *
    what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    std::string m_message; ///< The formatted message stored by the exception.
};

} // namespace mi

#endif /* MI_RUNTIME_EXCEPTION_HPP */
