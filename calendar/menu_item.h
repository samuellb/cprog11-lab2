#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <iostream>

#include "calendar.h"
#include "action.h"

class MenuItem : public Action {
    public:
        MenuItem(std::string n) : Action(n) {}
        virtual ~MenuItem() {}
};

template<typename T> class SelectDateMenuItem : public MenuItem {
    public:
        SelectDateMenuItem(std::string n, lab2::Calendar<T> & c) : MenuItem(n), calendar(c) {}

        virtual void run() {
            int year = UserInterface::read("år");
            int month = UserInterface::read("månad");
            int day = UserInterface::read("dag");

            UserInterface::check_input(calendar.set_date(year, month, day));
        }
        
    private:
        lab2::Calendar<T> & calendar;
};

template<typename T> class SelectMonthMenuItem : public MenuItem {
    public:
        SelectMonthMenuItem(std::string n, lab2::Calendar<T> & c) : MenuItem(n), calendar(c) {}

        virtual void run() {
            int month = UserInterface::read("månad");

            UserInterface::check_input(calendar.set_month(month));
        };
        
    private:
        lab2::Calendar<T> & calendar;
};

template<typename T> class SelectFormatMenuItem : public MenuItem {
    public:
        SelectFormatMenuItem(std::string n, lab2::Calendar<T> & c, typename lab2::Calendar<T>::format f) : MenuItem(n), calendar(c), format(f) {}

        virtual void run() {
            calendar.set_format(format);
        };
        
    private:
        lab2::Calendar<T> & calendar;
        const typename lab2::Calendar<T>::format format;
};

#endif
