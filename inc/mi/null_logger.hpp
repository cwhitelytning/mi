/**
 * @file null_logger.hpp
 * @brief Defines a logger that performs no logging operations.
 *
 * This is a part of a logging library which provides an implementation
 * for a logger that ignores all log messages, acting as a "null" logger.
 */

#ifndef MI_NULL_LOGGER_HPP
#define MI_NULL_LOGGER_HPP

#include "base_logger.hpp"

namespace mi::logger
{

/**
 * @class null_logger
 * @brief A logger class that ignores all log messages.
 *
 * The null_logger class inherits from base_logger and is used
 * to ignore logging messages in scenarios where logging is not required.
 * It overrides the log function but provides no implementation
 * (a no-operation), effectively discarding all log messages.
 */
class null_logger final : public base_logger<extension>
{
public:
    /**
     * @brief Inherits the base_logger's constructors.
     * This allows the null_logger to be initialized in the same manner as the
     * base_logger.
     */
    using base_logger::base_logger;

    /**
     * @brief Overrides the log function to perform no logging.
     *
     * This function is called to log a message. In the case of null_logger,
     * this function performs no operations, effectively discarding the message.
     *
     * @param level The severity level of the log message.
     * @param args The contents of the log message, provided as a list of string views.
     */
    void
    log(const extension &sender, logger_level level, std::string_view message) override
    {
        /* No operation performed for null_logger */
    }
};

} // namespace mi::logger

#endif /* MI_NULL_LOGGER_HPP */
