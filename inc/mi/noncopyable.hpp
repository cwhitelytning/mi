/**
 * @file noncopyable.hpp
 * @brief Defines the noncopyable class to prevent copy operations.
 */

#ifndef MI_NONCOPYABLE_HPP
#define MI_NONCOPYABLE_HPP

namespace mi
{

/**
 * @class noncopyable
 * @brief A class that disables copy semantics.
 *
 * The noncopyable class serves to prevent copying of
 * any instances of the class or its derivatives.
 *
 * This is achieved by explicitly deleting the copy constructor and copy
 * assignment operator, making the class and its descendants non-copyable.
 */
class noncopyable
{
public:
    /**
     * @brief Default constructor.
     *        Constructs a new noncopyable object.
     *
     * As this class is meant to be a base class,
     * the constructor is defaulted.
     */
    noncopyable() = default;

    /**
     * @brief Deleted copy constructor.
     *
     * Explicitly deletes the copy constructor to prevent copying of
     * any instance of the noncopyable class or its derivatives.
     *
     * @param other - The instance to copy from.
     *                Not applicable as the function is deleted.
     */
    noncopyable(const noncopyable &) = delete;

    /**
     * @brief Deleted copy assignment operator.
     *
     * Explicitly deletes the copy assignment operator to prevent copying
     * of any instance of the noncopyable class or its derivatives.
     *
     * @param other - The instance to copy from.
     *                Not applicable as the function is deleted.
     *
     * @return noncopyable& - Not applicable as the function is deleted.
     */
    noncopyable &
    operator=(const noncopyable &) = delete;

    /**
     * @brief Virtual destructor.
     *        Destroys the noncopyable object.
     *
     * This destructor is virtual to allow derived classes
     * to clean up resources in a polymorphic context.
     *
     * It is defaulted to encourage clean
     * and safe inheritance patterns.
     */
    virtual ~noncopyable() = default;
};

} // namespace mi

#endif /* MI_NONCOPYABLE_HPP */
