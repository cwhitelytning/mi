/**
 * @file logger_aware_class.hpp
 * @brief Declares the logger_aware_class which provides logging capabilities.
 */

#ifndef MI_LOGGER_AWARE_CLASS_HPP
#define MI_LOGGER_AWARE_CLASS_HPP

#include "anchor.hpp"
#include "noncopyable.hpp"
#include "nonmovable.hpp"

namespace mi::mixin
{

/**
 * @class logger_aware_class
 * @brief A class template that provides logging capabilities.
 *
 * This class is meant to be used as a base class that provides logging functionality
 * to derived classes. It inherits from noncopyable and nonmovable to prevent copy
 * and move operations, ensuring that the logger is unique to each instance.
 *
 * @tparam T The type of logger this class should use.
 *           This type must be compatible with the anchor template.
 */
template <typename T, typename AnchorType = anchor<T>>
class logger_aware_class : private noncopyable, private nonmovable
{
public:
    /**
     * @brief Returns a reference to the logger object.
     * @return A non-const reference to the logger instance.
     */
    auto &
    logger() noexcept
    {
        return m_logger;
    }

    /**
     * @brief Returns a constant reference to the logger object.
     * @return A const reference to the logger instance.
     */
    [[nodiscard]]
    const auto &
    logger() const noexcept
    {
        return m_logger;
    }

    /**
     * @brief Assigns a logger to be used by this object.
     *
     * Associates a logger object with this instance,
     * allowing logging operations
     * to be directed through the specified logger.
     *
     * This method enables dynamic switching of logger instances at runtime,
     * facilitating flexible logging strategies,
     * such as changing log levels or outputs on the fly.
     *
     * @tparam LoggerType The type of the logger object.
     *
     *                    This flexibility allows for the use of various logger
     *                    implementations, accommodating different logging frameworks
     *                    or custom logger classes that meet the interface or behavior
     *                    required by this class.
     *
     * @param logger A reference to an instance of LoggerType.
     *               This logger will be assigned to the current object and used for
     *               subsequent logging operations.
     *
     *               The method expects a non-const reference, permitting the logger
     *               itself to be mutable and possibly altered by the reset operation,
     *               depending on the specifics of the logger management implementation.
     *
     * @note The actual behavior of how the logger is reset
     *       or replaced is abstracted away by the m_logger.reset method.
     *
     *       Implementers should ensure that the reset method properly handles the
     *       transition from the current logger to the new one,
     *       including any necessary resource management or configuration updates.
     */
    virtual void
    logger(T &logger) noexcept
    {
        m_logger.emplace(logger);
    }

    /**
     * @brief Construct a new logger_aware_class object
     *        with optional parameters.
     *
     * This constructor forwards its arguments to the logger's constructor,
     * allowing for flexible initialization.
     *
     * @tparam Args Variable template arguments for logger construction.
     * @param args Arguments to forward to the logger's constructor.
     */
    template <typename... Args>
    explicit logger_aware_class(Args &&...args)
        : m_logger(std::forward<Args>(args)...)
    {
    }

private:
    /**
     * @brief The logger object.
     * @detail Stored as an anchor type for logger type flexibility.
     */
    AnchorType m_logger;
};

} // namespace mi::mixin

#endif /* MI_LOGGER_AWARE_CLASS_HPP */
