
#include "date.h"
#include <iostream>
#include <iomanip>

namespace lab2 {

    std::ostream & operator<<(std::ostream & os, const Date & date) {
        os << date.year() << "-";
        os << std::setfill('0') << std::setw(2) << date.month();
        os << std::resetiosflags(std::ios::left);
        os << "-" << std::setfill('0') << std::setw(2) << date.day();
        return os;
    }
    
}



