#include <iostream>
#include <ctime>
#include "calendar.h"
#include "gregorian.h"
#include "kattistime.h"

int main() {

    set_k_time(std::time(NULL));

    std::cout << "----------------------------------------" << std::endl;
    lab2::Calendar<lab2::Gregorian> cal;
    cal.set_date(2000, 12, 2);
    cal.add_event("Basketträning", 4, 12, 2000);
    cal.add_event("Basketträning", 11, 12, 2000);
    cal.add_event("Nyårsfrukost", 1, 1, 2001);
    cal.add_event("Första advent", 1); // år = 2000, månad = 12
    cal.add_event("Vårdagjämning", 20, 3); // år = 2000
    cal.add_event("Julafton", 24, 12);
    cal.add_event("Kalle Anka hälsar god jul", 24); // också på julafton
    cal.add_event("Julafton", 24); // En likadan händelse samma datum ska
    // ignoreras och inte sättas in i kalendern
    cal.add_event("Min första cykel", 20, 12, 2000);
    cal.remove_event("Basketträning", 4);
    std::cout << cal; // OBS! Vårdagjämning och första advent är
    // före nuvarande datum och skrivs inte ut
    std::cout << "----------------------------------------" << std::endl;
    cal.remove_event("Vårdagjämning", 20, 3, 2000);
    cal.remove_event("Kalle Anka hälsar god jul", 24, 12, 2000);
    cal.set_date(2000, 11, 2);
    if (! cal.remove_event("Julafton", 24)) {
        std::cout << " cal.remove_event(\"Julafton\", 24) tar inte"<< std::endl
            << " bort något eftersom aktuell månad är november" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << cal;

    std::cout << "----------------------------------------" << std::endl;
    lab2::Calendar<lab2::Gregorian> calendar;
    calendar.set_date(2007, 12, 2);
    calendar.set_format(lab2::Calendar<lab2::Gregorian>::cal);
    calendar.add_event("Julafton", 24, 12, 2007);
    calendar.add_event("Min andra cykel", 20, 12, 2007);
    std::cout << calendar;

    return 0;
}
