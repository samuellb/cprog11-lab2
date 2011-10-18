
#include "date.h"
#include <iostream>

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
        os << date.year() << "-" << date.month() << "-" << date.days_this_month();
        return os;
    }
    
}



