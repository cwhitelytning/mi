/**
 * @file str.hpp
 * @brief Defines type aliases for strings and characters that
 *        are unicode-aware and platform-specific within the `mi` namespace.
 */

#ifndef MI_STR_HPP
#define MI_STR_HPP

#include "builtin.hpp"
#include <sstream>

namespace mi
{

/**
 * @brief Writes a message to an output stream.
 *
 * This function is the base case for the variadic template function that
 * recursively replaces "{}" placeholders with arguments in the message.
 *
 * @param os The output stream to write the message to.
 * @param message The message to be written to the output stream
 *                without formatting.
 */
static void
interpolate_stream(std::ostream &os, std::string_view message) noexcept
{
    os << message;
}

/**
 * @brief Writes a formatted message to an output stream,
 *        replacing "{}" placeholders with arguments.
 *
 * Recursively calls itself to replace each "{}" placeholder in the message
 * with the provided arguments until all placeholders are replaced
 * or arguments are used.
 *
 * @tparam T The type of the first value to be inserted
 *           in place of the placeholder.
 *
 * @tparam Args Variadic template for the remaining arguments.
 *
 * @param os The output stream to write the formatted message to.
 * @param message The message with "{}" placeholders for formatting.
 * @param value The argument to replace the first occurrence of "{}".
 * @param args The remaining arguments to replace any further "{}" placeholders.
 */
template <typename T, typename... Args>
void
interpolate_stream(std::ostream    &os,
                   std::string_view message,
                   T              &&value,
                   Args &&...args) noexcept
{
    auto pos = message.find("{}");
    if (pos == std::string::npos)
    {
        interpolate_stream(os, message);
        return;
    }
    os << message.substr(0, pos) << value;
    interpolate_stream(os, message.substr(pos + 2), std::forward<Args>(args)...);
}

/**
 * @brief Creates a formatted string from a message template
 *        and a set of arguments.
 *
 * This function uses the interpolate_stream function templates to perform
 * substitution of "{}" placeholders with the provided arguments,
 * and returns the resulting string.
 *
 * @tparam Args The types of the values to be inserted
 *              in place of the placeholders.
 *
 * @param message The message template string with "{}" placeholders
 *                for formatting.
 *
 * @param args The arguments to replace "{}" placeholders
 *             in the message template.
 *
 * @return A formatted string with placeholders
 *         replaced by the argument values.
 */
template <typename... Args>
std::string
interpolate_string(std::string_view message, Args &&...args) noexcept
{
    std::stringstream oss;
    interpolate_stream(oss, message, std::forward<Args>(args)...);
    return oss.str();
}

/**
 * @brief Converts a C-style string to a std::string.
 *
 * This function safely converts a C-style string (char array)
 * to a C++ std::string.
 *
 * It checks if the input pointer is NULL. If it is not NULL, it creates a
 * std::string from the C-style string; otherwise, it returns an empty
 * std::string.
 *
 * @param src A pointer to the constant C-style string to be converted.
 *            It can be nullptr.
 *
 * @return std::string A std::string that contains the same characters as the
 *                     input C-style string.
 *
 *                     If the input is nullptr,
 *                     an empty std::string is returned.
 */
MI_BUILTIN std::string
           cstring_to_string(const char *src)
{
    return src ? std::string(src) : std::string();
}

} // namespace mi

#endif /* MI_STR_HPP */