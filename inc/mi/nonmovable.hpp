/**
 * @file MI_NonMovable.hpp
 * @brief Contains the definition of the nonmovable class.
 *        This class is designed to be a base to prevent
 *        move operations on derived classes.
 */

#ifndef MI_NONMOVABLE_HPP
#define MI_NONMOVABLE_HPP

namespace mi::mixin
{

/**
 * @class nonmovable
 * @brief A class that prevents move operations.
 *
 * The nonmovable class is a utility class designed to be inherited by other
 * classes that should not be movable. This is accomplished by deleting the move
 * constructor and move assignment operator.
 *
 * A class derived from nonmovable will not be able to be moved,
 * ensuring that resources managed by such a class are not accidentally moved
 * and potentially invalidated.
 */
class nonmovable
{
public:
    /**
     * @brief Default constructor.
     *        Constructs a new nonmovable object.
     *
     * As this class is meant to be a base class,
     * the constructor is defaulted.
     */
    nonmovable() = default;

    /**
     * @brief Deleted move constructor.
     *
     * Prevents the object from being moved,
     * ensuring that it cannot be moved to another instance.
     *
     * This move constructor is explicitly deleted to disable
     * move semantics for this class and its derived classes.
     *
     * @param other The other instance to move from.
     *              This operation is not allowed.
     */
    nonmovable(nonmovable &&) = delete;

    /**
     * @brief Deleted move assignment operator.
     *
     * Prevents the object from being replaced by a temporary object,
     * ensuring that it cannot be assigned a new value via move semantics.
     *
     * This assignment operator is explicitly deleted to disable
     * move semantics for this class and its derived classes.
     *
     * @param other The other instance to move assign from.
     *              This operation is not allowed.
     *
     * @return A reference to this instance after attempting the move.
     *         This operation is deleted and will not compile if used.
     */
    nonmovable &
    operator=(nonmovable &&) = delete;

    /**
     * @brief Virtual destructor.
     *        Destroys the nonmovable object.
     *
     * This destructor is virtual to allow derived classes to clean up resources
     * in a polymorphic context. It is defaulted to encourage clean and safe
     * inheritance patterns.
     */
    virtual ~nonmovable() = default;
};

} // namespace mi::mixin

#endif /* MI_NONMOVABLE_HPP */
