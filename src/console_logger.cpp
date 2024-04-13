#include <mi/bitflag.hpp>
#include <mi/console_logger.hpp>
#include <mi/datetime.hpp>

using namespace mi;

void
console_logger::log(const extension &sender, logger_level level, ustring_view message)
{
    if (BITFLAG_CHECK_BY_INDEX(flags(), level))
    {
        format::interpolate_stream(uclog,
                                   std::string_view("L {}\t[{}]\t{}\t{}"),
                                   now_datetime("%Y.%m.%d %H:%M:%S"),
                                   sender.classname(),
                                   logger_level_to_string(level),
                                   message);
    }
}
