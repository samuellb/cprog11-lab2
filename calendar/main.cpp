#include "calendar.h"
#include "gregorian.h"
#include "menu.h"
#include "menu_item.h"
#include "kattistime.h"
#include "user_interface.h"

// Defines how the user interface should look like (used by the menu)
template<typename T> class CalendarUI : public UserInterface {
    public:
        CalendarUI(lab2::Calendar<T> & c) : calendar(c) { }
        
        virtual void print() {
            for (int i = 0; i < 30; i++) {
                std::cout << "\n"; // print newline without flushing output buffer
            }
            std::cout << calendar << std::endl;
        }
        
    private:
        lab2::Calendar<T> & calendar;
};

template<typename T> int work() {
    set_k_time(std::time(NULL));
    lab2::Calendar<T> calendar;
    calendar.set_format(lab2::Calendar<T>::format::cal);

    Menu main_menu("Huvudmeny");

    // Main menu
    CalendarMenuItem3<T, decltype(&lab2::Calendar<T>::set_date), int, int, int> select_date(
        "Välj datum", calendar, &lab2::Calendar<T>::set_date, {"år", "månad", "dag"});
    main_menu.add(select_date);

    CalendarMenuItem1<T, decltype(&lab2::Calendar<T>::set_month), int> select_month(
        "Välj månad", calendar, &lab2::Calendar<T>::set_month, {"månad"});
    main_menu.add(select_month);

    Menu format_menu("Formatmeny");
    Menu event_menu("Händelsemeny");
    main_menu.add(format_menu);
    main_menu.add(event_menu);
    
    // Format menu
    typedef CalendarMenuItemBound<T, decltype(&lab2::Calendar<T>::set_format), typename lab2::Calendar<T>::format> FormatMenuItem;
    
    FormatMenuItem format_list("Lista", calendar, &lab2::Calendar<T>::set_format, lab2::Calendar<T>::format::list);
    format_menu.add(format_list);
    
    FormatMenuItem format_cal("Kalender", calendar, &lab2::Calendar<T>::set_format, lab2::Calendar<T>::format::cal);
    format_menu.add(format_cal);
    
    FormatMenuItem format_ical("ical", calendar, &lab2::Calendar<T>::set_format, lab2::Calendar<T>::format::icalendar);
    format_menu.add(format_ical);
    
    // Event menu
    // TODO

    CalendarUI<T> ui(calendar);
    UserInterface::set_ui(ui);

    main_menu.run();

    return 0;
}

int main() {
    return work<lab2::Gregorian>();
}


