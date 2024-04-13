#ifndef MI_INC_MI_DATETIME_HPP
#define MI_INC_MI_DATETIME_HPP

#include "unicode.hpp"
#include <chrono>
#include <ctime>

namespace mi
{

/**
 * @typedef timestamp_t
 * @brief Defines a type for representing timestamps.
 *
 * This type is used for representing timestamps in the application, allowing
 * for an abstraction over the actual underlying numerical type.
 *
 * It is currently defined as a size_t, suitable for representing large numbers.
 */
using timestamp_t = size_t;

/** @brief Number of milliseconds in one second.
 *
 *  This constant represents the number of milliseconds in one second,
 *  defining the relationship between these two units of time.
 *  It is useful for conversions between milliseconds and seconds.
 */
constexpr timestamp_t MILLISECONDS_IN_SECOND = 1000;

/** @brief Number of microseconds in one millisecond.
 *
 *  This constant defines the number of microseconds in a single millisecond,
 *  facilitating conversions between these time units.
 *  It aids in precise time calculations and measurements.
 */
constexpr timestamp_t MICROSECONDS_IN_MILLISECOND = 1000;

/** @brief Number of nanoseconds in one microsecond.
 *
 *  This constant specifies the number of nanoseconds in one microsecond,
 *  essential for conversions and calculations involving these units.
 *  It supports high-resolution timing and performance metrics.
 */
constexpr timestamp_t NANOSECONDS_IN_MICROSECOND = 1000;

/** @brief Number of seconds in one minute.
 *
 *  This constant indicates the number of seconds in one minute,
 *  used for converting between minutes and seconds.
 *  It is useful in various time-related calculations and operations.
 */
constexpr timestamp_t SECONDS_IN_MINUTE = 60;

/** @brief Number of minutes in one hour.
 *
 *  This constant represents the number of minutes in one hour,
 *  providing a base for time conversions between minutes and hours.
 *  It assists in scheduling and time management operations.
 */
constexpr timestamp_t MINUTES_IN_HOUR = 60;

/** @brief Number of hours in one day.
 *
 *  This constant details the number of hours in one standard day,
 *  crucial for converting between days and hours.
 *  It plays a key role in daily scheduling and long-term planning.
 */
constexpr timestamp_t HOURS_IN_DAY = 24;

/** @brief Number of days in one week.
 *
 *  This constant provides the number of days in a standard week,
 *  essential for calculations and operations involving weeks
 *  and days. It is commonly used in weekly planning and scheduling tasks.
 */
constexpr timestamp_t DAYS_IN_WEEK = 7;

/** @brief Number of milliseconds in one minute.
 *
 *  This constant calculates the number of milliseconds in a single minute,
 *  derived from the number of milliseconds in a second and the number of
 *  seconds in a minute. It is useful for time conversions and precise
 *  timing operations over longer periods.
 */
constexpr timestamp_t MILLISECONDS_IN_MINUTE = MILLISECONDS_IN_SECOND * SECONDS_IN_MINUTE;

/** @brief Number of milliseconds in one hour.
 *
 *  This constant determines the number of milliseconds in one hour,
 *  combining the milliseconds in a minute and the number of minutes in an hour.
 *  It aids in accurate time tracking and conversions over hourly periods.
 */
constexpr timestamp_t MILLISECONDS_IN_HOUR = MILLISECONDS_IN_MINUTE * MINUTES_IN_HOUR;

/** @brief Number of milliseconds in one day.
 *
 *  This constant calculates the number of milliseconds in a standard day,
 *  utilizing the number of milliseconds in an hour and the number of hours in a
 * day. It is crucial for precise timing and scheduling over daily cycles.
 */
constexpr timestamp_t MILLISECONDS_IN_DAY = MILLISECONDS_IN_HOUR * HOURS_IN_DAY;

/** @brief Number of seconds in one hour.
 *
 *  This constant defines the number of seconds in a single hour,
 *  based on the number of seconds in a minute and the number of minutes in an
 * hour. It facilitates conversions and calculations involving hours and
 * seconds.
 */
constexpr timestamp_t SECONDS_IN_HOUR = SECONDS_IN_MINUTE * MINUTES_IN_HOUR;

/** @brief Number of seconds in one day.
 *
 *  This constant indicates the total number of seconds in one standard day,
 *  derived from the number of seconds in an hour and the number of hours in a
 * day. It is used for time management and day-length calculations.
 */
constexpr timestamp_t SECONDS_IN_DAY = SECONDS_IN_HOUR * HOURS_IN_DAY;

/**
 * @brief Extracts the milliseconds part of a time_point object.
 *
 * This function takes a std::chrono::time_point object and extracts the
 * milliseconds part from it, relative to the total duration since the epoch.
 *
 * This is useful for operations that require granularity
 * at the millisecond level rather than a full timestamp.
 *
 * @tparam Clock The clock type of the time_point
 *               (e.g., system_clock, steady_clock).
 *
 * @tparam Duration The duration type of the time_point
 *                  (e.g., nanoseconds, microseconds, milliseconds).
 *
 * @param point The time_point object from which to extract milliseconds.
 * @return timestamp_t The milliseconds part of the time.
 *
 * @note It's important to note that this method returns only the milliseconds
 *       part within the current second, not the total milliseconds
 *       since the epoch.
 */
template <typename Clock, typename Duration>
timestamp_t
extract_milliseconds(std::chrono::time_point<Clock, Duration> point);

/**
 * @brief Returns the current time in milliseconds.
 *
 * This method returns the current system time in milliseconds, but only the
 * part that represents the milliseconds within the current second.
 *
 * This is useful for operations or measurements that require the millisecond
 * part of the current time.
 *
 * @note It's important to note that this method returns only the milliseconds
 *       part within the current second, not the total milliseconds
 *       since the epoch.
 *
 * @return timestamp_t The milliseconds part of the current system time.
 */
timestamp_t
now_milliseconds();

/**
 * @brief Checks if the given datetime format string is valid.
 *
 * This function verifies if the provided datetime format string
 * complies with a set of basic time format specifiers.
 *
 * The validation is performed by matching the format string against a
 * predefined regular expression that recognizes a sequence of allowable format
 * specifiers and literal characters.
 *
 * The format specifiers are expected to be prefixed with a '%' symbol and can
 * include characters representing year (Y), month (m), day (d), hour (H),
 * minute (M), second (S), and various combined representations like the ISO8601
 * format (R, F).
 *
 * Literal characters are allowed and should not be prefixed with '%'.
 * This allows for a wide range of datetime formats to be validated.
 *
 * @param format A string view representing the datetime format to be validated.
 *               The format uses '%' preceding single characters as placeholders
 *               for specific time components
 *               (e.g., "%Y-%m-%d" for "year-month-day").
 *
 * @return bool `true` if the format string matches
 *              the allowed datetime format specifiers, otherwise `false`.
 */
bool
is_valid_format(std::string_view str);

/**
 * @brief Writes the current system time to the provided output stream,
 *        formatted according to the specified format string.
 *
 * This function fetches the current system time and formats it according to a
 * user-provided format string, which is then written to an output stream.
 *
 * The format for the datetime representation is based on the specifications
 * provided by std::put_time.
 *
 * If the format string is invalid (as determined by is_valid_format),
 * an exception is thrown.
 *
 * @param stream Reference to an output stream where
 *               the formatted datetime will be written.
 *
 * @param fmt A view to a string that specifies
 *              the format of the datetime output.
 *
 *              The format string should be compatible
 *              with std::put_time.
 *
 * @throw datetime_error if the format string is identified
 *                       as invalid by is_valid_format.
 */

void
now_datetime(std::ostream &stream, std::string_view fmt);

/**
 * @brief Gets the current time formatted according to the given format string.
 *
 * This function retrieves the current system time and formats it into a string
 * based on the provided format string. The formatting process is internal and
 * handled by a helper function that takes a string stream (std::ostringstream)
 * and the format string as inputs.
 *
 * The format string should follow the standards used by strftime for
 * consistency, although the actual interpretation may depend on the
 * implementation of the helper function now_datetime(std::ostringstream&,
 * std::string_view).
 *
 * @param fmt A string view representing
 *               the desired format of the current time.
 *
 * @return A std::string that contains the current time
 *         formatted as per the format parameter.
 *
 * @throw datetime_error if the format string is identified
 *                       as invalid by is_valid_format.
 */
std::string
now_datetime(std::string_view fmt);

} // namespace mi

#endif /* MI_INC_MI_DATETIME_HPP */
