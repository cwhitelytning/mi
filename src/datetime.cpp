#include <iomanip>
#include <mi/datetime.hpp>
#include <mi/datetime_error.hpp>
#include <regex>

using namespace mi;
using namespace mi::datetime;

template <typename Clock, typename Duration>
timestamp_t
datetime::extract_milliseconds(std::chrono::time_point<Clock, Duration> point)
{
    using namespace std::chrono;

    // Convert the current time to milliseconds
    auto now_ms = time_point_cast<milliseconds>(point);

    // We get the time since the beginning of the epoch in milliseconds
    auto epoch = now_ms.time_since_epoch();

    // Convert time type to milliseconds
    auto duration = duration_cast<milliseconds>(epoch);

    // We get the remainder of the division of milliseconds
    auto duration_ms = duration.count() % MILLISECONDS_IN_SECOND;

    // Return the number of milliseconds
    return duration_ms;
}

timestamp_t
datetime::now_milliseconds()
{
    return extract_milliseconds(std::chrono::system_clock::now());
}

bool
datetime::is_valid_format(std::string_view format)
{
#ifdef MI_SUPPORT_MILLISECONDS
    uregex pattern(USTRING("(%[YmdHMStRLFS]+|[^%]+)+"));
#else
    uregex pattern(USTRING("(%[YmdHMStRFS]+|[^%]+)+"));
#endif

    return std::regex_match(format.data(), pattern);
}

void
datetime::now_datetime(std::ostream &stream, std::string_view fmt)
{
    if (!is_valid_format(fmt))
    {
        throw exception::datetime_error("invalid datetime format (format: {})", fmt);
    }

    auto now  = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::tm bt{};

#if defined(MI_OS_UNIX_LIKE)
    localtime_r(&time, &bt);
#elif defined(MI_OS_WINDOWS)
    localtime_s(&bt, &time);
#else
    static std::mutex           mtx; // For thread safe use of localtime
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&time);
#endif

#ifdef MI_SUPPORT_MILLISECONDS
    {
        size_t pos = fmt.find("%L");
        if (pos != std::string::npos)
        {
            auto duration_ms = now_milliseconds();

            str::ustring str = fmt.data();
            str.replace(pos, 2, std::to_string(duration_ms));
            stream << std::put_time(&bt, str.c_str());
        }
    }
#else
    stream << std::put_time(&bt, fmt.data());
#endif
}

std::string
datetime::now_datetime(std::string_view fmt)
{
    uostringstream oss;
    now_datetime(oss, fmt);
    return oss.str();
}