/**
 * @file base_logger.hpp
 * @brief Base logger class template for logging mechanisms.
 *
 * This file contains the definition of the base_logger class template,
 * which serves as the foundation for all logging mechanisms within the
 * mi namespace. It extends the functionality of the extension class.
 */

#ifndef MI_BASE_LOGGER_HPP
#define MI_BASE_LOGGER_HPP

#include "extension.hpp"
#include "logger_level_flags.hpp"

namespace mi
{

/**
 * @class base_logger<T>
 * @brief Abstract base class for loggers.
 *
 * The base_logger class template is designed to be the base class for
 * all loggers, providing common interface and functionality for logging.
 * It is an abstract class and expects derived classes to implement the
 * log method.
 *
 * @tparam SenderType Type of the sender object associated with the log messages.
 */
template <typename SenderType>
class base_logger : public extension
{
public:
    /**
     * @typedef sender_type
     * @brief Defines the type of the sender object associated with the log messages.
     */
    using sender_type = SenderType;

    /**
     * @brief Constructs a new base_logger object.
     *
     * Initializes a new instance of the base_logger class with a reference
     * to an owner and initial logger level flags.
     *
     * @param owner An rvalue reference to the owner of the logger instance.
     * @param flags Initial logging level flags to be applied.
     */
    template <typename OwnerType>
    explicit base_logger(OwnerType &&owner, logger_level_flags flags)
        : extension(std::forward<OwnerType>(owner)),
          m_flags(flags)
    {
    }

    /**
     * @brief Retrieves the current logging level flags.
     *
     * This method is marked as [[nodiscard]] to indicate the compiler that
     * the return value should not be ignored when calling this method.
     *
     * @return The current logger_level_flags.
     */
    [[nodiscard]]
    logger_level_flags
    flags() const noexcept
    {
        return m_flags;
    }

    /**
     * @brief Sets the logging level flags.
     *
     * Allows changing the logging level flags for this logger instance.
     *
     * @param flags The new logger_level_flags to set.
     */
    void
    flags(logger_level_flags flags) noexcept
    {
        m_flags = flags;
    }

    /**
     * @brief Logs a message.
     *
     * Pure virtual function that logs a message with the given sender and level.
     * Derived classes need to implement this function to handle the logging.
     *
     * @param sender The sender of the log message.
     * @param level The severity level of the log message.
     * @param message The message to log.
     */
    virtual void
    log(const sender_type &sender, logger_level level, ustring_view message) = 0;

private:
    logger_level_flags m_flags; ///< Logging level flags.
};

} // namespace mi

#endif /* MI_BASE_LOGGER_HPP */
