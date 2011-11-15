#include <iostream>
#include <ctime>
#include "calendar.h"
#include "gregorian.h"
#include "kattistime.h"

int main() {

    set_k_time(std::time(NULL));

    std::cout << "----------------------------------------" << std::endl;
    lab2::Calendar<lab2::Gregorian> cal;
    cal.set_date(2000, 11, 1);
    cal.add_event("Beställa dator", 4, 11, 2000);
    cal.add_related_event(lab2::Gregorian(2000, 11, 4), 7, "Beställa dator", "Hämta dator");
    cal.add_related_event(lab2::Gregorian(2000, 11, 11), -1, "Hämta dator", "Kolla karta");
    
    cal.add_related_event(lab2::Gregorian(2000, 11, 4), 30, "Beställa dator", "Lämna tillbaka dator");
    
    std::cout << "----------------------------------------" << std::endl;
    std::cout << cal;

    std::cout << "----------------------------------------" << std::endl;
    
    cal.remove_event("Hämta dator", 11, 11, 2000);
    
    std::cout << cal;

    return 0;
}
