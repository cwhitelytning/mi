/**
 * @file dynamic_loader.hpp
 * @brief Defines the dynamic_loader class for dynamic module management.
 */

#ifndef MI_DYNAMIC_LOADER_HPP
#define MI_DYNAMIC_LOADER_HPP

#include "base_loader.hpp"
#include "dynamic_module.hpp"

namespace mi
{

/**
 * @class dynamic_loader
 * @brief Provides a mechanism to manage dynamic modules and their lifecycle.
 *
 * The dynamic_loader class extends the capabilities of the dynamic_module class
 * and implements the container interface for managing multiple dynamic modules.
 *
 * It offers functionality to load, unload, and manage dynamic modules at
 * runtime, allowing for flexible and efficient system customization
 * and extension.
 *
 * The class provides various methods to attach new modules, manage the loading
 * and unloading of modules to ensure correct initialization and cleanup.
 *
 * It is designed to work with any module class that fulfills the requirements
 * of being a dynamic module, making it versatile and adaptable
 * to different use cases.
 */
class dynamic_loader : public dynamic_module, public base_loader<dynamic_module>
{
protected:
    /**
     * @brief Loads all modules that are currently unloaded.
     *
     * This function iterates over each module in reverse order
     * and attempts to load it, if it is not already loaded.
     */
    virtual void
    load_modules();

    /**
     * @brief Unloads all modules that are currently loaded.
     *
     * This function iterates over each module in reverse order
     * and attempts to unload it, if it is not already unloaded.
     */
    virtual void
    unload_modules();

public:
    /**
     * @brief Inherits the constructor of dynamic_module.
     */
    using dynamic_module::dynamic_module;

    /**
     * @brief Attaches a module of type CustomType to the system.
     *
     * This function template creates and attaches a new module of type
     * CustomType by forwarding the provided arguments to the attach function.
     *
     * It is designed to be flexible and work with any module class
     * that fits the constraints of the attach function.
     *
     * The attach function is assumed to initialize the module,
     * register it within the system, and return a reference
     * to the newly attached module.
     *
     * @tparam CustomType The type of the module to attach.
     *
     *                    This type must be compatible with
     *                    the attach function's expectations.
     *
     * @tparam Args Variadic template arguments representing the types
     *              of arguments to be forwarded to the attach function.
     *
     * @param args Variadic arguments of any type that are perfectly
     *             forwarded to the attach function's parameters
     *             for module initialization.
     *
     * @return CustomType& A reference to the
     *         attached module of type CustomType.
     */
    template <typename CustomType, typename... Args>
    CustomType &
    attach_module(Args &&...args)
    {
        return this->emplace_unique<CustomType>(*this,
                                                logger(),
                                                std::forward<Args>(args)...);
    }

    /**
     * @brief Loads the dynamic module and then loads all unloaded modules.
     *
     * This is a higher level function that first calls the load function of the
     * dynamic_module and then proceeds to load all other modules that are unloaded.
     */
    void
    load() override;

    /**
     * @brief Unloads all loaded modules and then the dynamic module itself.
     *
     * This is a higher level function that first unloads all modules
     * that are currently loaded and then calls the unload function of the dynamic_module.
     */
    void
    unload() override;
};

} // namespace mi

#endif /* MI_DYNAMIC_LOADER_HPP */
