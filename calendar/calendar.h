#ifndef CALENDAR_H
#define CALENDAR_H

#include <string>
#include <iostream>
#include <map>
#include <stdexcept>
#include <iomanip>
#include "date.h"

namespace lab2 {

template <class T> class Calendar {
    
  public:

    enum format {list, cal, icalendar};

    Calendar() : date(), events(), outformat(list) { }
    
    template<typename U> Calendar(const Calendar<U> & cal) :
        date(cal.date),
        events(),
        outformat(cal.outformat) {

        typename std::multimap<U, std::string>::const_iterator it;
        for (it = cal.events.begin(); it != cal.events.end(); it++) {
            events.insert(std::pair<T, std::string>(it->first, it->second));
        }
    }
    
    template<typename U> Calendar & operator=(const Calendar<U> & cal) {
        
        date = cal.date;
        outformat = cal.outformat;
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

    bool move_event(const Date & from, const Date & to, std::string event) {
        return (remove_event(event, from.day(), from.month(), from.year()) &&
                add_event(event, to.day(), to.month(), to.year()));
    }

    void set_format(format outformat) {
        this->outformat = outformat;
    }

    std::ostream & format_cal(std::ostream & os) const {
        os << date.month_name() << " " << date.year() << std::endl;
        os << " må  ti  on  to  fr  lö  sö " << std::endl;
        T first_day_of_month = T(date.year(), date.month(), 1);
        int day = 1;
        for (int i = 1; i < 42; ++i) {
            if (i % 7 == 1 && i != 1) {
                os << std::endl;
            }
            if (i < first_day_of_month.week_day()) {
                os << "    ";
            } else if (i >= first_day_of_month.week_day() && day <= first_day_of_month.days_this_month()) {
                if (day == date.day())  {
                    os << "<" << std::setfill(' ') << std::setw(2) << day << std::resetiosflags(std::ios::left) << ">";
                } else {
                    os << " " << std::setfill(' ') << std::setw(2) << day << std::resetiosflags(std::ios::left);
                    T temp_date = T(date.year(), date.month(), day);
                    if (events.find(temp_date) != events.end()) {
                        os << "*";
                    } else {
                        os << " ";
                    }
                }
                day++;
            } else {

            }
        }
        os << std::endl << std::endl;

        typename std::multimap<T, std::string>::const_iterator it;
        for (it = events.begin(); it != events.end(); ++it) {
            os << (*it).first << " : " << (*it).second << std::endl;
        }
        os << std::endl;

        return os;
    }

    std::ostream & format_list(std::ostream & os) const {
        typename std::multimap<T, std::string>::const_iterator it;
        for (it = events.begin(); it != events.end(); ++it) {
            if ((*it).first > date) {
                os << (*it).first << " : " << (*it).second << std::endl;
            }
        }

        return os;
    }

    std::ostream & format_icalendar(std::ostream & os) const {
        os << "BEGIN:VCALENDAR" << std::endl;
        os << "VERSION:2.0" << std::endl;
        os << "PRODID:saker" << std::endl;
        typename std::multimap<T, std::string>::const_iterator it;
        for (it = events.begin(); it != events.end(); ++it) {
            os << "BEGIN:VEVENT" << std::endl;
            os << "DTSTART:" << (*it).first.year() << (*it).first.month() << (*it).first.day() << "T080000" << std::endl;
            os << "DTEND:" << (*it).first.year() << (*it).first.month() << (*it).first.day() << "T090000" << std::endl;
            os << "SUMMARY:" << (*it).second << std::endl;
            os << "END:VEVENT" << std::endl;
        }
        os << "END:VCALENDAR" << std::endl;

        return os;
    }

    friend std::ostream & operator<<(std::ostream & os, const Calendar<T> & calendar) {
        switch (calendar.outformat) {
            case list:
                return calendar.format_list(os);
            case cal:
                return calendar.format_cal(os);
            case icalendar:
                return calendar.format_icalendar(os);
        }
        return os;
    }

    T date;
    std::multimap<T, std::string> events;
    format outformat;
};

}

#endif


