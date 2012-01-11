#include "calendar.h"
#include "gregorian.h"
#include "menu.h"
#include "menu_item.h"
#include "kattistime.h"

int main() {
    set_k_time(std::time(NULL));
    lab2::Calendar<lab2::Gregorian> calendar;

    Menu main_menu("Huvudmeny");
    Menu format_menu("Formatmeny");
    Menu event_menu("Händelsemeny");

    SelectDateMenuItem select_date("Välj datum", calendar);
    main_menu.add(select_date);

    SelectMonthMenuItem select_month("Välj månad", calendar);
    main_menu.add(select_month);

    main_menu.add(format_menu);
    main_menu.add(event_menu);

    main_menu.run();

    return 0;
}


