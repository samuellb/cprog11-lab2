#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <iostream>
#include <vector>

#include "calendar.h"
#include "action.h"

class MenuItem : public Action {
    public:
        MenuItem(std::string n) : Action(n) {}
        virtual ~MenuItem() {}
};

template<typename C, typename M, typename A1, typename A2, typename A3> class CalendarMenuItem3 : public MenuItem {
    public:
        CalendarMenuItem3(std::string n, lab2::Calendar<C> & c, M m, std::vector<std::string> p) :
            MenuItem(n),
            calendar(c),
            method(m),
            prompts(p) {}

        virtual void run() {
            A1 a1 = UIRead::read<A1>(prompts[0]);
            A2 a2 = UIRead::read<A2>(prompts[1]);
            A3 a3 = UIRead::read<A3>(prompts[2]);

            UserInterface::check_input((calendar.*method)(a1, a2, a3));
        }
        
    private:
        lab2::Calendar<C> & calendar;
        M method;
        std::vector<std::string> prompts;
};

template<typename C, typename M, typename A1, typename A2> class CalendarMenuItem2 : public MenuItem {
    public:
        CalendarMenuItem2(std::string n, lab2::Calendar<C> & c, M m, std::vector<std::string> p) :
            MenuItem(n),
            calendar(c),
            method(m),
            prompts(p) {}

        virtual void run() {
            A1 a1 = UIRead::read<A1>(prompts[0]);
            A2 a2 = UIRead::read<A2>(prompts[1]);

            UserInterface::check_input((calendar.*method)(a1, a2));
        }
        
    private:
        lab2::Calendar<C> & calendar;
        M method;
        std::vector<std::string> prompts;
};

template<typename C, typename M, typename A1> class CalendarMenuItem1 : public MenuItem {
    public:
        CalendarMenuItem1(std::string n, lab2::Calendar<C> & c, M m, std::vector<std::string> p) :
            MenuItem(n),
            calendar(c),
            method(m),
            prompts(p) {}

        virtual void run() {
            A1 a1 = UIRead::read<A1>(prompts[0]);

            UserInterface::check_input((calendar.*method)(a1));
        }
        
    private:
        lab2::Calendar<C> & calendar;
        M method;
        std::vector<std::string> prompts;
};

// This "binds" a parameter to the function
template<typename C, typename M, typename A1> class CalendarMenuItemBound : public MenuItem {
    public:
        CalendarMenuItemBound(std::string n, lab2::Calendar<C> & c, M m, A1 a1) :
            MenuItem(n),
            calendar(c),
            method(m),
            argument1(a1) {}

        virtual void run() {
            (calendar.*method)(argument1);
        }
        
    private:
        lab2::Calendar<C> & calendar;
        M method;
        A1 argument1;
};

#endif
