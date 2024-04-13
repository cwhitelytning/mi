/**
 * @file MI_TYPE_ALIASES.hpp
 * @brief Defines standard type aliases used throughout the mi namespace.
 *
 * This file provides template structures that define standard type aliases such as
 * references and pointers for easier and more readable type definitions.
 */

#ifndef MI_TYPE_ALIASES_HPP
#define MI_TYPE_ALIASES_HPP

namespace mi
{

/**
 * @struct type_aliases
 * @brief Defines standard type aliases for a given type.
 *
 * This structure provides type aliases for value, reference, const_reference,
 * pointer, and const_pointer types based on the given type T.
 *
 * @tparam T The base type for which to create the type aliases.
 */
template <typename T>
struct type_aliases
{
    /**
     * @brief The base type as value_type.
     */
    using value_type = T;

    /**
     * @brief Mutable reference to the base type.
     */
    using reference = T &;

    /**
     * @brief Immutable reference to the base type.
     */
    using const_reference = T const &;

    /**
     * @brief Mutable pointer to the base type.
     */
    using pointer = T *;

    /**
     * @brief Immutable pointer to the base type.
     */
    using const_pointer = T const *;
};

/**
 * @struct type_aliases<T const>
 * @brief Specializes the type_aliases for const-qualified types.
 *
 * This structure is a specialization of type_aliases for const-qualified types,
 * ensuring that the value_type and all pointer and reference types are also
 * const-qualified.
 *
 * @tparam T The base type for which to create const-qualified type aliases.
 */
template <typename T>
struct type_aliases<T const>
{
    /**
     * @brief The base type as const-qualified value_type.
     */
    using value_type = T const;

    /**
     * @brief Immutable reference to the base type.
     */
    using reference = T const &;

    /**
     * @brief Immutable reference to the base type (redundant, same as reference).
     */
    using const_reference = T const &;

    /**
     * @brief Immutable pointer to the base type.
     */
    using pointer = T const *;

    /**
     * @brief Immutable pointer to the base type (redundant, same as pointer).
     */
    using const_pointer = T const *;
};

} // namespace mi

#endif // MI_TYPE_ALIASES_HPP
