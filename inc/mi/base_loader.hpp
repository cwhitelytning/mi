/**
 * @file base_loader.hpp
 * @brief Defines the loader template class.
 *
 * This file contains the definition of the loader class template which extends
 * the unique_container to provide specialized destruction behavior.
 */

#ifndef MI_BASE_LOADER_HPP
#define MI_BASE_LOADER_HPP

#include "filter.hpp"
#include "unique_container.hpp"

namespace mi
{

/**
 * @class base_loader
 * @brief A loader class that extends unique_container with custom destruction logic.
 *
 * The loader class template is a specialized unique_container with an overridden
 * destructor that ensures all contained elements are properly destroyed in reverse order.
 *
 * @tparam ValueType The type of elements stored in the loader container.
 */
template <typename ValueType>
class base_loader : public unique_container<ValueType>
{
public:
    /**
     * @brief Destructor that clears the container in reverse order.
     *
     * Destroys all of the elements in the loader container by resetting their unique
     * pointers in reverse order, making sure resources are released properly.
     */
    ~base_loader()
    {
        filter::iterate(this->rbegin(),
                        this->rend(),
                        [](auto &object)
                        {
                            object.reset();
                        });
    }
};

} // namespace mi

#endif /* MI_BASE_LOADER_HPP */
