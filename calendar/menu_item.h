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
            unsigned int year, month, day;
            std::cout << "år > ";
            std::cin >> year;
            std::cout << "månad > ";
            std::cin >> month;
            std::cout << "dag > ";
            std::cin >> day;

            calendar.set_date(year, month, day);
            std::cout << calendar << std::endl;
        }
        
    private:
        lab2::Calendar<T> & calendar;
};

template<typename T> class SelectMonthMenuItem : public MenuItem {
    public:
        SelectMonthMenuItem(std::string n, lab2::Calendar<T> & c) : MenuItem(n), calendar(c) {}

        virtual void run() {};
        
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
