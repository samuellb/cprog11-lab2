#include <stdexcept>
#include "gregorian.h"
#include "kattistime.h"

namespace lab2 {

Gregorian::Gregorian() : WesternDate() { }

Gregorian::Gregorian(int year, int month, int day) {
    set_date(year, month, day);
    // Check that the date is correct
    calc();
    if (year != calc_year || month != calc_month || day != calc_day)
        throw std::out_of_range("Invalid date");
}

Gregorian::Gregorian(const Date & d) : WesternDate(d) { }


void Gregorian::calc() const {
    /*if (calculated_date != -1 && date == calculated_date)
        return;*/

    int j = date + 32044;
    int g = j / 146097;
    int dg = j % 146097;
    int c = (dg / 36524 + 1) * 3 / 4;
    int dc = dg - c * 36524;
    int b = dc / 1461;
    int db = dc % 1461;
    int a = (db / 365 + 1) * 3 / 4;
    int da = db - a * 365;
    int y = g * 400 + c * 100 + b * 4 + a;
    int m = (da * 5 + 308) / 153 - 2;
    int d = da - (m + 4) * 153 / 5 + 122;
    calc_year = y - 4800 + (m + 2) / 12;
    calc_month = (m + 2) % 12 + 1;
    calc_day = d + 1;

    calculated_date = date;
}

void Gregorian::set_date(int year, int month, int day) {
    int a = (14 - month) / 12;
    int y = 4800 + year - a;
    int m = month + 12 * a - 3;

    date = day + ((153 * m + 2) / 5) + 365 * y + (y / 4) - (y / 100) + (y / 400) - 32045;
}

bool Gregorian::leap_year(int year) const {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

}
