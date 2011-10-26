#include "gregorian.h"
#include "julian.h"
#include "kattistime.h"
#include <iostream>
#include <stdexcept>
#include <ctime>

int main() {

    set_k_time(std::time(NULL));

    lab2::Gregorian g;
    std::cout << g << std::endl;
    std::cout << g.week_day_name() << std::endl;

    lab2::Julian j;
    std::cout << j << std::endl;
    std::cout << j.week_day_name() << std::endl;
    
    g.add_year(4);
    std::cout << g << std::endl;

    lab2::Gregorian d(2004, 2, 29);
    std::cout << "test leap day: " << d << std::endl;

    d.add_year(4);
    std::cout << "add 4 years: " << d << std::endl;

    d.add_year(1);
    std::cout << "add 1 year: " << d << std::endl;

    lab2::Gregorian r = ++d;
    std::cout << "++d: " << d << ", return: " << r << std::endl;

    lab2::Gregorian r2 = d += 30;
    std::cout << "d += 1: " << d << ", return: " << r2 << std::endl;

    lab2::Gregorian r1 = d++;
    std::cout << "d++: " << d << ", return: " << r1 << std::endl;

    lab2::Gregorian good(2004, 2, 29);
    std::cout << "created 2004-02-29: " << good << std::endl;

    try {
        lab2::Gregorian bad(2003, 2, 29);
        std::cout << "created 2003-02-29 (wrong!): " << bad << std::endl;
    } catch (std::out_of_range) {
        std::cout << "caught exception from invalid date" << std::endl;
    }

    /* Test a large date */
    lab2::Gregorian future(2560, 10, 2);
    std::cout << "   Gregorian(2560, 10, 2) :  " << future << std::endl;

    return 0;
}
