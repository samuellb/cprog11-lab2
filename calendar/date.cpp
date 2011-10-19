
#include "date.h"
#include <iostream>
#include <iomanip>

namespace lab2 {
    
    /*bool Date::operator!=(const Date & other) const {
        return !(*this == other);
    }
    
    bool operator<=(const Date & other) const {
        return !(other < *this);
    }
    
    bool operator>(const Date &) const {
        return !(*this <= other);
    }
    
    bool operator>=(const Date &) const {
        return !(*this < other);
    }
    */
    std::ostream & operator<<(std::ostream & os, const Date & date) {
        // TODO: days_this_month() > day()
        os << date.year() << "-";
        os << std::setfill('0') << std::setw(2) << date.month();
        os << std::resetiosflags(std::ios::left);
        os << "-" << std::setfill('0') << std::setw(2) << date.days_this_month();
        return os;
    }
    
}



