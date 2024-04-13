/**
 * @file console_logger.hpp
 * @brief Defines the console_logger class,
 *        which is a specific implementation of base_logger for console output.
 *
 * This header file provides the declaration of the console_logger class,
 * which is designed to log messages to the console.
 *
 * It inherits from the base_logger and overrides
 * the log method to provide the functionality for console output.
 */

#ifndef MI_CONSOLE_LOGGER_HPP
#define MI_CONSOLE_LOGGER_HPP

#include "extension_logger.hpp"

namespace mi
{

/**
 * @class console_logger
 * @brief Logger implementation that outputs logs to the console.
 *
 * The console_logger is a final class derived from extension_logger
 * that specializes the logging behavior to output messages to the console.
 *
 * It uses the functionality provided by the extension_logger class
 * and implements the log method to direct the log messages to
 * the standard console output.
 */
class console_logger final : public extension_logger
{
public:
    /**
     * @brief Inherit the base class constructor.
     *
     * Enables the direct use of extension_logger
     * constructors within console_logger.
     */
    using extension_logger::extension_logger;

    /**
     * @brief Logs a message to the console.
     *
     * Overrides the pure virtual function from the base_logger class
     * to implement the logging of messages to the console.
     *
     * The function is called with the sender of the log message,
     * the log level, and the log message itself.
     *
     * @param sender The entity that is sending the log message.
     *               It is a reference to a const extension object.
     *
     * @param level The severity level of the log message,
     *              represented by the logger_level enum.
     *
     * @param message The actual message to be logged,
     *                encapsulated in a ustring_view.
     */
    void
    log(const sender_type &sender, logger_level level, ustring_view message) override;
};

} // namespace mi

#endif /* MI_CONSOLE_LOGGER_HPP */
