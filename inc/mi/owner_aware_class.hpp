/**
 * @file owner_aware_class.hpp
 * @brief A header file for the owner_aware_class within the mi namespace.
 */

#ifndef MI_OWNER_AWARE_CLASS_HPP
#define MI_OWNER_AWARE_CLASS_HPP

#include "anchor.hpp"
#include "noncopyable.hpp"
#include "nonmovable.hpp"

namespace mi::mixin
{

/**
 * @class owner_aware_class
 * @brief A class template that provides ownership semantics.
 *
 * The owner_aware_class encapsulates an owning object,
 * offering a strict ownership model while prohibiting copy
 * and move semantics to ensure the integrity and safety of ownership.
 *
 * This class is a component of a broader mechanism designed
 * to manage resources and enforce ownership policies
 * within complex systems.
 *
 * @tparam OwnerType The type of the owned object.
 * @tparam AnchorType A type used as an anchor for additional ownership mechanisms,
 *                    defaults to anchor<T>.
 *
 *                    This parameter allows customizing the ownership behavior,
 *                    for instance, facilitating unique ownership or supporting
 *                    shared ownership depending on the anchor's implementation.
 *
 * The class is part of an architecture that strictly forbids the copying and moving
 * of owning objects to prevent any unauthorized or accidental ownership transfers,
 * thereby enhancing the security and reliability of resource management.
 */
template <typename OwnerType, typename AnchorType = const anchor<OwnerType>>
class owner_aware_class : private noncopyable, private nonmovable
{
public:
    /**
     * @brief Gets a reference to the owner.
     * @return A reference to the owner object.
     */
    auto &
    owner() noexcept
    {
        return m_owner;
    }

    /**
     * @brief Gets a constant reference to the owner (const overload).
     * @return A constant reference to the owner object.
     */
    const auto &
    owner() const noexcept
    {
        return m_owner;
    }

    /**
     * @brief Constructs the owner_aware_class
     *        with parameters forwarded to the owner’s constructor.
     *
     * This constructor template allows for the creation of the owned object with
     * arbitrary arguments, forwarding them to the constructor of the owner_type.
     *
     * This provides flexibility in initializing
     * the owned object managed by this owner_aware_class.
     *
     * @tparam Args Variadic template parameter pack
     *              for constructor arguments of the owned object.
     *
     * @param args Arguments to be forwarded
     *             to the constructor of the owned object.
     */
    template <typename... Args>
    explicit owner_aware_class(Args &&...args)
        : m_owner(std::forward<Args>(args)...)
    {
    }

private:
    AnchorType m_owner; ///< The owner object, encapsulating the ownership.
};

} // namespace mi::mixin

#endif /* MI_OWNER_AWARE_CLASS_HPP */
