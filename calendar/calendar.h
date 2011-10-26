#ifndef CALENDAR_H
#define CALENDAR_H

#include <string>
#include <iostream>
#include <map>
#include <stdexcept>
#include "date.h"

namespace lab2 {

template <class T> class Calendar {
    
  public:

    Calendar() : date(), events() { }
    
    template<typename U> Calendar(const Calendar<U> & cal) :
        date(cal.date),
        events() {
        
        typename std::multimap<U, std::string>::const_iterator it;
        for (it = cal.events.begin(); it != cal.events.end(); it++) {
            events.insert(std::pair<T, std::string>(it->first, it->second));
        }
    }
    
    template<typename U> Calendar & operator=(const Calendar<U> & cal) {
        
        date = cal.date;
        events.clear();
        
        typename std::multimap<U, std::string>::const_iterator it;
        for (it = cal.events.begin(); it != cal.events.end(); it++) {
            events.insert(std::pair<T, std::string>(it->first, it->second));
        }
        
        return *this;
    }

    bool set_date(int year, int month, int day) {
        try {
            date = T(year, month, day);
        } catch (std::out_of_range) {
            return false;
        }

        return true;
    }

    bool add_event(std::string s) {
        return add_event(s, date.day(), date.month(), date.year());
    }

    bool add_event(std::string s, int day) {
        return add_event(s, day, date.month(), date.year());
    }

    bool add_event(std::string s, int day, int month) {
        return add_event(s, day, month, date.year());
    }

    bool add_event(std::string s, int day, int month, int year) {
        try {
            T temp_date = T(year, month, day);

            typename std::multimap<T, std::string>::iterator it;
            for (it = events.begin(); it != events.end(); it++) {
                if (it->first == temp_date && it->second == s) {
                    return false;
                }
            }

            events.insert(std::pair<T, std::string>(temp_date, s));
            return true;
        } catch (std::out_of_range) {
            return false;
        }
    }

    bool remove_event(std::string s) {
        return remove_event(s, date.day(), date.month(), date.year());
    }

    bool remove_event(std::string s, int day) {
        return remove_event(s, day, date.month(), date.year());
    }

    bool remove_event(std::string s, int day, int month) {
        return remove_event(s, day, month, date.year());
    }

    bool remove_event(std::string s, int day, int month, int year) {
        try {
            T temp_date = T(year, month, day);

            typename std::multimap<T, std::string>::iterator it;
            for (it = events.begin(); it != events.end(); it++) {
                if (it->first == temp_date && it->second == s) {
                    events.erase(it);
                    return true;
                }
            }

            return false;
        } catch (std::out_of_range) {
            return false;
        }
    }

    friend std::ostream & operator<<(std::ostream & os, const Calendar<T> & calendar) {
        typename std::multimap<T, std::string>::const_iterator it;
        for (it = calendar.events.begin(); it != calendar.events.end(); it++)
            if ((*it).first >= calendar.date)
                os << (*it).first << " : " << (*it).second << std::endl;

        return os;
    }

//  private:
    T date;
    std::multimap<T, std::string> events;
};

}

#endif


