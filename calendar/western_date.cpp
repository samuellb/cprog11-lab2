#include "western_date.h"

namespace lab2 {

WesternDate::WesternDate() : Date() { }
WesternDate::WesternDate(const Date & d) : Date(d) { }


int WesternDate::week_day() const {
    return (mod_julian_day() + 1) % 7 + 1;
}

int WesternDate::days_per_week() const {
    return 7;
}

int WesternDate::days_this_month() const {
    static const int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days_per_month[month() - 1];
}

int WesternDate::months_per_year() const {
    return 12;
}

const std::string & WesternDate::week_day_name() const {
    static const std::string day_names[] = {
        "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday",
    };
    return day_names[week_day() - 1];
}

const std::string & WesternDate::month_name() const {
    static const std::string month_names[] = {
        "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december",
    };
    return month_names[month() - 1];
}

}
