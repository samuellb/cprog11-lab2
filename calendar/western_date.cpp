#include "western_date.h"

#include <cstdlib>

namespace lab2 {

WesternDate::WesternDate() : Date() { }
WesternDate::WesternDate(const Date & d) : Date(d) { }


int WesternDate::week_day() const {
    return date % 7 + 1;
}

int WesternDate::days_per_week() const {
    return 7;
}

int WesternDate::days_that_month(int year, int month) const {
    static const int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && leap_year(year)) return 29;
    else return days_per_month[month - 1];
}

int WesternDate::days_this_month() const {
    return days_that_month(year(), month());
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

bool WesternDate::leap_year() const {
    return leap_year(year());
}


void WesternDate::add_year(int year) {
    calc();
    int y = calc_year + year;
    int m = calc_month;
    int d = calc_day;
    
    if (!leap_year(y) && m == 2 && d == 29) d = 28;

    set_date(y, m, d);
}

void WesternDate::add_month(int month) {
    int abs_month = std::abs(month);
    int step = (month < 0 ? -1 : 1);
    for (int i = 0; i < abs_month; ++i) {
        calc();
        int y = calc_year;
        int m = calc_month;
        int d = calc_day;
        
        m += step;

        // Fix the date
        if (m <= 0) { y--; m = months_per_year(); }
        if (m > months_per_year()) { y++; m = 1; }
        
        // Check the day
        if (d > days_that_month(y, m)) {
            // Add/subtract 30 days
            *this += 30*step;
        } else {
            // Add one month
            set_date(y, m, d);
        }
    }
}

bool WesternDate::valid_date(int year, int month, int day) const {
    if (year < -4000 || year > 3000) return false; // Tested date range
    if (month <= 0 || month > months_per_year()) return false;
    if (day <= 0 || day > days_that_month(year, month)) return false;
    return true;
}


}

