/**
 * @file logger_level.hpp
 * @brief Defines the levels of logging severity for mi namespace.
 *
 * This file contains the enumeration of logging levels used within the mi namespace.
 * These levels are intended to indicate the severity of the logs that are generated.
 * The levels include from debug, which is the least severe, to emergency,
 * which indicates a system-critical issue.
 */

#ifndef MI_LOGGER_LEVEL_HPP
#define MI_LOGGER_LEVEL_HPP

#include "unicode.hpp"

/**
 * @brief Macro that converts a logger level
 *        to its corresponding string representation.
 *
 * This macro takes a logger level as its argument and returns a string literal
 * representing the name of the level. The logger level is expected to be one of
 * the predefined logger level constants. If the level does not match any of the
 * known levels, it returns "???" indicating an unknown level.
 *
 * @param level The logger level to be converted to string.
 *              This should be one of the predefined logger level constants.
 *
 * @return A string literal corresponding to the given logger level.
 *         If the level is not recognized, "???" is returned.
 *
 * Example usage:
 * @code
 * logger_level level = LOGGER_DEBUG_LEVEL;
 * const char* levelStr = LOGGER_LEVEL_TO_STRING(level);
 * printf("Log level: %sn", levelStr); // Output: Log level: DBG
 * @endcode
 */
#define LOGGER_LEVEL_TO_STRING(level)                                                    \
    ((level) == LOGGER_DEBUG_LEVEL       ? USTRING("DBG")                                \
     : (level) == LOGGER_INFO_LEVEL      ? USTRING("INF")                                \
     : (level) == LOGGER_NOTICE_LEVEL    ? USTRING("NTC")                                \
     : (level) == LOGGER_WARNING_LEVEL   ? USTRING("WRN")                                \
     : (level) == LOGGER_ERROR_LEVEL     ? USTRING("ERR")                                \
     : (level) == LOGGER_CRITICAL_LEVEL  ? USTRING("CRT")                                \
     : (level) == LOGGER_ALERT_LEVEL     ? USTRING("ALT")                                \
     : (level) == LOGGER_EMERGENCY_LEVEL ? USTRING("EMG")                                \
                                         : USTRING("???"))

namespace mi
{

/**
 * @enum logger_level
 * @brief Enumerates the levels of logging severity.
 *
 * These enumerated values represent the various levels of severity for log messages
 * within the logger system. Usage of these levels helps in filtering log output
 * based on the importance and the need for action.
 *
 * @var logger_level::LOGGER_DEBUG_LEVEL
 *      Debug level for detailed system information,
 *      intended for development use.
 *
 * @var logger_level::LOGGER_INFO_LEVEL
 *      Informational messages that highlight
 *      the progress of the application.
 *
 * @var logger_level::LOGGER_NOTICE_LEVEL
 *      Normal but significant events that are more
 *      important than informational messages.
 *
 * @var logger_level::LOGGER_WARNING_LEVEL
 *      Warning messages not necessarily indicative
 *      of an error but of potential issues.
 *
 * @var logger_level::LOGGER_ERROR_LEVEL
 *      Error messages indicating that a problem occurred
 *      but the application can still continue running.
 *
 * @var logger_level::LOGGER_CRITICAL_LEVEL
 *      Critical conditions that require immediate attention
 *      but are not as severe as errors.
 *
 * @var logger_level::LOGGER_ALERT_LEVEL
 *      Alerts that demand action immediately
 *      to prevent system failure.
 *
 * @var logger_level::LOGGER_EMERGENCY_LEVEL
 *      Emergency level indicating system is unusable
 *      and requires immediate intervention.
 */
enum logger_level : unsigned
{
    LOGGER_DEBUG_LEVEL     = 0, /**< Detailed debug information. */
    LOGGER_INFO_LEVEL      = 1, /**< Runtime events that are not errors. */
    LOGGER_NOTICE_LEVEL    = 2, /**< Normal but significant events. */
    LOGGER_WARNING_LEVEL   = 3, /**< Indicates potential problem. */
    LOGGER_ERROR_LEVEL     = 4, /**< Error conditions. */
    LOGGER_CRITICAL_LEVEL  = 5, /**< Critical conditions. */
    LOGGER_ALERT_LEVEL     = 6, /**< Action must be taken immediately. */
    LOGGER_EMERGENCY_LEVEL = 7  /**< System is unusable. */
};

/**
 * @brief Converts a logger_level enum
 *        to its string representation using LOGGER_LEVEL_TO_STRING macro.
 *
 * This function serves as a wrapper around the LOGGER_LEVEL_TO_STRING macro,
 * converting the logger_level enum to a string view
 * which represents the name of the level.
 *
 * It allows for the logger_level enum to be used directly
 * with functions that require a string representation.
 *
 * @param level The logger level of type enum logger_level to be converted to string.
 *
 * @return A ustring_view containing the string representation of the logger level.
 *         If the level does not match any of the known levels,
 *         a string view containing "???" is returned.
 *
 * Example usage:
 * @code
 * enum logger_level level = LOGGER_DEBUG_LEVEL;
 * ustring_view levelStr = mi::logger_level_to_string(level);
 * std::cout << "Log level: " << levelStr.data() << std::endl; // Output: Log level: DBG
 * @endcode
 */
ustring_view
logger_level_to_string(enum logger_level level);

} // namespace mi

#endif /* MI_LOGGER_LEVEL_HPP */
