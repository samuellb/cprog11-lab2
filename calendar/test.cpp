#include "gregorian.h"
#include "kattistime.h"
#include <iostream>
#include <ctime>

int main() {

    set_k_time(std::time(NULL));

    lab2::Gregorian g;
    std::cout << g << std::endl;
    std::cout << g.week_day_name() << std::endl;
    
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

    lab2::Gregorian bad(2003, 2, 29);
    std::cout << "created 2003-02-29 (wrong!): " << bad << std::endl;


    return 0;
}
