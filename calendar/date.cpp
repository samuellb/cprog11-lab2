
#include "date.h"
#include "kattistime.h"
#include <iostream>
#include <iomanip>

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

void Date::add_year(int year) {
    calc();
    set_date(calc_year + year, calc_month, calc_day);
}

void Date::add_month(int month) {
    calc();
    set_date(calc_year, calc_month + month, calc_day);
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



