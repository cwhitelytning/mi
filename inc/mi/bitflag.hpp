/**
 * @file bitflag.hpp
 * @brief Utility macros for performing bit operations.
 */

#ifndef MI_BITFLAG_HPP
#define MI_BITFLAG_HPP

/**
 * @brief Sets the bits specified by mask v in variable x.
 *
 * @param x The variable whose bits are to be modified.
 * @param v The bit mask specifying which bits to set.
 * @return The new value of x with the specified bits set.
 */
#define BITFLAG_SET(x, v) ((x) | (v))

/**
 * @brief Checks if any bits specified by mask v are set in variable x.
 *
 * @param x The variable to check.
 * @param v The bit mask specifying which bits to check.
 * @return Non-zero if any of the specified bits are set, zero otherwise.
 */
#define BITFLAG_CHECK(x, v) ((x) & (v))

/**
 * @brief Clears the bits specified by mask v in variable x.
 *
 * @param x The variable whose bits are to be cleared.
 * @param v The bit mask specifying which bits to clear.
 * @return The new value of x with the specified bits cleared.
 */
#define BITFLAG_CLEAR(x, v) ((x) & ~(v))

/**
 * @brief Toggles the bits specified by mask v in variable x.
 *
 * @param x The variable whose bits are to be toggled.
 * @param v The bit mask specifying which bits to toggle.
 * @return The new value of x with the specified bits toggled.
 */
#define BITFLAG_TOGGLE(x, v) ((x) ^ (v))

/**
 * @brief Sets a bit at index i in variable x.
 *
 * @param x The variable whose bit is to be set.
 * @param i The index of the bit to set.
 */
#define BITFLAG_SET_BY_INDEX(x, i) ((x) |= (1ULL << (i)))

/**
 * @brief Clears a bit at index i in variable x.
 *
 * @param x The variable whose bit is to be cleared.
 * @param i The index of the bit to clear.
 */
#define BITFLAG_CLEAR_BY_INDEX(x, i) ((x) &= ~(1ULL << (i)))

/**
 * @brief Toggles a bit at index i in variable x.
 *
 * @param x The variable whose bit is to be toggled.
 * @param i The index of the bit to toggle.
 */
#define BITFLAG_TOGGLE_BY_INDEX(x, i) ((x) ^= (1ULL << (i)))

/**
 * @brief Checks if a bit at index i is set in variable x.
 *
 * @param x The variable to check.
 * @param i The index of the bit to check.
 * @return Non-zero if the specified bit is set, zero otherwise.
 */
#define BITFLAG_CHECK_BY_INDEX(x, i) ((x) & (1ULL << (i)))

/**
 * @brief Changes a bit at index i in variable x to n.
 *
 * @param x The variable whose bit is to be changed.
 * @param i The index of the bit to change.
 * @param n The new value for the bit (0 or 1).
 */
#define BITFLAG_CHANGE_BY_INDEX(x, i, n) ((x) = ((x) & ~(1ULL << (i))) | ((n) << (i)))

/**
 * @brief Gets a byte at index i from variable x.
 *
 * @param x The variable to extract the byte from.
 * @param i The index of the byte to extract.
 * @return The extracted byte.
 */
#define BITFLAG_GET_BYTE_BY_INDEX(x, i) (((x) >> (8 * (i))) & 0xFF)

/**
 * @brief Sets a byte at index i in variable x to n.
 *
 * @param x The variable whose byte is to be set.
 * @param i The index of the byte to set.
 * @param n The value to set the byte to.
 */
#define BITFLAG_SET_BYTE_BY_INDEX(x, i, n)                                               \
    ((x) = ((x) & ~(0xFFULL << (8 * (i)))) | ((n) << (8 * (i))))

/**
 * @brief Rotates the bits of x to the left n times.
 *
 * @param x The variable whose bits are to be rotated.
 * @param n The number of positions to rotate to the left.
 * @return The value of x after the bits have been rotated.
 */
#define BITFLAG_ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (sizeof(x) * 8 - (n))))

/**
 * @brief Rotates the bits of x to the right n times.
 *
 * @param x The variable whose bits are to be rotated.
 * @param n The number of positions to rotate to the right.
 * @return The value of x after the bits have been rotated.
 */
#define BITFLAG_ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (sizeof(x) * 8 - (n))))

#endif /* MI_BITFLAG_HPP */
