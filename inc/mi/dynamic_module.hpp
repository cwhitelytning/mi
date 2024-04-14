/**
 * @file dynamic_module.hpp
 * @brief Defines the dynamic_module class
 *        which integrates dynamic library loading with extension mechanisms.
 */

#ifndef MI_DYNAMIC_MODULE_HPP
#define MI_DYNAMIC_MODULE_HPP

#include "dynamic_library.hpp"
#include "extension_logger.hpp"
#include "logger_aware_class.hpp"
#include "module_info.hpp"

namespace mi
{

/**
 * @class dynamic_module
 * @brief A class that combines functionality
 *        from both dynamic_library and extension classes.
 *
 * This class is designed to manage dynamic modules, incorporating both loading
 * and unloading capabilities, and functionality for retrieving detailed
 * information about the module.
 */
class dynamic_module : public extension,
                       protected mixin::logger_aware_class<extension_logger>,
                       public dl::dynamic_library
{
public:
    /**
     * @brief Loads the dynamic module.
     *
     * This function overrides extension::load to provide specific
     * implementation for dynamic modules.
     *
     * It ensures the dynamic library
     * associated with this module is loaded appropriately.
     */
    void
    load() override;

    /**
     * @brief Unloads the dynamic module.
     *
     * Overrides extension::unload to offer a customized unload mechanism for
     * dynamic modules, ensuring the dynamic library associated with this module
     * is unloaded properly.
     */
    void
    unload() override;

    /**
     * @brief Retrieves module information from the dynamic library.
     *
     * This function serves as a proxy to access specific module information
     * by calling a predetermined function (on_module_info)
     * within the dynamic library.
     *
     * It leverages the call method to dynamically invoke on_module_info,
     * which is expected to return an instance or a reference to an module_info
     * structure containing the relevant information about the module.
     *
     * It's important to ensure that on_module_info adheres to the expected
     * signature and behavior, as it directly affects the outcome and
     * reliability of this method.
     *
     * @note The function relies on the dynamic calling capability provided by
     *       call<const module_info &()>. Hence, the existence and correct
     *       signature of on_module_info within the library are critical.
     *
     * @return A constant reference to a module_info instance,
     *         representing the module's information.
     *
     * @throw dynamic_library_error If the dynamic library is not loaded or the
     *                              on_module_info function is not found within
     *                              the library.
     *
     *                              These exceptions are propagated
     *                              from the call function.
     *
     * @see call for more details on how functions
     *           are dynamically called within the library.
     */
    [[nodiscard]]
    virtual const module_info &
    info() const;

    /**
     * @brief Returns the directory path of the loaded dynamic module.
     *
     * This method computes the parent directory of the module path.
     * It is useful for situations where you need to manipulate
     * or inspect the directory containing the dynamically loaded module.
     *
     * @return A path_t object representing the directory containing
     *         the module.
     *
     *         This object is of the type dynamic_library::path_t,
     *         indicating its compatibility with file system path
     *         operations defined elsewhere in the dynamic_library.
     */
    [[nodiscard]]
    fs::path_t
    root_path() const;

    /**
     * @brief Returns the path to the configuration directory
     *        associated with the loaded dynamic module.
     *
     * This method calculates the path to the configuration directory by
     * appending "config" to the parent directory of the module's path.
     *
     * It is particularly useful for scenarios where accessing configuration
     * files, specifically organized in a dedicated "config" directory,
     * adjacent to the module's directory, is required.
     *
     * @return A path_t object representing the path
     *         to the configuration directory for the module.
     *
     *         This object is of the type dynamic_library::path_t,
     *         indicating its compatibility with filesystem path operations
     *         defined elsewhere in the dynamic_library.
     *
     *         The returned path ensures direct access to the module's
     *         configuration files stored within a "config" folder located
     *         in the same directory hierarchy as the module itself.
     */
    [[nodiscard]]
    fs::path_t
    config_dir() const;

    /**
     * @brief Retrieves the class name of the current instance.
     *
     * This function utilizes Boost's type_index library to demangle and
     * retrieve the pretty name of the type of the current instance at runtime.
     *
     * @return A string representing the class name of the instance.
     *
     * @note This function is declared as virtual to allow overrides
     *       in derived classes, ensuring that the correct type name
     *       is retrieved in a polymorphic hierarchy.
     */
    [[nodiscard]]
    std::string
    classname() const override;

    /**
     * @brief Constructs a dynamic_module object associated with a specified owner,
     *        logger, and library path.
     *
     * This constructor initializes a dynamic_module with an owner,
     * a logger instance, and a path to the dynamic library.
     *
     * The dynamic_module class extends from the extension
     * and logger_aware_class to inherit ownership and logging capabilities,
     * and also encapsulates a dynamic_library representing the loaded library
     * at the specified path.
     *
     * @tparam OwnerType The type of the owner of the module.
     *
     *                   This template parameter ensures that
     *                   the dynamic_module is associated with an owner,
     *                   enforcing a relationship or ownership model.
     *
     * @tparam LoggerType The type of the logger to be used for logging purposes.
     *                    This template parameter allows the dynamic_module to utilize
     *                    an external logger.
     *
     * @param owner A reference to the owner entity,
     *              which the dynamic_module is associated with.
     *
     * @param logger A reference to the logger,
     *               which the dynamic_module will use for logging operations.
     *
     *               The logger is forwarded
     *               to the logger_aware_class base class constructor.
     *
     * @param path The file system path to the dynamic library for the module.
     */
    template <typename OwnerType, typename LoggerType>
    dynamic_module(OwnerType &&owner, LoggerType logger, const fs::path_t &path)
        : extension(std::forward<OwnerType>(owner)),
          logger_aware_class(std::forward<LoggerType>(logger)),
          dynamic_library(path)
    {
    }
};

} // namespace mi

#endif /* MI_DYNAMIC_MODULE_HPP */
