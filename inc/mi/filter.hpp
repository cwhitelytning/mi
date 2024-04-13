/**
 * @file filter.hpp
 * @brief Defines a generic filtering mechanism for applying actions
 *        to elements in a range based on a predicate.
 *
 * This header provides utilities for applying a given action to each element in a range
 * that satisfies a specified filtering condition. It includes a default filter that
 * applies the action to all elements and a customizable filter iterator function
 * that applies an action to elements that pass a user-defined filter.
 *
 * This is particularly useful for algorithms that may need
 * to conditionally process elements based on runtime criteria.
 *
 * Example usage:
 * @code
 * auto result = mi::filter::iterate(collection.begin(), collection.end(),
 *                                   [](auto& item) { ... },
 *                                   [](const auto& item) { return item.is_valid(); });
 * @endcode
 */

#ifndef MI_FILTER_HPP
#define MI_FILTER_HPP

#include <type_traits>

namespace mi::filter
{

/**
 * @var default_filter
 * @brief A default filter function that always returns true,
 *        indicating no filtering is to be applied.
 *
 * This constant expression lambda function acts as
 * a default predicate that is used in filtering operations.
 *
 * It accepts any number of arguments of any type, and always returns true,
 * signifying that all elements pass the filter by default.
 *
 * Example usage in an algorithm that can optionally filter elements:
 * @code
 * auto result = custom_algorithm(collection.begin(), collection.end(),
 * processing_function, default_filter);
 * @endcode
 *
 * The default_filter can be replaced with a user-defined function
 * to apply specific filtering logic.
 *
 * @tparam auto A template parameter pack representing
 *              any number of arguments of any type.
 *
 * @param ... A parameter pack capturing
 *            all arguments passed to the lambda.
 *
 * @return Always returns true,
 *         indicating every element should be considered by the filtering algorithm.
 */
constexpr const auto default_filter = [](const auto &...)
{
    return true;
};

/**
 * @brief Iterates over a range and applies a callback to each element,
 *        with an optional filtering callback.
 *
 * This function template iterates from begin to end, applying callback to each element.
 * If a filter callback is provided, it will only apply callback to elements that pass
 * the filter. If no filter is provided, callback is applied to all elements.
 *
 * @tparam Iterator The type of the iterator for the range.
 * @tparam Callback The type of the callback function that defines
 *                  the action to be applied to each element.
 * @tparam FilterCallback The type of the callback function used to filter elements.
 *                        Defaults to a function that always returns true.
 *
 * @param begin The beginning of the range to iterate over.
 * @param end The end of the range to iterate over.
 * @param callback The action to apply to each element.
 * @param filter The filter to decide whether the action should be applied to an element.
 *               Defaults to a function that always returns true.
 *
 * @return A pointer to the element that caused the callback to return a non-void,
 *         non-false value, or nullptr if no such element exists
 *         or if the callback is void.
 */
template <typename Iterator,
          typename Callback,
          typename FilterCallback = decltype(default_filter)>
auto
iterate(Iterator       begin,
        Iterator       end,
        Callback       callback,
        FilterCallback filter = default_filter) -> decltype(&*begin)
{
    /// Deduced return type of the callback.
    using return_type = std::invoke_result_t<Callback, decltype(*begin)>;

    /// Loop over the range from begin to end.
    for (; begin != end; ++begin)
    {
        /// If a custom filter is provided.
        if constexpr (!std::is_same_v<FilterCallback, decltype(default_filter)>)
        {
            /// Deduced return type of the filter callback.
            using filter_return_type =
                std::invoke_result_t<FilterCallback, decltype(*begin)>;

            /// Assert the filter returns a boolean.
            static_assert(std::is_convertible_v<filter_return_type, bool>,
                          "Filter callback must return boolean");

            /// If the element does not pass the filter.
            if (!filter(*begin))
            {
                /// Skip the current element and continue with the next iteration.
                continue;
            }
        }

        /// If the callback has a void return type.
        if constexpr (std::is_void_v<return_type>)
        {
            /// Simply call the callback.
            callback(*begin);
        }
        else
        {
            /// If the callback returns a truthy value.
            if (callback(*begin))
            {
                /// Return a pointer to the current element.
                return &(*begin);
            }
        }
    }

    /// If no elements meet the condition, return nullptr.
    return nullptr;
}

} // namespace mi::filter

#endif /* MI_FILTER_HPP */
