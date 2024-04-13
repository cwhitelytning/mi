#include <mi/logger_level.hpp>

using namespace mi;

ustring_view
mi::logger_level_to_string(enum logger_level level)
{
    return LOGGER_LEVEL_TO_STRING(level);
}