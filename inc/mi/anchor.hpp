/**
 * @file anchor.hpp
 * @brief A header file for the Anchor class within the mi namespace.
 */

#ifndef MI_ANCHOR_HPP
#define MI_ANCHOR_HPP

#include "anchor_exception.hpp"
#include "builtin.hpp"
#include "type_aliases.hpp"

namespace mi
{

/**
 * @class anchor
 * @brief Manages a pointer to provide memory management and utility functions.
 *
 * The anchor class template manages a pointer, often to dynamically allocated
 * memory, providing a mechanism to ensure proper resource management and
 * convenience functions to handle the pointer more safely and intuitively.
 *
 * @tparam T The type of object the anchor is managing.
 */
template <typename T>
class anchor final
{
public:
    /// Alias for a reference to the managed type.
    using reference = typename type_aliases<T>::reference;

    /// Alias for a constant reference to the managed type.
    using const_reference = typename type_aliases<T>::const_reference;

    /// Alias for a pointer to the managed type.
    using pointer = typename type_aliases<T>::pointer;

    /// Alias for a constant pointer to the managed type.
    using const_pointer = typename type_aliases<T>::const_pointer;

    /**
     * @brief Retrieves the stored pointer.
     * @return A pointer to the managed object.
     */
    pointer
    ptr() noexcept
    {
        return m_ptr;
    }

    /**
     * @brief Retrieves the stored pointer (constant overload).
     * @return A constant pointer to the managed object.
     */
    const_pointer
    ptr() const noexcept
    {
        return m_ptr;
    }

    /**
     * @brief Checks if the anchor manages no object.
     * @return True if the stored pointer is null, false otherwise.
     */
    [[nodiscard]]
    bool
    empty() const noexcept
    {
        return ptr() == nullptr;
    }

    /**
     * @brief Checks if the anchor has a reference to an object.
     * @return true if the anchor has a reference to an object, false if it is empty.
     */
    [[nodiscard]]
    bool
    has_reference() const noexcept
    {
        return !empty();
    }

    /**
     * @brief Sets the managed pointer to a new value.
     * @param ptr The new pointer to manage.
     */
    void
    emplace(pointer ptr) noexcept
    {
        m_ptr = ptr;
    }

    /**
     * @brief Assigns a reference, effectively managing the reference's address.
     * @param ref The reference to manage.
     */
    void
    emplace(reference ref) noexcept
    {
        emplace(&ref);
    }

    /**
     * @brief Resets the managed object pointer, effectively making the anchor empty.
     */
    void
    reset() noexcept
    {
        emplace(nullptr);
    }

    /**
     * @brief Obtains a reference to the managed object.
     * @return A reference to the managed object.
     * @throws anchor_exception if the managed pointer is null.
     */
    reference
    ref()
    {
        if (has_reference())
        {
            return *ptr();
        }
        throw anchor_exception("reference is not engaged");
    }

    /**
     * @brief Obtains a reference to the managed object (constant overload).
     * @return A constant reference to the managed object.
     */
    [[nodiscard]]
    const_reference
    ref() const
    {
        return const_cast<anchor *>(this)->ref();
    }

    /**
     * @brief Constructs an anchor to manage a given pointer.
     * @param ptr The pointer to manage.
     */
    explicit anchor(pointer ptr)
        : m_ptr(ptr)
    {
    }

    /**
     * @brief Default constructor.
     * @brief Initializes the managed pointer to nullptr.
     */
    anchor()
        : anchor(nullptr)
    {
    }

    /**
     * @brief Move constructor.
     *
     * Transfers ownership of the resource managed by other to *this object. The
     * other object is left in a valid but unspecified state afterwards, which
     * means it no longer owns or has any responsibility over the resource it
     * previously managed.
     *
     * @param other The anchor object to move resources from.
     *              After this operation, other is guaranteed to be in a state
     *              where it does not manage any resource.
     *
     * @note This constructor is noexcept as it guarantees no exceptions
     *       will be thrown during its execution, making it safe for certain
     *       optimizations and operations within the C++ standard library.
     */
    anchor(anchor &&other) noexcept
        : m_ptr(other.ptr())
    {
        other.reset();
    }

    /**
     * @brief Creates a new anchor object as a copy of an existing object.
     *
     * It's important to note that this constructor performs a shallow copy of resources.
     * This means that the copied object and its copy will share the same managed resource
     * (if any). Depending on the context of the class's use, this might be desired
     * behavior or a potential source of problems (e.g., unexpected data modification or
     * memory management errors).
     *
     * @param ref A reference to an anchor object from which to create the copy.
     */
    explicit anchor(const_reference ref)
        : m_ptr(&ref)
    {
    }

    /**
     * @brief Copy constructor that initializes
     *        the anchor with another anchor's pointer.
     *
     * This constructor creates a new anchor instance by copying the pointer managed by
     * another anchor instance. It is noexcept as it does not throw exceptions.
     *
     * @param other The other anchor instance from which the pointer is copied.
     */
    anchor(anchor &other) noexcept
        : m_ptr(other.ptr())
    {
    }

    /**
     * @brief Templated copy constructor that initializes
     *        the anchor with a different type.
     *
     * This constructor template enables the creation of a new anchor from another anchor
     * managing a different type. This is particularly useful when converting between
     * anchor types, provided that U* is convertible to T*.
     *
     * @tparam U The type of object the other anchor is managing.
     * @param other The other anchor instance from which the pointer is copied.
     */
    template<typename U>
    explicit anchor(const anchor<U> &other) noexcept
        : m_ptr(other.ptr())
    {
    }

    /**
     * @brief Move assignment operator.
     *
     * Transfers ownership of the managed resource from other to this object,
     * taking care to release any resource currently owned by this object
     * beforehand. If the object is engaged to itself, the operation has no effect.
     *
     * @param other Another anchor object to assign from.
     *              This object will be left in a valid but unspecified state
     *              after the operation, with no resource under its management.
     *
     * @return A reference to *this object, to allow
     *         for chaining of assignment operations.
     *
     * @note This operator is noexcept, meaning it is guaranteed to not throw
     *       exceptions, which is essential for types that are moved often,
     *       allowing certain optimizations in the C++ standard library.
     */
    anchor &
    operator=(anchor &&other) noexcept
    {
        if (this != &other)
        {
            emplace(other.ptr());
            other.reset();
        }
        return *this;
    }

    /**
     * @brief Destructor.
     * @details Resets the managed pointer,
     *          potentially freeing the managed resource.
     */
    ~anchor() noexcept
    {
        reset();
    }

    /**
     * @brief Equality comparison between managed object
     *        and a raw object reference.
     * @param lhs The left-hand side anchor object.
     * @param rhs The right-hand side object reference.
     * @return true if the managed object is the same as the rhs reference,
     *         false otherwise.
     */
    friend bool
    operator==(const anchor<T> &lhs, const T &rhs)
    {
        return lhs.ptr() == &rhs;
    }

    /**
     * @brief Inequality comparison between managed object
     *        and a raw object reference.
     *
     * @param lhs The left-hand side anchor object.
     * @param rhs The right-hand side object reference.
     * @return true if the managed object is not the same as the rhs reference,
     *         false otherwise.
     */
    friend bool
    operator!=(const anchor<T> &lhs, const T &rhs)
    {
        return !operator==(lhs, rhs);
    }

    /**
     * @brief Equality comparison between two anchors.
     * @param lhs The left-hand side anchor object.
     * @param rhs The right-hand side anchor object.
     * @return true if both anchors manage the same object, false otherwise.
     */
    friend bool
    operator==(const anchor<T> &lhs, const anchor<T> &rhs)
    {
        return lhs.ptr() == rhs.ptr();
    }

    /**
     * @brief Inequality comparison between two anchors.
     * @param lhs The left-hand side anchor object.
     * @param rhs The right-hand side anchor object.
     * @return true if the anchors manage different objects, false otherwise.
     */
    friend bool
    operator!=(const anchor<T> &lhs, const anchor<T> &rhs)
    {
        return !operator==(lhs, rhs);
    }

    /**
     * @brief Conversion operator to bool.
     * @return true if the anchor manages an object, false otherwise.
     */
    explicit
    operator bool() const noexcept
    {
        return has_reference();
    }

    /**
     * @brief Member access operator.
     * @return A pointer to the managed object.
     */
    pointer
    operator->()
    {
        return ptr();
    }

    /**
     * @brief Member access operator (constant overload).
     * @return A constant pointer to the managed object.
     */
    const_pointer
    operator->() const noexcept
    {
        return ptr();
    }

    /**
     * @brief Dereference operator.
     * @return A reference to the managed object.
     */
    reference
    operator*()
    {
        return ref();
    }

    /**
     * @brief Dereference operator (constant overload).
     * @return A constant reference to the managed object.
     */
    const_reference
    operator*() const
    {
        return ref();
    }

private:
    pointer m_ptr; ///< The managed pointer.
};

} // namespace mi

#endif /* MI_ANCHOR_HPP */