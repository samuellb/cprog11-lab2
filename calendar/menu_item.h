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

class SelectDateMenuItem : public Action { 
    public:
        lab2::Calendar & calendar;
        SelectDateMenuItem(std::string n, lab2::Calendar & c) : Action(n), calendar(c) {}

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
        };
};

class SelectMonthMenuItem : public Action {
    public:
        SelectMonthMenuItem(std::string n) : Action(n) {}

        virtual void run() {};
};

#endif
