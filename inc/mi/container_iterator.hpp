/**
 * @file container_iterator.hpp
 * @brief Defines the container_iterator template class for the mi namespace.
 *
 * This file contains the definition of the container_iterator template class, which
 * is designed to wrap a standard iterator and provide additional functionalities
 * while maintaining compatibility with the standard iterator interface.
 */

#ifndef MI_CONTAINER_ITERATOR_HPP
#define MI_CONTAINER_ITERATOR_HPP

#include "type_aliases.hpp"
#include <iterator>

namespace mi
{

/**
 * @class container_iterator
 * @brief A wrapper iterator class that provides standard iterator functionality.
 *
 * container_iterator is a template class that acts as a wrapper around a standard
 * iterator to provide additional functionalities and interface consistency across
 * different iterator types. It is designed to work seamlessly with standard STL
 * containers.
 *
 * @tparam IteratorType The underlying iterator type that this class wraps.
 * @tparam ContainerType The type of the container that the iterator will iterate over.
 */
template <typename IteratorType, typename ContainerType>
class container_iterator
{
protected:
    using traits_type = std::iterator_traits<IteratorType>;

public:
    /**
     * @typedef iterator_type
     * @brief Alias for the type of iterator used by the container.
     */
    typedef IteratorType iterator_type;

    /**
     * @typedef container_type
     * @brief Alias for the type of the underlying container.
     */
    typedef ContainerType container_type;

    /**
     * @typedef iterator_category
     * @brief Alias for the category of the iterator.
     *
     * This type alias is derived from the traits_type and determines the iterator's
     * category, such as input_iterator_tag, output_iterator_tag, forward_iterator_tag,
     * bidirectional_iterator_tag, or random_access_iterator_tag.
     */
    typedef typename traits_type::iterator_category iterator_category;

    /**
     * @typedef value_type
     * @brief Alias for the type of the elements pointed to by the iterator.
     *
     * This type alias is derived from the traits_type and represents the type of the
     * elements that the container holds.
     */
    typedef typename traits_type::value_type value_type;

    /**
     * @typedef difference_type
     * @brief Alias for the type used to represent the difference between two iterators.
     *
     * This type alias is derived from the traits_type and is typically used to measure
     * the distance between two iterators.
     */
    typedef typename traits_type::difference_type difference_type;

    /**
     * @typedef reference
     * @brief Alias for the reference type to the value type.
     *
     * This type alias is derived from the traits_type and represents the type of a
     * reference to an element in the container.
     */
    typedef typename traits_type::reference reference;

    /**
     * @typedef pointer
     * @brief Alias for the pointer type to the value type.
     *
     * This type alias is derived from the traits_type and represents the type of a
     * pointer to an element in the container.
     */
    typedef typename traits_type::pointer pointer;

protected:
    iterator_type m_iterator;

public:
    /**
     * @brief Dereferences the iterator to access the value
     *        to which the iterator points (const version).
     *
     * This operator is the const version of the dereference operator.
     * It allows read-only access to the value at the iterator's current position.
     * The underlying base iterator is dereferenced to provide this access.
     *
     * @return A const reference to the value that the iterator currently points to.
     * @note This operation does not throw exceptions and is marked as noexcept.
     */
    constexpr virtual reference
    operator*() const noexcept
    {
        return *m_iterator;
    }

    /**
     * @brief Const member access operator to directly access
     *        the members of the element pointed to by the iterator.
     *
     * This const version of the member access operator provides read-only access to the
     * members of the value pointed to by the iterator. It is used when the iterator
     * itself is const-qualified, preventing modification of the targeted element.
     *
     * @return A const pointer to the current element that the iterator points to,
     *         allowing for member access.
     *
     * @note This operation is noexcept,
     *       meaning it is guaranteed not to throw an exception.
     */
    constexpr pointer
    operator->() const noexcept
    {
        return m_iterator;
    }

    /**
     * @brief Increments the iterator to point to the next element in the container.
     *
     * Advances the iterator to the next position within the container it is iterating
     * over. This operation is the pre-increment version, which increments the
     * iterator's position and then returns a reference
     * to the incremented iterator.
     *
     * This operation relies on the underlying iterator's operator++
     * to perform the increment.
     *
     * @return A reference to this iterator after it has been incremented.
     *
     * @note This operation is marked noexcept,
     *       indicating that it does not throw exceptions.
     *
     *       Care should be taken not to increment an iterator past the end of the
     *       container it iterates over, as this would result in undefined behavior.
     */
    constexpr container_iterator &
    operator++() noexcept
    {
        ++m_iterator;
        return *this;
    }

    /**
     * @brief Increments the iterator to point to the next element in the container,
     *        returning the previous value of the iterator.
     *
     * This is the postfix increment operator. It increases the iterator's position to the
     * next element in the container, but returns a copy of the iterator as it was before
     * being incremented. This allows the operation to be used in a broader range of
     * expressions while maintaining the expected behavior.
     *
     * @param unused An int parameter to differentiate between the postfix and prefix
     *               increment operators. It is not used in the operation.
     *
     * @return A copy of the iterator before it was incremented.
     *
     * @note This operation is marked as noexcept, indicating that it does not throw
     *       exceptions. However, incrementing past the end of the container is undefined
     *       behavior.
     */
    constexpr container_iterator
    operator++(int) noexcept
    {
        return container_iterator(m_iterator++);
    }

    /**
     * @brief Decrements the iterator to point to the previous element in the container.
     *
     * Moves the iterator to the previous position within the container it is iterating
     * over. This operation is the prefix decrement version, which decrements the
     * iterator's position and then returns a reference to the decremented iterator.
     *
     * @return A reference to this iterator after it has been decremented.
     *
     * @note This operation is marked noexcept, indicating that it does not throw
     *       exceptions. Decrementing an iterator before the beginning of the
     *       container results in undefined behavior.
     */
    constexpr container_iterator &
    operator--() noexcept
    {
        --m_iterator;
        return *this;
    }

    /**
     * @brief Decrements the iterator to point to the previous element in the container,
     * returning the previous value of the iterator.
     *
     * This is the postfix decrement operator. It decreases the iterator's position to
     * the previous element in the container, but returns a copy of the iterator as it
     * was before being decremented. This operation is useful when decrementing within
     * the context of an expression that requires the original value of the iterator.
     *
     * @param unused An int parameter to differentiate between the postfix and prefix
     *               decrement operators. It is not used in the operation.
     *
     * @return A copy of the iterator before it was decremented.
     *
     * @note This operation is marked as noexcept, indicating that it does not throw
     *       exceptions. However, decrementing past the beginning of the container
     *       is undefined behavior.
     */
    constexpr container_iterator
    operator--(int) noexcept
    {
        return container_iterator(m_iterator--);
    }

    /**
     * @brief Accesses the element at the given position relative to the current iterator.
     *
     * Provides access to the element at a specified offset from the current iterator
     * position, effectively adding n to the iterator's current position
     * and dereferencing it.
     *
     * This enables random access capabilities within the iterated sequence.
     *
     * @param n The offset from the current iterator position of the element to access.
     *          n can be positive or negative, allowing access to elements both ahead
     *          of and behind the current position.
     *
     * @return A reference to the element at the specified offset
     *         from the current iterator.
     *
     * @note This operation is noexcept.
     *
     *       However, accessing beyond the bounds
     *       of the container results in undefined behavior.
     */
    constexpr reference
    operator[](difference_type n) const noexcept
    {
        return m_iterator[n];
    }

    /**
     * @brief Advances the iterator by a specified number of positions.
     *
     * Increments the iterator's position by n elements within the container.
     * This operation modifies the current iterator, effectively advancing
     * it n steps forward in the sequence.
     *
     * @param n The number of elements to advance the iterator by.
     *          If n is negative, the siterator moves backwards.
     *
     * @return A reference to this iterator after being advanced.
     *
     * @note This operation is noexcept.
     *
     *       However, moving the iterator outside the bounds
     *       of the container results in undefined behavior.
     */
    constexpr container_iterator &
    operator+=(difference_type n) noexcept
    {
        m_iterator += n;
        return *this;
    }

    /**
     * @brief Returns a new iterator that is advanced
     *        by a specified number of positions from the current iterator.
     *
     * Creates and returns a new container_iterator that represents the position n
     * elements ahead of the current iterator's position. Unlike operator+=, this
     * operation does not modify the current iterator but returns a new one instead.
     *
     * @param n The number of elements to advance the new iterator by from the current
     *          position. n can be negative, resulting in an iterator that is
     *          positioned before the current one.
     *
     * @return A new container_iterator advanced by n positions
     *         from the current iterator.
     *
     * @note This operation is noexcept. Similar to operator+=,
     *       moving beyond the bounds of the container results in undefined behavior.
     */
    constexpr container_iterator
    operator+(difference_type n) const noexcept
    {
        return container_iterator(m_iterator + n);
    }

    /**
     * @brief Decrements the iterator's position
     *        by a specified number of positions.
     *
     * Modifies the current iterator by moving it backwards by n elements within the
     * container. This operation provides the ability to reverse iterate over the
     * sequence.
     *
     * @param n The number of elements to move the iterator backwards by.
     *          If n is positive, the iterator moves backwards;
     *          if n is negative, it moves forward.
     *
     * @return A reference to this iterator after being decremented.
     *
     * @note This operation is noexcept. However, decrementing the iterator beyond
     *       the beginning of the container, or moving it past the end,
     *       results in undefined behavior.
     */
    constexpr container_iterator &
    operator-=(difference_type n) noexcept
    {
        m_iterator -= n;
        return *this;
    }

    /**
     * @brief Returns a new iterator that is the result of decrementing
     *        the current iterator by a specified number of positions.
     *
     * Creates and returns a new container_iterator that represents the position n
     * elements behind the current iterator's position. This operation does not modify the
     * current iterator but returns a new one instead.
     *
     * @param n The number of elements to move the new iterator backwards by from the
     *          current position. If n is positive, the resulting iterator is positioned
     *          before the current one.
     *
     * @return A new container_iterator decremented by n positions
     *         from the current iterator.
     *
     * @note This operation is noexcept.
     *
     *       Moving beyond the bounds of the container, either before the first element
     *       or past the last, results in undefined behavior.
     */
    constexpr container_iterator
    operator-(difference_type n) const noexcept
    {
        return container_iterator(m_iterator - n);
    }

    /**
     * @brief Compares this container_iterator with another for equality.
     *
     * This operator determines if two container_iterators
     * are equal by comparing their underlying iterators.
     *
     * Two iterators are considered equal if they point to the same element
     * in the container or if both are at the same end position.
     *
     * @param other A constant reference to another container_iterator to compare with.
     * @return true if the underlying iterators are equal, otherwise false.
     */
    constexpr bool
    operator==(const container_iterator &other) const
    {
        return m_iterator == other.m_iterator;
    }

    /**
     * @brief Compares this container_iterator with another for inequality.
     *
     * This operator determines if two container_iterators
     * are not equal by comparing their underlying iterators.
     *
     * Two iterators are considered not equal if they point to different elements
     * in the container, or if only one is at the end position.
     *
     * @param other A constant reference to another container_iterator to compare with.
     * @return true if the underlying iterators are not equal, otherwise false.
     */
    constexpr bool
    operator!=(const container_iterator &other) const
    {
        return m_iterator != other.m_iterator;
    }

    /**
     * @brief Retrieves the base iterator.
     *
     * This member function returns a reference to the underlying iterator. It provides
     * read-only access to the base iterator, allowing operations or inspections that
     * depend on the specific iterator type.
     *
     * @return A constant reference to the underlying iterator_type, m_iterator.
     *
     * @note This operation is noexcept
     *       and does not modify the state of the container_iterator.
     */
    constexpr const iterator_type &
    base() const noexcept
    {
        return m_iterator;
    }

    /**
     * @brief Constructs a new container_iterator
     *        with a default-initialized internal iterator.
     *
     * This default constructor initializes the internal iterator (m_iterator) to its
     * default state. It essentially creates a container_iterator that is ready to be
     * assigned or initialized with a specific iterator position.
     *
     * @note This operation is noexcept.
     *
     *       The internal iterator is default-constructed,
     *       and the state of the created container_iterator
     *       depends on the default state of the iterator_type.
     */
    constexpr container_iterator() noexcept
        : m_iterator(iterator_type())
    {
    }

    /**
     * @brief Constructs a container_iterator
     *        using a specific underlying iterator_type.
     *
     * This constructor creates a container_iterator that wraps around a provided
     * iterator_type, effectively allowing the container_iterator to begin
     * iteration from the position specified by ref.
     *
     * @param ref A constant reference to an iterator_type object.
     *            The container_iterator will use this iterator as its starting position.
     *
     * @note This operation is marked as noexcept.
     *       It guarantees that the container_iterator will be initialized
     *       to wrap the provided iterator without the risk of throwing an exception.
     */
    constexpr explicit container_iterator(const iterator_type &iterator) noexcept
        : m_iterator(iterator)
    {
    }

    /**
     * @brief Type trait to check if a custom iterator type
     *        can be converted to the base iterator type.
     *
     * This utility type trait is used to enable template functions or constructors
     * only for those types that are convertible to the specified iterator_type
     * of this container_iterator. It leverages SFINAE to conditionally enable
     * certain behaviors based on the type compatibility.
     *
     * @tparam custom_iterator_type The custom iterator type to check
     *                              for convertibility to the base iterator_type.
     *
     * @note This trait can be used to restrict template instantiation to compatible
     *       iterator types, preventing compile-time errors and clarifying
     *       the intended use of templates.
     */
    template <typename custom_iterator_type>
    using convertible_from =
        std::enable_if_t<std::is_convertible_v<custom_iterator_type, iterator_type>>;

    /**
     * @brief Constructs a container_iterator
     *        from another container_iterator of a potentially different type.
     *
     * This constructor template allows constructing a container_iterator instance
     * from another container_iterator with a different underlying iterator_type,
     * given that the source iterator's type is convertible to the target iterator_type.
     *
     * This enables interoperability between container_iterator instances
     * that wrap compatible but different iterator types.
     *
     * @tparam custom_iterator_type The type of the iterator in the source
     *                              container_iterator, which must be convertible
     *                              to this iterator's iterator_type as determined
     *                              by the convertible_from type trait.
     *
     * @param ref A constant reference to the source container_iterator
     *            from which to construct this iterator.
     *
     *            The source iterator's base iterator
     *            will be used to initialize this iterator's base iterator.
     *
     * @note This operation is noexcept, assuming that the conversion between iterator
     *       types does not throw. It's designed to enable seamless conversion between
     *       compatible container_iterator types, enhancing the template's flexibility.
     */
    template <typename custom_iterator_type,
              typename = convertible_from<custom_iterator_type>>

    constexpr explicit container_iterator(
        const container_iterator<custom_iterator_type, container_type> &ref) noexcept
        : m_iterator(ref.base())
    {
    }
};

} // namespace mi

#endif /* MI_CONTAINER_ITERATOR_HPP */
