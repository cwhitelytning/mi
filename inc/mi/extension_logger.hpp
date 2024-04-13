/**
 * @file extension_logger.hpp
 * @brief Defines an alias for the base_logger template
 *        instantiated with the extension type.
 *
 * This header file creates an alias for a common use case of the base_logger template,
 * where the logger is specifically used for logging extension objects.
 *
 * It simplifies the usage of base_logger by providing
 * a predefined type  for this particular scenario.
 */

#ifndef MI_EXTENSION_LOGGER_HPP
#define MI_EXTENSION_LOGGER_HPP

#include "base_logger.hpp"

namespace mi
{

/**
 * @typedef extension_logger
 * @brief A type alias for base_logger instantiated
 *        with the extension type.
 *
 * extension_logger simplifies the creation of logger instances
 * for logging messages related to extension objects.
 *
 * It is an alias for the base_logger,
 * which is a template class expecting a type parameter that represents
 * the sender of log messages. In this case, the sender type is extension.
 */
using extension_logger = base_logger<const extension>;

} // namespace mi

#endif /* MI_EXTENSION_LOGGER_HPP */
