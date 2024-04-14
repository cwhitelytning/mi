/**
 * @file container.hpp
 * @brief This file defines the `container` class which provides a template container
 *        class with custom value and array types.
 *
 * @details The container class provides methods to access and modify its elements
 *          with bounds checking, and methods to query its size and emptiness.
 *          It uses an internal array representation to store its elements.
 */

#ifndef MI_CONTAINER_HPP
#define MI_CONTAINER_HPP

#include "container_iterator.hpp"
#include "range_error.hpp"
#include "type_aliases.hpp"
#include <memory>
#include <vector>

namespace mi
{

/**
 * @class container
 * @brief A template class that encapsulates a dynamic array structure.
 *
 * @details The container class template is designed
 *          to manage a collection of elements in a contiguous storage location.
 *
 * The class provides a variety of member functions to access and modify its elements,
 * including checked and unchecked element access, size retrieval, and iterators
 * for traversal. It supports standard operations such as checking for emptiness,
 * accessing the back element, and bounds-checked access with at().
 *
 * The class is designed with type aliases to be flexible
 * with the types of elements and the underlying array representation it uses.
 *
 * @tparam ValueType The type of elements stored in the container.
 * @tparam ArrayType The type of underlying array structure used to store the elements,
 *                   defaults to std::vector.
 *
 * @note This class assumes that the provided ArrayType supports size_type,
 *       begin(), end(), and other typical container member functions.
 *
 * The class uses SFINAE (Substitution Failure Is Not An Error) principles for template
 * type checks, ensuring that operations are performed safely with respect to the types
 * involved.
 *
 * Exception safety is also a consideration, with functions marked noexcept where
 * applicable, and exceptions thrown in cases where operations like bounds-checked
 * access fail.
 *
 * Iterators and const_iterators are provided for forward and reverse traversal,
 * allowing the container to be used with standard algorithms and iterator-based loops.
 *
 * The container class is a foundational part of the 'mi' namespace and can be extended
 * or used as a base for more complex container implementations.
 */
template <typename ValueType, typename ArrayType = std::vector<ValueType>>
class container
{
public:
    /**
     * @brief Type alias for the value type.
     *
     * Defines a member type that enables
     * the representation of the value type used by the container.
     *
     * This type alias is used throughout the container class to refer to the elements
     * that the container holds, providing a convenient shorthand for the type of these
     * elements.
     *
     * @tparam ValueType The type of elements in the container.
     */
    using value_type = ValueType;

    /**
     * @brief Type alias for a mutable reference
     *        to an element of type ValueType.
     *
     * reference is obtained from a set of type aliases which is assumed
     * to define various types related to ValueType,
     * including the reference type.
     *
     * It is used to provide a modifiable alias to the stored element type
     * within a container or other data structures.
     */
    using reference = typename type_aliases<value_type>::reference;

    /**
     * @brief Type alias for a non-mutable (const) reference
     *        to an element of type ValueType.
     *
     * const_reference is obtained from a set of type aliases which
     * is assumed to define various types related to ValueType,
     * including the const reference type.
     *
     * It is used to provide a non-modifiable alias to the stored element type
     * within a container or other data structures,
     * ensuring the element cannot be changed.
     */
    using const_reference = typename type_aliases<value_type>::const_reference;

    /**
     * @brief Type alias for the array type used
     *        in the container or data structure.
     *
     * array_type refers to the internal storage container type
     * used to manage collections of elements.
     *
     * This could be any container-like structure
     * that supports size_type definition.
     */
    using array_type = ArrayType;

    /**
     * @brief Type alias for an unsigned integral type that can represent
     *        the size of the largest object in the allocation model.
     *
     * size_type is typically used for array indexing and loop counting,
     * obtained from the array_type's own definition of size_type.
     *
     * It ensures that the size type is consistent
     * with that used by the internal array structure.
     */
    using size_type = typename array_type::size_type;

    /**
     * @brief Type alias for a pointer
     *        to an element of type ValueType.
     *
     * pointer is defined within a set of type aliases which typically
     * includes various pointer types related to ValueType.
     *
     * This type alias is used to provide a modifiable pointer to the elements managed by
     * a container or other data structures, allowing for direct element manipulation.
     */
    using pointer = typename type_aliases<ValueType>::pointer;

    /**
     * @brief Type alias for a const pointer
     *        to an element of type ValueType.
     *
     * const_pointer is defined within a set of type aliases
     * which typically includes various pointer types related to ValueType.
     *
     * This type alias is used to provide a non-modifiable (const) pointer to the elements
     * managed by a container or other data structures, preventing modification of the
     * pointed-to element.
     */
    using const_pointer = typename type_aliases<ValueType>::const_pointer;

    /**
     * @brief Type alias for an iterator over a container.
     *
     * iterator is defined as a container_iterator templated
     * with pointer and the container itself.
     *
     * This type alias is used to traverse the elements in a container
     * in a forward direction, providing modifiable access to each element.
     */
    using iterator = container_iterator<pointer, container>;

    /**
     * @brief Type alias for a const iterator over a container.
     *
     * const_iterator is defined as a container_iterator templated
     * with `const_pointer` and the const container.
     *
     * This type alias is used to traverse the elements in a container
     * in a forward direction without modifying the elements.
     */
    using const_iterator = container_iterator<const_pointer, container>;

    /**
     * @brief Type alias for a reverse iterator over a container.
     *
     * reverse_iterator is a standard reverse iterator templated
     * with the iterator.
     *
     * This provides a way to traverse the container in reverse order,
     * effectively iterating from the end to the beginning of the container,
     * with modifiable access to each element.
     */
    using reverse_iterator = std::reverse_iterator<iterator>;

    /**
     * @brief Type alias for a const reverse iterator over a container.
     *
     * const_reverse_iterator is a standard reverse iterator templated
     * with the const_iterator.
     *
     * This provides a way to traverse the container in reverse order,
     * effectively iterating from the end to the beginning of the container,
     * without modifying the elements.
     */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    array_type m_values;

public:
    /**
     * @brief Retrieves a constant reference to the element
     *        at the specified index without bounds checking.
     *
     * This constexpr function returns a const reference to the element at the given index
     * in the container. It is marked noexcept because it does not throw exceptions. This
     * function does not perform bounds checking, and accessing an out-of-bounds index
     * will result in undefined behavior.
     *
     * @param index The index of the element to retrieve.
     * @return A const reference to the element at the specified index in the container.
     */
    constexpr const_reference
    at_unsafe(size_type index) const noexcept
    {
        return m_values[index];
    }

    /**
     * @brief Retrieves a reference to the element
     *        at the specified index without bounds checking.
     *
     * This constexpr function returns a reference to the element at the given index in
     * the container. It is marked noexcept because it does not throw exceptions. This
     * function does not perform bounds checking, and accessing an out-of-bounds index
     * will result in undefined behavior.
     *
     * @param index The index of the element to retrieve.
     * @return A reference to the element at the specified index in the container.
     */
    constexpr reference
    at_unsafe(size_type index) noexcept
    {
        return m_values[index];
    }

    /**
     * @brief Gets the number of elements in the container.
     *
     * This function returns the number of elements that
     * the container has currently allocated space for.
     *
     * @return The total number of elements in the container.
     */
    [[nodiscard]]
    constexpr size_type
    size() const noexcept
    {
        return m_values.size();
    }

    /**
     * @brief Checks if the container has no elements.
     *
     * This function returns a boolean value indicating whether
     * the container is empty (i.e., contains no elements).
     *
     * @return true if the container is empty, false otherwise.
     */
    [[nodiscard]]
    constexpr bool
    empty() const noexcept
    {
        return m_values.empty();
    }

protected:
    /**
     * @brief Retrieves the raw pointer from a pointer-like object
     *        if the container is not empty.
     *
     * This function template returns the raw pointer to the element_type as pointed
     * to by ptr. If the container is empty, it returns a nullptr instead.
     *
     * This is useful for obtaining a raw pointer from various smart pointer types
     * or pointer-like objects within a non-empty container.
     *
     * @tparam PointerType The type of the pointer-like object.
     *                     It must satisfy the requirements of PointerTraits.
     * @param ptr A pointer-like object of type PointerType
     *            from which the raw pointer is obtained.
     * @return The raw pointer to the element_type pointed
     *         to by ptr if the container is not empty; otherwise, nullptr.
     */
    template <typename PointerType>
    constexpr typename std::pointer_traits<PointerType>::element_type *
    data_raw_pointer(PointerType ptr) const
    {
        return empty() ? nullptr : std::to_address(ptr);
    }

public:
    /**
     * @brief Obtains a raw pointer to the underlying data.
     *
     * This function returns a pointer to the container's underlying data structure.
     * If the container is empty, it returns nullptr.
     *
     * It provides raw access to the data, which can be useful for interfacing with APIs
     * that require raw pointers. This function is marked constexpr indicating that it
     * can be evaluated at compile time, and noexcept meaning it does not throw any
     * exceptions.
     *
     * @return A pointer to the underlying data of the container,
     *         or nullptr if the container is empty.
     */
    [[nodiscard]]
    constexpr pointer
    data() noexcept
    {
        return data_raw_pointer(m_values.data());
    }

    /**
     * @brief Obtains a const raw pointer to the underlying data.
     *
     * This function returns a const pointer to the container's underlying data structure.
     * If the container is empty, it returns nullptr.
     *
     * It provides raw access to the data, which can be useful for reading the container's
     * contents without modifying them. This function is marked constexpr indicating that
     * it can be evaluated at compile time, and noexcept meaning it does not throw any
     * exceptions.
     *
     * @return A const pointer to the underlying data of the container,
     *         or nullptr if the container is empty.
     */
    [[nodiscard]]
    constexpr const_pointer
    data() const noexcept
    {
        return data_raw_pointer(m_values.data());
    }

    /**
     * @brief Obtains an iterator
     *        to the first element of the container.
     *
     * This function returns an iterator pointing to the first element in the container.
     * If the container is empty, the returned iterator will be equal to the end iterator.
     *
     * This function is marked as constexpr, indicating that it can be evaluated
     * at compile time, and noexcept, meaning it does not throw any exceptions.
     *
     * @return An iterator to the beginning of the container.
     */
    constexpr iterator
    begin() noexcept
    {
        return iterator(data());
    }

    /**
     * @brief Obtains a const_iterator
     *        to the first element of the container.
     *
     * This function returns a const_iterator pointing to the first element in
     * the container. If the container is empty, the returned const_iterator
     * will be equal to the end const_iterator.
     *
     * This function is marked as constexpr, indicating that it can be evaluated
     * at compile time, and noexcept, meaning it does not throw any exceptions.
     *
     * @return A const_iterator to the beginning of the container.
     */
    constexpr const_iterator
    begin() const noexcept
    {
        return const_iterator(data());
    }

    /**
     * @brief Obtains an iterator
     *        to the element following the last element of the container.
     *
     * This function returns an iterator to the element following the last element of the
     * container, which is the end iterator. This iterator acts as a placeholder;
     * attempting to access it will result in undefined behavior.
     *
     * This function is marked as constexpr, indicating that it can be evaluated
     * at compile time, and noexcept, meaning it does not throw any exceptions.
     *
     * @return An iterator to the end of the container.
     */
    constexpr iterator
    end() noexcept
    {
        return iterator(data() + size());
    }

    /**
     * @brief Obtains a const_iterator
     *        to the element following the last element of the container.
     *
     * This function returns a const_iterator to the element following the last element
     * of the container, which is the end const_iterator. This iterator acts as a
     * placeholder; attempting to access it will result in undefined behavior.
     *
     * This function is marked as constexpr, indicating that it can be evaluated
     * at compile time, and noexcept, meaning it does not throw any exceptions.
     *
     * @return A const_iterator to the end of the container.
     */
    constexpr const_iterator
    end() const noexcept
    {
        return const_iterator(data() + size());
    }

    /**
     * @brief Obtains a reverse iterator
     *        to the first element of the reversed container.
     *
     * This function returns a reverse iterator pointing to the first element of the
     * container when traversed in reverse (which is the last element of the container
     * when traversed forward). If the container is empty, the returned reverse iterator
     * will be equal to rend().
     *
     * This function is marked as constexpr, indicating that it can be evaluated
     * at compile time, and noexcept, meaning it does not throw any exceptions.
     *
     * @return A reverse iterator to the beginning of the reversed container.
     */
    constexpr reverse_iterator
    rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    /**
     * @brief Obtains a const reverse iterator
     *        to the first element of the reversed container.
     *
     * This function returns a const reverse iterator pointing to the first element of the
     * container when traversed in reverse (which is the last element of the container
     * when traversed forward). If the container is empty, the returned const reverse
     * iterator will be equal to rend().
     *
     * This function is marked as constexpr, indicating that it can be evaluated
     * at compile time, and noexcept, meaning it does not throw any exceptions.
     *
     * @return A const reverse iterator to the beginning of the reversed container.
     */
    constexpr const_reverse_iterator
    rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    /**
     * @brief Obtains a reverse iterator
     *        to the element following the last element of the reversed container.
     *
     * This function returns a reverse iterator that points to the element following the
     * last element in the reversed container, which corresponds to the element preceding
     * the first element in the non-reversed container. This is often used as the end
     * marker in a reverse iteration loop. The container must not be empty when calling
     * this function.
     *
     * It is marked as constexpr, indicating that it can be evaluated at compile time,
     * and noexcept, meaning it does not throw any exceptions.
     *
     * @return A reverse iterator to the end of the reversed container.
     */
    constexpr reverse_iterator
    rend() noexcept
    {
        return reverse_iterator(begin());
    }

    /**
     * @brief Obtains a const reverse iterator
     *        to the element following the last element of the reversed container.
     *
     * This function returns a const reverse iterator that points to the element following
     * the last element in the reversed container, which corresponds to the element
     * preceding the first element in the non-reversed container.
     *
     * This is often used as the end marker in a reverse iteration loop.
     * The container must not be empty when calling this function.
     *
     * It is marked as constexpr, indicating that it can be evaluated at compile time,
     * and noexcept, meaning it does not throw any exceptions.
     *
     * @return A const reverse iterator to the end of the reversed container.
     */
    constexpr const_reverse_iterator
    rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    /**
     * @brief Checks whether an element exists
     *        at the specified index in the container.
     *
     * This function checks if the given index is within the bounds of the container.
     * The function is constexpr, meaning it can be evaluated at compile time,
     * and noexcept, indicating that it does not throw any exceptions.
     *
     * The [[nodiscard]] attribute prompts the caller to handle the returned value,
     * as it contains important information regarding the existence of an element
     * at the specified index.
     *
     * @param index The index to check for the existence of an element.
     * @return true if an element exists at the specified index, false otherwise.
     *
     * @note This function assumes that the index is zero-based
     *       and that size() returns the number of elements in the container.
     */
    [[nodiscard]]
    constexpr bool
    exists(size_type index) const noexcept
    {
        return index < size();
    }

    /**
     * @brief Accesses the element at the specified index
     *        with bounds checking.
     *
     * This function provides safe access to the elements of the container
     * by checking if the specified index is within the bounds of the container.
     *
     * If the index is valid, it returns a reference to the element at that index.
     * If the index is out of bounds, it throws an out_of_range_exception.
     *
     * This function is constexpr, meaning it can be evaluated
     * at compile time if the index is a compile-time constant.
     *
     * @param index The index of the element to access.
     * @return A reference to the element at the specified index in the container.
     * @throws out_of_range_exception if the index is out of bounds.
     */
    constexpr reference
    at(size_type index)
    {
        if (exists(index))
        {
            return at_unsafe(index);
        }
        throw range_error("index is out of range (index: {})", index);
    }

    /**
     * @brief Accesses the element at the specified index
     *        with bounds checking, const version.
     *
     * This function is the const version of at(size_type index),
     * providing safe access to the elements of the container by
     * checking if the specified index is within the bounds of the container.
     *
     * If the index is valid, it returns a const reference to the element at that index.
     * If the index is out of bounds, it throws an out_of_range_exception.
     *
     * This function is constexpr, meaning it can be evaluated
     * at compile time if the index is a compile-time constant.
     *
     * @param index The index of the element to access.
     * @return A const reference to the element at the specified index in the container.
     * @throws out_of_range_exception if the index is out of bounds.
     */
    constexpr const_reference
    at(size_type index) const
    {
        if (exists(index))
        {
            return at_unsafe(index);
        }
        throw range_error("index is out of range (index: {})", index);
    }

    /**
     * @brief Adds a new element to the end of the container.
     *
     * This function will append a copy of the given element to the end of the container.
     * The element is copied using the container's element type copy constructor.
     *
     * @param value A reference to the element to be copied
     *              and added to the container.
     */
    void
    push_back(const_reference value)
    {
        m_values.push_back(value);
    }

    /**
     * @brief Adds a new element to the end of the container by moving it.
     *
     * This function will append the given element to the end of the container by moving
     * it, avoiding a copy for efficiency. The element is moved using the container's
     * element type move constructor.
     *
     * @param value An rvalue reference to the element to be moved
     *              and added to the container.
     */
    void
    push_back(value_type &&value)
    {
        m_values.push_back(std::move(value));
    }

    /**
     * @brief Overloaded subscript operator to provide unchecked access
     *        to container elements.
     *
     * This operator provides unchecked access to the element at the given index.
     * It is equivalent to calling at_unsafe and does not perform bounds checking.
     * Accessing out-of-bounds elements will result in undefined behavior.
     *
     * @param index Index of the element to access.
     * @return A reference to the unique pointer at the specified index.
     */
    constexpr reference
    operator[](size_type index) noexcept
    {
        return at_unsafe(index);
    }

    /**
     * @brief Overloaded subscript operator to provide unchecked const access
     *        to container elements.
     *
     * This const-overloaded operator provides unchecked access to the element at the
     * given index. It is equivalent to calling at_unsafe and does not perform bounds
     * checking. Accessing out-of-bounds elements will result in undefined behavior.
     *
     * @param index Index of the element to access.
     * @return A const reference to the unique pointer at the specified index.
     */
    constexpr const_reference
    operator[](size_type index) const noexcept
    {
        return at_unsafe(index);
    }

    /**
     * @brief Copy assignment operator that assigns the contents
     *        of another container to this container.
     *
     * If the other container is the same as this container, no action is taken.
     * Otherwise, the contents of this container are replaced
     * with a copy of the contents of the other container.
     *
     * @param other A reference to the container to copy from.
     * @return A reference to this container.
     */
    constexpr container &
    operator=(const container &other)
    {
        if (this != &other)
        {
            m_values = other.m_values;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator that moves the contents
     *        of another container into this container.
     *
     * If the other container is the same as this container, no action is taken.
     * Otherwise, the contents of this container are replaced with the contents
     * of the other container, which is left in an unspecified but valid state.
     *
     * @param other An rvalue reference to the container to move from.
     * @return A reference to this container.
     */
    constexpr container &
    operator=(container &&other) noexcept
    {
        if (this != &other)
        {
            m_values = std::move(other.m_values);
        }
        return *this;
    }

    /**
     * @brief Equality comparison operator that checks if two containers are equal.
     *
     * Two containers are considered equal if their respective elements are equal.
     * This operator performs an element-wise comparison of the containers.
     *
     * @param other A reference to the container to compare with.
     * @return true if the containers are equal, false otherwise.
     */
    constexpr bool
    operator==(const container &other) const
    {
        return m_values == other.m_values;
    }

    /**
     * @brief Inequality comparison operator that checks if two containers are not equal.
     *
     * Two containers are considered not equal if at least one pair of their respective
     * elements is not equal. This operator performs an element-wise comparison of the
     * containers.
     *
     * @param other A reference to the container to compare with.
     * @return true if the containers are not equal, false otherwise.
     */
    constexpr bool
    operator!=(const container &other) const
    {
        return m_values != other.m_values;
    }

    /**
     * @brief Default constructor
     *        that initializes an empty container.
     *
     * Constructs an empty container with no elements.
     * This is the default constructor.
     */
    container() = default;

    /**
     * @brief Constructs the container
     *        with a specified number of default-inserted elements.
     *
     * @param size The number of default-inserted elements the container should contain.
     */
    explicit container(size_t size)
        : m_values(size)
    {
    }

    /**
     * @brief Constructs the container with a specified number of elements,
     *        each initialized to a given value.
     *
     * @param size The number of elements to construct.
     * @param value The value to initialize each element of the container with.
     */
    container(size_t size, const_reference value)
        : m_values(size, value)
    {
    }

    /**
     * @brief Copy constructor that initializes
     *        the container with the contents of another container.
     *
     * @param other A reference to the container from which to copy the elements.
     */
    container(const container &other)
        : m_values(other.m_values)
    {
    }

    /**
     * @brief Move constructor that initializes the container with the contents
     *        of another container, which is left in an unspecified but valid state.
     *
     * @param other An rvalue reference to the container to be moved.
     */
    container(container &&other) noexcept
        : m_values(std::move(other.m_values))
    {
    }

    /**
     * @brief Constructs the container with the contents of an initializer list.
     * @param list An initializer_list object to initialize
     *             the elements of the container with.
     */
    container(std::initializer_list<ValueType> list)
        : m_values(list)
    {
    }
};

} // namespace mi

#endif /* MI_CONTAINER_HPP */
