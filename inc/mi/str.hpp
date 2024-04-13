#ifndef MI_STR_HPP
#define MI_STR_HPP

#include "builtin.hpp"
#include <sstream>
#include <string>

namespace mi::str
{

MI_BUILTIN std::string
           cstring_to_string(const char *src)
{
    return src ? std::string(src) : std::string();
}

} // namespace mi::str

#endif /* MI_STR_HPP */
