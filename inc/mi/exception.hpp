/**
 * @file exception.hpp
 * @brief Exception handling utilities within the mi::exception namespace.
 * @details Defines utilities to handle exceptions in a functional style.
 */

#ifndef MI_EXCEPTION_HPP
#define MI_EXCEPTION_HPP

#include <exception>
#include <functional>

namespace mi::exception
{

/**
 * @typedef handler_t
 * @brief Function type that handles exceptions.
 *
 * This type defines a function that takes a constant reference to
 * an exception and does not return a value.
 */
using handler_t = std::function<void(const std::exception &exception)>;

/**
 * @brief Executes a callable object and catches any thrown std::exception.
 *
 * This template function tries to invoke a callable with provided arguments.
 * If an exception of type std::exception is thrown,
 * it will be handled by a provided handler.
 *
 * @tparam Callable Type of the callable object.
 * @tparam Args Types of the arguments to pass to the callable object.
 * @param handler A function to handle an exception if one is thrown.
 * @param callable The callable object to be invoked.
 * @param args Arguments to be forwarded to the callable object.
 *
 * @return The result of invoking the callable object.
 *         If an exception is thrown and the return type is not void,
 *         returns a default constructed object of the callable's return type.
 */
template <typename Callable, typename... Args>
auto
invoke_and_catch(const handler_t &handler,
                 Callable       &&callable,
                 Args &&...args) noexcept -> std::invoke_result_t<Callable, Args...>
{
    try
    {
        return std::invoke(std::forward<Callable>(callable), std::forward<Args>(args)...);
    }
    catch (const std::exception &exception)
    {
        if (handler)
        {
            handler(exception);
        }

        using return_type = std::invoke_result_t<Callable, Args...>;
        if constexpr (!std::is_void_v<return_type>)
        {
            return return_type{};
        }
    }
}

/**
 * @brief Executes a callable object without exception propagation.
 *
 * This function is a wrapper around invoke_and_catch that passes a null handler,
 * effectively invoking the callable without handling exceptions.
 *
 * @tparam Callable Type of the callable object.
 * @tparam Args Types of the arguments to pass to the callable object.
 * @param callable The callable object to be invoked.
 * @param args Arguments to be forwarded to the callable object.
 * @return The result of invoking the callable object.
 */
template <typename Callable, typename... Args>
MI_BUILTIN decltype(auto)
invoke_noexcept(Callable &&callable, Args &&...args)
{
    return invoke_and_catch(nullptr,
                            std::forward<Callable>(callable),
                            std::forward<Args>(args)...);
}

} // namespace mi::exception

#endif /* MI_EXCEPTION_HPP */
