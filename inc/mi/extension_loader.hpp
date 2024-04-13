/**
 * @file extension_loader.hpp
 * @brief Defines the extension_loader class that manages extension objects.
 */

#ifndef MI_EXTENSION_LOADER_HPP
#define MI_EXTENSION_LOADER_HPP

#include "base_loader.hpp"
#include "extension.hpp"
#include "owner_aware_class.hpp"

namespace mi
{

/**
 * @class extension_loader
 * @brief Manages loading and attaching of extension objects.
 *
 * The extension_loader class inherits from loader<extension> to load extensions
 * and from extension to allow it to be used as an extension itself. It provides
 * a mechanism to attach custom extensions.
 */
class extension_loader : public base_loader<extension>, public extension
{
public:
    /**
     * @brief Inherits constructors from extension.
     */
    using extension::extension;

    /**
     * @brief Attaches a custom extension of type CustomType.
     *
     * This template method allows for the attachment of custom extensions
     * by forwarding its arguments to the constructor of the CustomType,
     * ensuring efficient argument passing.
     *
     * @tparam CustomType The type of the extension to attach.
     *                    This type must derive from extension.
     *
     * @tparam Args The types of the arguments to forward
     *              to the constructor of CustomType.
     *
     * @param args Arguments to forward to the constructor of the CustomType.
     * @return A reference to the attached extension of type CustomType.
     */
    template <typename CustomType, typename... Args>
    CustomType &
    attach_extension(Args &&...args)
    {
        return this->emplace_unique<CustomType>(*this, std::forward<Args>(args)...);
    }
};

} // namespace mi

#endif /* MI_EXTENSION_LOADER_HPP */
