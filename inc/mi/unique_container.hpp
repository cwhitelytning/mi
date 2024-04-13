/**
 * @file unique_container.hpp
 * @brief Contains the declaration of the unique_container template class.
 *
 * This file defines the unique_container class, which is a template for creating
 * containers that maintain ownership of their elements via unique pointers.
 *
 * It extends from the container class and implements non-copyable
 * semantics to prevent copying of the container.
 *
 * @note The ElementType parameter specifies the type
 *       of elements managed by the container.
 *
 *       ValueType defaults to a unique_ptr of ElementType,
 *       and ArrayType defaults to a std::vector of ValueType.
 */

#ifndef MI_UNIQUE_CONTAINER_HPP
#define MI_UNIQUE_CONTAINER_HPP

#include "container.hpp"
#include "noncopyable.hpp"
#include "null_pointer_exception.hpp"

namespace mi
{

/**
 * @class unique_container
 * @brief A container that stores unique pointers to objects,
 *        ensuring unique ownership and non-copyability.
 *
 * The unique_container extends the container class to provide
 * a container that can store elements with unique ownership semantics.
 *
 * It uses std::unique_ptr to manage the lifetime of the objects, ensuring that they are
 * automatically destroyed when the container is destroyed or when an element is removed.
 *
 * This container is non-copyable
 * to maintain the unique ownership of its elements.
 *
 * @tparam ElementType The type of the elements that this container will store.
 * @tparam ValueType The type of the value that the container will store,
 *                   defaulted to std::unique_ptr of ElementType.
 * @tparam ArrayType The underlying container type,
 *                   defaulted to std::vector of ValueType.
 */
template <typename ElementType,
          typename ValueType = std::unique_ptr<ElementType>,
          typename ArrayType = std::vector<ValueType>>

class unique_container : public container<ValueType, ArrayType>,
                         private mixin::noncopyable
{
public:
    /**
     * @typedef container_type
     * @brief Alias for the container template instantiated
     *        with specific ValueType and ArrayType.
     */
    using container_type = container<ValueType, ArrayType>;

    /**
     * @typedef size_type
     * @brief Alias for the size type as defined by container_type.
     */
    using size_type = typename container_type::size_type;

    /**
     * @typedef element_type
     * @brief Alias for the type of elements managed by this container.
     */
    using element_type = ElementType;

    /**
     * @typedef element_reference
     * @brief Alias for a reference to an element_type.
     *
     * This type alias is obtained from a set of type aliases which are assumed to define
     * various types related to element_type, including the reference type.
     */
    using element_reference = typename type_aliases<element_type>::reference;

    /**
     * @typedef element_const_reference
     * @brief Alias for a const reference to an element_type.
     *
     * This type alias is obtained from a set of type aliases which are assumed to define
     * various types related to element_type, including the const reference type.
     */
    using element_const_reference = typename type_aliases<element_type>::const_reference;

    /**
     * @brief Retrieves a reference to the element
     *        at the specified index without checking for validity.
     *
     * This function provides unchecked access
     * to the element at the specified index.
     *
     * It assumes that the index is valid and that the caller
     * is responsible for ensuring this.
     *
     * The function returns a reference to the element,
     * which can be modified.
     *
     * @pre The index must be within the bounds of the container. The behavior is
     * undefined if the index is invalid.
     *
     * @param index The index of the element to retrieve.
     * @return A reference to the element at the specified index.
     */
    constexpr element_reference
    get_unsafe(size_type index)
    {
        return *this->at(index);
    }

    /**
     * @brief Retrieves a const reference to the element
     *        at the specified index without checking for validity.
     *
     * This function provides unchecked access
     * to the element at the specified index.
     *
     * It assumes that the index is valid
     * and that the caller is responsible for ensuring this.
     *
     * The function returns a const reference to the element,
     * which cannot be modified.
     *
     * @pre The index must be within the bounds of the container.
     *      The behavior is undefined if the index is invalid.
     *
     * @param index The index of the element to retrieve.
     * @return A const reference to the element at the specified index.
     */
    [[nodiscard]]
    constexpr element_const_reference
    get_unsafe(size_type index) const
    {
        return *this->at(index);
    }

    /**
     * @brief Checks if the element at the specified index is a null value.
     *
     * This function compares the element at the specified index to nullptr to determine
     * if it is null. It is intended for use with containers that store pointer-like
     * objects.
     *
     * @param index The index of the element to check.
     * @return true if the element at the specified index is null,
     *         false otherwise.
     */
    [[nodiscard]]
    constexpr bool
    is_value_null(size_type index) const
    {
        return this->at(index) == nullptr;
    }

    /**
     * @brief Checks if the element at the specified index holds a non-null value.
     *
     * This function determines if the element at the specified index is not null,
     * implying that it holds a value. It is the logical negation of is_value_null.
     *
     * @param index The index of the element to check.
     * @return true if the element at the specified index holds a non-null value,
     *         false if it is null.
     */
    [[nodiscard]]
    constexpr bool
    has_value(size_type index) const
    {
        return !is_value_null(index);
    }

protected:
    /**
     * @brief Checks if the element at the specified index has an assigned value.
     *
     * This function verifies whether the element at the given index in the container
     * has been assigned a value. If no value has been assigned,
     * it throws a null_pointer_exception.
     *
     * @param index The index of the element to check.
     * @throws null_pointer_exception if the element at the specified index
     *                                has no assigned value.
     */
    constexpr void
    throw_if_value_equal_null(size_type index)
    {
        if (is_value_null(index))
        {
            throw null_pointer_exception("no value assigned (index: {})", index);
        }
    }

public:
    /**
     * @brief Retrieves a reference to the element
     *        at the specified index after checking for validity.
     *
     * This function ensures that the element at the given index has a value assigned.
     * If the element is valid, it returns a reference to the element.
     * If no value is assigned at the index, it throws an exception.
     *
     * @param index The index of the element to retrieve.
     * @return A reference to the element at the specified index.
     * @throws null_pointer_exception if no value is assigned at the specified index.
     */
    constexpr element_reference
    get(size_type index)
    {
        throw_if_value_equal_null(index);
        return get_unsafe(index);
    }

    /**
     * @brief Retrieves a const reference to the element
     *        at the specified index after checking for validity.
     *
     * This const version of the get function ensures that
     * the element at the given index has a value assigned.
     *
     * If the element is valid, it returns a const reference to the element.
     * If no value is assigned at the index, it throws an exception.
     *
     * @param index The index of the element to retrieve.
     * @return A const reference to the element at the specified index.
     * @throws null_pointer_exception if no value is assigned at the specified index.
     */
    constexpr element_const_reference
    get(size_type index) const
    {
        throw_if_value_equal_null(index);
        return get_unsafe(index);
    }

    /**
     * @brief Creates a unique object of type CustomType
     *        and adds it to the container.
     *
     * This function uses perfect forwarding to forward its arguments to the constructor
     * of CustomType. It constructs an object in place at the end of the container and
     * returns the index where the new object is inserted. This is typically used with
     * containers that manage objects through unique pointers.
     *
     * @tparam CustomType The type of the object to create.
     * @tparam Args Variadic template arguments deduced
     *              from the parameters passed to the function.
     * @param args Arguments to forward to the constructor of CustomType.
     * @return The index at which the new object is inserted into the container.
     */
    template <typename CustomType, typename... Args>
    size_type
    make_unique(Args &&...args)
    {
        auto index = this->size();
        this->push_back(std::make_unique<CustomType>(std::forward<Args>(args)...));
        return index;
    }

    /**
     * @brief Constructs an object of type CustomType
     *        in place within the container and returns a reference to it.
     *
     * This function template forwards its arguments to make_unique
     * to construct an object of CustomType, which is then added to the container.
     *
     * It then obtains and returns a reference
     * to the newly created object.
     *
     * This function is typically used when direct access
     * to the newly created object is required immediately after its creation.
     *
     * @tparam CustomType The type of the object to emplace.
     * @tparam Args Variadic template arguments deduced
     *              from the parameters passed to the function.
     * @param args Arguments to forward to the constructor of CustomType.
     * @return A reference to the newly emplaced object of type CustomType.
     */
    template <typename CustomType, typename... Args>
    CustomType &
    emplace_unique(Args &&...args)
    {
        const auto index = make_unique<CustomType>(std::forward<Args>(args)...);
        return static_cast<CustomType &>(this->get_unsafe(index));
    }

    /**
     * @brief Overloaded function call operator that provides
     *        unchecked access to the element at the specified index.
     *
     * This operator returns a reference to the element
     * at the given index, without performing any bounds checking.
     *
     * The caller is responsible for ensuring the index
     * is within the valid range of the container.
     *
     * @param index The index of the element to access.
     * @return A reference to the element at the given index.
     */
    element_reference
    operator()(size_type index)
    {
        return get_unsafe(index);
    }

    /**
     * @brief Overloaded function call operator that provides
     *        unchecked const access to the element at the specified index.
     *
     * This const-overloaded operator returns a const reference to the element
     * at the given index, without performing any bounds checking.
     *
     * The caller is responsible for ensuring the index
     * is within the valid range of the container.
     *
     * @param index The index of the element to access.
     * @return A const reference to the element at the given index.
     */
    element_const_reference
    operator()(size_type index) const
    {
        return get_unsafe(index);
    }
};

} // namespace mi

#endif /* MI_UNIQUE_CONTAINER_HPP */
