/**
 * @file extension_logger.hpp
 * @brief Type alias for base_logger specialized with const extension.
 *
 * This file provides a type alias for a base_logger that is specialized to work
 * with const extension objects. It simplifies the usage of base_logger for this
 * common use case within the mi namespace.
 */

#ifndef MI_EXTENSION_LOGGER_HPP
#define MI_EXTENSION_LOGGER_HPP

#include "base_logger.hpp"

namespace mi
{

/**
 * @typedef extension_logger
 * @brief Type alias for base_logger specialized for extension.
 *
 * extension_logger is a type alias that simplifies
 * the usage of base_logger when the sender type is a extension.
 *
 * It is intended to provide a more convenient syntax
 * for declaring loggers that are tied to extensions.
 */
using extension_logger = base_logger<const extension>;

} // namespace mi

#endif /* MI_EXTENSION_LOGGER_HPP */
