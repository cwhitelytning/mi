/**
 * @file base_logger.hpp
 * @brief Declaration of the base_logger class within the mi namespace.
 *
 * This file contains the base_logger class template which is a part of the
 * logging system. It provides the interface for logging messages with
 * different levels of importance.
 */

#ifndef MI_BASE_LOGGER_HPP
#define MI_BASE_LOGGER_HPP

#include "extension.hpp"
#include "logger_level_flags.hpp"
#include <string_view>

namespace mi
{

/**
 * @class base_logger
 * @brief Abstract base class for loggers.
 *
 * base_logger is a template class that defines the interface for logger
 * classes. It is inherited from the extension class. It provides methods to
 * get and set logger flags and requires the implementation of the log method.
 *
 * @tparam T The type of the sender that will be logged.
 */
template <typename T>
class base_logger : public extension
{
public:
    /**
     * @brief Constructs a new base logger object.
     *
     * @param owner The owner of this logger instance.
     * @param flags Initial logging level flags.
     *
     * @tparam OwnerType The type of the owner.
     */
    template <typename OwnerType>
    explicit base_logger(OwnerType &&owner, logger_level_flags flags)
        : extension(std::forward<OwnerType>(owner)),
          m_flags(flags)
    {
    }

    /**
     * @brief Gets the current logger level flags.
     * @return The current logger level flags.
     */
    [[nodiscard]]
    logger_level_flags
    flags() const noexcept
    {
        return m_flags;
    }

    /**
     * @brief Sets the logger level flags.
     * @param flags New logger level flags to be set.
     */
    void
    flags(logger_level_flags flags) noexcept
    {
        m_flags = flags;
    }

    /**
     * @brief Pure virtual function for logging a message.
     *
     * This function needs to be implemented to handle
     * the logging of messages with a specific logger level.
     *
     * @param sender The sender of the message.
     *               The type is defined by the template parameter T.
     * @param level The importance level of the message.
     * @param message The message to log.
     */
    virtual void
    log(const T &sender, logger_level level, ustring_view message) = 0;

private:
    logger_level_flags m_flags; ///< Flags indicating the logging level.
};

} // namespace mi

#endif /* MI_BASE_LOGGER_HPP */
