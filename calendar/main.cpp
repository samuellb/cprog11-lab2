#include "calendar.h"
#include "gregorian.h"
#include "menu.h"
#include "menu_item.h"
#include "kattistime.h"

template<typename T> int work() {
    set_k_time(std::time(NULL));
    lab2::Calendar<T> calendar;
    calendar.set_format(lab2::Calendar<T>::format::cal);

    Menu main_menu("Huvudmeny");
    Menu format_menu("Formatmeny");
    Menu event_menu("Händelsemeny");

    SelectDateMenuItem<T> select_date("Välj datum", calendar);
    main_menu.add(select_date);

    SelectMonthMenuItem<T> select_month("Välj månad", calendar);
    main_menu.add(select_month);

    main_menu.add(format_menu);
    main_menu.add(event_menu);
    
    SelectFormatMenuItem<T> format_list("Lista", calendar, lab2::Calendar<T>::format::list);
    SelectFormatMenuItem<T> format_calendar("Kalender", calendar, lab2::Calendar<T>::format::cal);
    SelectFormatMenuItem<T> format_ical("ical", calendar, lab2::Calendar<T>::format::icalendar);
    format_menu.add(format_list);
    format_menu.add(format_calendar);
    format_menu.add(format_ical);

    main_menu.run();

    return 0;
}

int main() {
    return work<lab2::Gregorian>();
}


