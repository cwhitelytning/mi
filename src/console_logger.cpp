#include <mi/console_logger.hpp>
#include <mi/datetime.hpp>

using namespace mi;

void
console_logger::log(const extension &sender, logger_level level, ustring_view message)
{
    interpolate_stream(uclog,
                       USTRING("L {}\t[{}]\t{}\t{}"),
                       now_datetime(USTRING("%Y.%m.%d %H:%M:%S")),
                       sender.classname(),
                       logger_level_to_string(level),
                       message);
}
