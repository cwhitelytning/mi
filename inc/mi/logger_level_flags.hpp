/**
 * @file logger_level_flags.hpp
 * @brief Defines flag constants for various logging levels in mi namespace.
 *
 * This file extends the logger_level definitions by introducing flag constants
 * for each logging level. These flags are useful in defining filter masks that
 * can control the verbosity of the logging output at runtime.
 *
 * Each level is represented as a bit in an unsigned char,
 * allowing combinations of levels to be easily constructed and checked.
 */

#ifndef MI_LOGGER_LEVEL_FLAGS_HPP
#define MI_LOGGER_LEVEL_FLAGS_HPP

#include "logger_level.hpp"

namespace mi
{

/**
 * @enum logger_level_flags
 * @brief Enumerates flags corresponding to logging severity levels.
 *
 * Provides a set of flags, each corresponding to a level of logging severity.
 * These can be combined to form a mask that specifies multiple logging levels.
 * For convenience, a special flag represents all log levels, allowing for easy
 * selection or deselection of verbose logging.
 *
 * @var LOGGER_NONE_LEVEL_FLAGS
 *      Represents no logging level,
 *      used as a base case.
 *
 * @var LOGGER_DEBUG_LEVEL_FLAG
 *      Flag for logging detailed debug information,
 *      useful during development.
 *
 * @var LOGGER_INFO_LEVEL_FLAG
 *      Flag for informational messages
 *      that report general progress of the application.
 *
 * @var LOGGER_NOTICE_LEVEL_FLAG
 *      Flag for normal but significant events
 *      that are worth noting.
 *
 * @var LOGGER_WARNING_LEVEL_FLAG
 *      Flag for warning messages
 *      that indicate potential issues.
 *
 * @var LOGGER_ERROR_LEVEL_FLAG
 *      Flag for error messages
 *      indicating problems that have occurred.
 *
 * @var LOGGER_CRITICAL_LEVEL_FLAG
 *      Flag for critical conditions
 *      that require immediate attention.
 *
 * @var LOGGER_ALERT_LEVEL_FLAG
 *      Flag for alert messages
 *      that demand action to avoid severe consequences.
 *
 * @var LOGGER_EMERGENCY_LEVEL_FLAG
 *      Flag for emergency messages indicating
 *      that the system is unusable due to severe issues.
 *
 * @var LOGGER_ALL_LEVEL_FLAGS
 *      A combination of all flags,
 *      representing all levels of logging severity.
 *
 *      This is useful for setting a filter
 *      that logs every possible message.
 */
enum logger_level_flags : unsigned char
{
    /**
     * @brief Represents no logging level.
     */
    LOGGER_NONE_LEVEL_FLAGS = 0,

    /**
     * @brief Detailed debug information.
     */
    LOGGER_DEBUG_LEVEL_FLAG = (1 << LOGGER_DEBUG_LEVEL),

    /**
     * @brief Informational messages.
     */
    LOGGER_INFO_LEVEL_FLAG = (1 << LOGGER_INFO_LEVEL),

    /**
     * @brief Normal but significant events.
     */
    LOGGER_NOTICE_LEVEL_FLAG = (1 << LOGGER_NOTICE_LEVEL),

    /**
     * @brief Potential issues.
     */
    LOGGER_WARNING_LEVEL_FLAG = (1 << LOGGER_WARNING_LEVEL),

    /**
     * @brief Error conditions.
     */
    LOGGER_ERROR_LEVEL_FLAG = (1 << LOGGER_ERROR_LEVEL),

    /**
     * @brief Critical conditions.
     */
    LOGGER_CRITICAL_LEVEL_FLAG = (1 << LOGGER_CRITICAL_LEVEL),

    /**
     * @brief Action must be taken immediately.
     */
    LOGGER_ALERT_LEVEL_FLAG = (1 << LOGGER_ALERT_LEVEL),

    /**
     * @brief System is unusable.
     */
    LOGGER_EMERGENCY_LEVEL_FLAG = (1 << LOGGER_EMERGENCY_LEVEL),

    /**
     * @brief All logging levels.
     */
    LOGGER_ALL_LEVEL_FLAGS = (LOGGER_DEBUG_LEVEL_FLAG | LOGGER_INFO_LEVEL_FLAG |
                              LOGGER_NOTICE_LEVEL_FLAG | LOGGER_WARNING_LEVEL_FLAG |
                              LOGGER_ERROR_LEVEL_FLAG | LOGGER_CRITICAL_LEVEL_FLAG |
                              LOGGER_ALERT_LEVEL_FLAG | LOGGER_EMERGENCY_LEVEL_FLAG)
};

} // namespace mi

#endif /* MI_LOGGER_LEVEL_FLAGS_HPP */
