/**
 * @file extension.hpp
 * @brief This file contains the extension class that extends owner_aware_class.
 */

#ifndef MI_EXTENSION_HPP
#define MI_EXTENSION_HPP

#include "base_loader.hpp"
#include "owner_aware_class.hpp"
#include <boost/type_index.hpp>

namespace mi
{

/**
 * @class extension
 * @brief Extension class that inherits
 *        from owner_aware_class in a protected manner.
 *
 * It can be used as a base for creating classes that require knowledge about
 * their dynamic type or to provide type-specific functionalities beyond what
 * is available in owner_aware_class.
 *
 * The protection level of inheritance ensures the encapsulation of
 * owner_aware_class functionalities, making them accessible only within
 * extension or derived classes.
 */
class extension : protected owner_aware_class<const base_loader<extension>>
{
public:
    /**
     * @brief Inherits the constructor of owner_aware_class.
     */
    using owner_aware_class::owner_aware_class;

    /**
     * @brief Gets the classname of the instance.
     *
     * Uses boost::typeindex::type_id_runtime() to obtain the runtime type
     * information of the current instance, and then returns its pretty
     * formatted name as a standard string.
     *
     * This approach allows fetching the class name in a human-readable format,
     * aiding in debug or logging processes.
     *
     * @return std::string The pretty name of the class type.
     */
    [[nodiscard]]
    virtual inline std::string
    classname() const
    {
        return boost::typeindex::type_id_runtime(*this).pretty_name();
    }
};

} // namespace mi

#endif /* MI_EXTENSION_HPP */
