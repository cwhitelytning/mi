#include <mi/bitflag.hpp>
#include <mi/fs.hpp>

using namespace mi;
using namespace mi::fs;

bool
fs::is_readable(const fs::path_t &path)
{
    auto perms = std::filesystem::status(path).permissions();
    return BITFLAG_CHECK(perms, perms_t::owner_read) != perms_t::none ||
           BITFLAG_CHECK(perms, perms_t::group_read) != perms_t::none ||
           BITFLAG_CHECK(perms, perms_t::others_read) != perms_t::none;
}

bool
fs::is_writable(const fs::path_t &path)
{
    auto perms = std::filesystem::status(path).permissions();
    return BITFLAG_CHECK(perms, perms_t::owner_write) != perms_t::none ||
           BITFLAG_CHECK(perms, perms_t::group_write) != perms_t::none ||
           BITFLAG_CHECK(perms, perms_t::others_write) != perms_t::none;
}

bool
fs::is_executable(const fs::path_t &path)
{
    auto perms = std::filesystem::status(path).permissions();
    return BITFLAG_CHECK(perms, perms_t::owner_exec) != perms_t::none ||
           BITFLAG_CHECK(perms, perms_t::group_exec) != perms_t::none ||
           BITFLAG_CHECK(perms, perms_t::others_exec) != perms_t::none;
}