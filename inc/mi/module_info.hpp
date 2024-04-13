/**
 * @file module_info.hpp
 * @brief Contains the definition of module info structure.
 */

#ifndef MI_MODULE_INFO_HPP
#define MI_MODULE_INFO_HPP

#include <string>

namespace mi
{

/**
 * @struct module_info
 * @brief Holds information about a module.
 *
 * This structure is used to store information about a module,
 * including its name, author, version, and a brief description.
 */
struct module_info
{
    const std::string author;      ///< The author of the module.
    const std::string name;        ///< The name of the module.
    const std::string version;     ///< The version of the module.
    const std::string description; ///< A brief description of the module.
};

} // namespace mi

#endif /* MI_MODULE_INFO_HPP */
