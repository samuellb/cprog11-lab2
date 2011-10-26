
#include "date.h"
#include "kattistime.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace lab2 {

Date::Date() : 
    date((k_time(NULL) / 86400) + 2440588), // Added +0.5 rounded
    calculated_date(-1),
    calc_year(0),
    calc_month(0),
    calc_day(0) { }

Date::Date(int d) :
    date(d),
    calculated_date(-1),
    calc_year(0),
    calc_month(0),
    calc_day(0) { }

Date::Date(const Date & d) :
    date(d.date),
    calculated_date(d.calculated_date),
    calc_year(d.calc_year),
    calc_month(d.calc_month),
    calc_day(d.calc_day) { }

void Date::add_year(int year) {
    /*for (int minus_day = 0; minus_day < 3; minus_day++) {
        calc();
        int y = calc_year;
        int m = calc_month;
        int d = calc_day - minus_day;
    
        set_date(calc_year + year, calc_month, d);
        calc();
        if (calc_day == d) break; // Success

        // Restore and try again
        set_date(y, m, d);
    }*/

    calc();
    int y = calc_year + year;
    
    if (y % 4 != 0 && calc_month == 2 && calc_day == 29) calc_day--;

    set_date(y, calc_month, calc_day);
}

void Date::add_month(int month) {
    //calc();
    //set_date(calc_year, calc_month + month, calc_day);
    int abs_month = std::abs(month);
    int step = (month < 0 ? -1 : 1);
    for (int i = 0; i < abs_month; ++i) {
        /*calc();
        int y = calc_year;
        int m = calc_month;
        int d = calc_day;

        set_date(calc_year, calc_month + step, calc_day);
        calc();

        // Check if the new date is correct
        if (calc_day != d) {
            // Go back to old date
            set_date(y, m, d);

            // Add 30 days
            *this += 30*step;
        }*/

        calc();
        int y = calc_year;
        int m = calc_month;
        int d = calc_day;
        
        m += step;

        // Fix the date
        if (m <= 0) { y--; m = 1; }
        if (m > days_in_month()
    }
}


std::ostream & operator<<(std::ostream & os, const Date & date) {
    os << date.year() << "-";
    os << std::setfill('0') << std::setw(2) << date.month();
    os << std::resetiosflags(std::ios::left);
    os << "-" << std::setfill('0') << std::setw(2) << date.day();
    return os;
}

Date::~Date() { }


}



