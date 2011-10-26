#include <stdexcept>
#include "julian.h"
#include "kattistime.h"

namespace lab2 {

Julian::Julian() : WesternDate() { }

Julian::Julian(int year, int month, int day) {
    set_date(year, month, day);
    // Check that the date is correct
    calc();
    if (year != calc_year || month != calc_month || day != calc_day)
        throw std::out_of_range("Invalid date");
}

Julian::Julian(const Date & d) : WesternDate(d) { }

/**
 * calc
 * 
 * @link http://www8.cs.umu.se/~isak/Snippets/jdn.c
 */
void Julian::calc() const {
    if (date == calculated_date)
        return;

    long x, z, m, d, y;
    x = date + 68569L;
    x += 38;
    long daysPer400Years = 146100L;
    long fudgedDaysPer4000Years = 1461000L + 1;
    z = 4 * x / daysPer400Years;
    x = x - (daysPer400Years * z + 3) / 4;
    y = 4000 * (x + 1) / fudgedDaysPer4000Years;
    x = x - 1461 * y / 4 + 31;
    m = 80 * x / 2447;
    d = x - 2447 * m / 80;
    x = m / 11;
    m = m + 2 - 12 * x;
    y = 100 * (z - 49) + y + x;

    calc_year = (int) y;
    calc_month = (int) m;
    calc_day = (int) d;

    // Adjust BC year
    if (calc_year <= 0)
        (calc_year)--;

    calculated_date = date;
}

/**
 * set_date
 * 
 * @link http://www8.cs.umu.se/~isak/Snippets/jdn.c
 */
void Julian::set_date(int year, int month, int day) {
    // Adjust BC year
    if (year < 0)
        year++;

    date = 367L * year - 7 * (year + 5001L + (month - 9) / 7) / 4 + 275 * month / 9 + day + 1729777L;
}

}
