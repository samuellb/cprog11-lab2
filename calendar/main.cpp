#include "calendar.h"
#include "gregorian.h"
#include "menu.h"
#include "menu_item.h"
#include "kattistime.h"

template<typename T> int work() {
    set_k_time(std::time(NULL));
    lab2::Calendar<T> calendar;

    Menu main_menu("Huvudmeny");
    Menu format_menu("Formatmeny");
    Menu event_menu("Händelsemeny");

    SelectDateMenuItem<T> select_date("Välj datum", calendar);
    main_menu.add(select_date);

    SelectMonthMenuItem<T> select_month("Välj månad", calendar);
    main_menu.add(select_month);

    main_menu.add(format_menu);
    main_menu.add(event_menu);

    main_menu.run();

    return 0;
}

int main() {
    return work<lab2::Gregorian>();
}


