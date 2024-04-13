/**
 * @file format.hpp
 * @brief Format utilities for string manipulation
 *        and stream interpolation within the mi::format namespace.
 */

#ifndef MI_FORMAT_HPP
#define MI_FORMAT_HPP

#include <string>

namespace mi::format
{

/**
 * @brief Returns a placeholder string specific to the character type.
 *
 * @tparam CharType The character type (e.g., char, wchar_t).
 * @return constexpr auto The placeholder string.
 */
template <typename CharType>
constexpr auto
placeholder()
{
    if constexpr (std::is_same_v<CharType, wchar_t>)
    {
        return L"{}";
    }
    return "{}";
}

/**
 * @brief Inserts a message into the output stream.
 *
 * @tparam CharType The character type of the stream and the message.
 * @param os The output stream where the message will be inserted.
 * @param format The format string containing placeholders for the values.
 */
template <typename CharType>
constexpr void
interpolate_stream(std::basic_ostream<CharType>    &os,
                   std::basic_string_view<CharType> format) noexcept
{
    os << format;
}

/**
 * @brief Recursively processes the format string and arguments, inserting them
 *        into the output stream.
 *
 * @tparam CharType The character type of the stream and the format string.
 * @tparam ValueType The type of the first value to be interpolated.
 * @tparam Args The types of the remaining arguments.
 * @param os The output stream where the interpolated content will be inserted.
 * @param format The format string containing placeholders for the values.
 * @param value The first value to be interpolated into the format string.
 * @param args The remaining values to be interpolated.
 */
template <typename CharType, typename ValueType, typename... Args>
constexpr void
interpolate_stream(std::basic_ostream<CharType>    &os,
                   std::basic_string_view<CharType> format,
                   ValueType                      &&value,
                   Args &&...args) noexcept
{
    const auto pos = format.find(placeholder<CharType>());
    if (pos == std::string::npos)
    {
        return interpolate_stream(os, format);
    }
    os << format.substr(0, pos) << value;
    interpolate_stream(os, format.substr(pos + 2), std::forward<Args>(args)...);
}

/**
 * @brief Creates a formatted string by interpolating
 *        a series of values into a format string.
 *
 * @tparam CharType The character type of the format string.
 * @tparam Args The types of the values to be interpolated.
 * @param format The format string containing placeholders for the values.
 * @param args The values to be interpolated into the format string.
 * @return decltype(auto) The resulting formatted string.
 */
template <typename CharType, typename... Args>
constexpr decltype(auto)
interpolate_string(std::basic_string_view<CharType> format, Args &&...args) noexcept
{
    auto oss = std::basic_ostringstream<CharType>();
    interpolate_stream(oss, format, std::forward<Args>(args)...);
    return oss.str();
}

} // namespace mi::format

#endif /* MI_FORMAT_HPP */
