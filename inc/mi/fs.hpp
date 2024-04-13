/**
 * @file fs.hpp
 * @brief File system utilities for cross-platform file system operations.
 *
 * Provides a set of utilities, functions, and classes for working with the file
 * system in a cross-platform manner. This includes operations on paths, files,
 * and directories across different operating systems.
 *
 * @note This file is part of the mi::fs namespace,
 *       encapsulating file system operations and types.
 */

#ifndef MI_FS_HPP
#define MI_FS_HPP

#include <filesystem>

/**
 * @namespace mi::fs
 * @brief Namespace dedicated to cross-platform file system utilities.
 *
 * Encapsulates all the functionality for file system operations in a manner
 * that is consistent across different operating platforms. This includes
 * manipulation of paths, file I/O operations, and directory traversal among
 * other utilities.
 */
namespace mi::fs
{
/**
 * @typedef path_t
 * @brief Typedef for std::filesystem::path to simplify usage
 *        within the namespace.
 *
 * This typedef serves as an alias for std::filesystem::path, facilitating its
 * use within the mi::fs namespace and promoting code readability and ease of
 * maintenance.
 */
using path_t = std::filesystem::path;

/**
 * @typedef perms_t
 * @brief Type alias for std::filesystem::perms.
 *
 * This type alias is used to simplify working with file and directory
 * permissions by abstracting the verbose std::filesystem::perms enum class into
 * a more conveniently named perms_t type. It enables easier and more readable
 * usage of permission-related functionality within the fs namespace.
 *
 * The std::filesystem::perms enumeration represents the permissions available
 * for files and directories. These include permissions for reading, writing,
 * and executing files for the owner, the group, and others. The perms_t alias
 * thus directly corresponds to all permissions available under
 * std::filesystem::perms.
 *
 */
using perms_t = std::filesystem::perms;

/**
 * @brief Checks if the specified path is readable.
 *
 * This function checks if the given path has read permissions enabled for the
 * owner, group, or others. It utilizes the std::filesystem::status function
 * to retrieve the permissions of the file and then examines the read bits
 * for different user categories.
 *
 * @throws filesystem_error Thrown if the file or directory at the specified
 *                          path does not exist or if an error occurred when
 *                          trying to access its attributes.
 *
 * @param path The filesystem path to be checked for read permissions.
 * @return true if the path is readable by the owner, group, or others;
 *         false otherwise.
 */
bool
is_readable(const path_t &path);

/**
 * @brief Checks if the specified path is writable.
 *
 * Just like is_readable, this function determines if write permissions are set
 * for the owner, group, or others on the specified path. It makes use of
 * std::filesystem::status to acquire the file's permissions and checks
 * the appropriate write bits.
 *
 * @throws filesystem_error Thrown if the file or directory at the specified
 *                          path does not exist or if an error occurred when
 *                          trying to access its attributes.
 *
 * @param path The filesystem path to be checked for write permissions.
 * @return true if the path is writable by the owner, group, or others;
 *         false otherwise.
 */
bool
is_writable(const path_t &path);

/**
 * @brief Checks if the specified path is executable.
 *
 * This function examines the executable permissions for the owner, group, or
 * others on the provided path. It employs std::filesystem::status to obtain
 * the permissions and then inspects the execution bits for different sets
 * of users.
 *
 * @throws filesystem_error Thrown if the file or directory at the specified
 *                          path does not exist or if an error occurred when
 *                          trying to access its attributes.
 *
 * @param path The filesystem path to be checked for execution permissions.
 * @return true if the path is executable by the owner, group, or others;
 *         false otherwise.
 */
bool
is_executable(const path_t &path);

} // namespace mi::fs

#endif /* MI_FS_HPP */
