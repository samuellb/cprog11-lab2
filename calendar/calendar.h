#ifndef CALENDAR_H
#define CALENDAR_H

#include <string>
#include <set>
#include <iostream>
#include <map>
#include <stdexcept>
#include <iomanip>
#include "date.h"

namespace lab2 {

template <class T> class Calendar {
    
  public:

    enum format {list, cal, icalendar};

    struct Event {
        T date;
        std::string name;
        std::set<std::pair<T, std::string> > related;
        bool is_related;
        std::pair<T, std::string> related_by;
        
        Event(T d, std::string s) :
            date(d),
            name(s),
            related(),
            is_related(false),
            related_by() { }
        
        Event(T d, std::string s, const Event &relby) :
            date(d),
            name(s),
            related(),
            is_related(true),
            related_by(std::make_pair(relby.date, relby.name)) { }
    };

    Calendar() : date(), events(), outformat(list) { }
    
    template<typename U> Calendar(const Calendar<U> & cal) :
        date(cal.date),
        events(),
        outformat(cal.outformat) {

        typename std::multimap<U, Event>::const_iterator it;
        for (it = cal.events.begin(); it != cal.events.end(); it++) {
            events.insert(std::pair<T, Event>(it->first, it->second));
        }
    }
    
    template<typename U> Calendar & operator=(const Calendar<U> & cal) {
        
        date = cal.date;
        outformat = cal.outformat;
        events.clear();

        typename std::multimap<U, Event>::const_iterator it;
        for (it = cal.events.begin(); it != cal.events.end(); it++) {
            events.insert(std::pair<T, Event>(it->first, it->second));
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
            return add_event(T(year, month, day), s);
        } catch (std::out_of_range) {
            return false;
        }
    }
    
    bool add_event(const T &date, std::string s) {
        typename std::multimap<T, Event>::iterator it;
        for (it = events.begin(); it != events.end(); it++) {
            if (it->first == date && it->second.name == s) {
                return false;
            }
        }

        events.insert(std::pair<T, Event>(date, Event(date, s)));
        return true;
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
            return remove_event(T(year, month, day), s);
        } catch (std::out_of_range) {
            return false;
        }
    }

    bool remove_event(const T& date, std::string s) {
        typename std::multimap<T, Event>::iterator it;
        for (it = events.begin(); it != events.end(); it++) {
            Event &event = it->second;
            if (it->first == date && event.name == s) {
                // remove from parent that this event is related to
                if (event.is_related) {
                    detach(event);
                }
                
                // remove related events
                //typename std::vector<T>::iterator it = event.related;
                for (auto pair : event.related) {
                    remove_event(pair.first, pair.second);
                }
                
                events.erase(it);
                return true;
            }
        }

        return false;
    }
    
    void detach(Event &event) {
        typename std::pair<typename std::multimap<T, Event>::iterator,
                           typename std::multimap<T, Event>::iterator> range =
            events.equal_range(event.date);
        
        for (typename std::multimap<T, Event>::iterator it = range.first;
             it != range.second; ++it) {
            
            Event &rel_obj = it->second;
            if (rel_obj.name == event.name) {
                rel_obj.related.erase(std::make_pair(event.date, event.name));
                return;
            }
        }
    }

    bool move_event(const Date & from, const Date & to, std::string event) {
        // TODO update
        return (remove_event(event, from.day(), from.month(), from.year()) &&
                add_event(event, to.day(), to.month(), to.year()));
    }
    
    bool add_related_event(const Date & rel_date, int days,
                           std::string rel_event, std::string new_event) {
        // Find main event
        typename std::pair<typename std::multimap<T, Event>::iterator,
                           typename std::multimap<T, Event>::iterator> range =
            events.equal_range(T(rel_date));
        
        for (typename std::multimap<T, Event>::iterator it = range.first; it != range.second; ++it) {
            Event &rel_obj = it->second;
            if (rel_obj.name == rel_event) {
                
                // Found
                
                // Add
                T new_date(rel_date);
                new_date += days;
                
                if (!add_event(new_date, new_event)) return false;
                
                // Add relation
                rel_obj.related.insert(std::make_pair(new_date, new_event));
                
                return true;
            }
        }
        return false;
        
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

        typename std::multimap<T, Event>::const_iterator it;
        for (it = events.begin(); it != events.end(); ++it) {
            os << (*it).first << " : " << (*it).second.name << std::endl;
        }
        os << std::endl;

        return os;
    }

    std::ostream & format_list(std::ostream & os) const {
        typename std::multimap<T, Event>::const_iterator it;
        for (it = events.begin(); it != events.end(); ++it) {
            if ((*it).first > date) {
                os << (*it).first << " : " << (*it).second.name << std::endl;
            }
        }

        return os;
    }

    std::ostream & format_icalendar(std::ostream & os) const {
        os << "BEGIN:VCALENDAR" << std::endl;
        os << "VERSION:2.0" << std::endl;
        os << "PRODID:saker" << std::endl;
        typename std::multimap<T, Event>::const_iterator it;
        for (it = events.begin(); it != events.end(); ++it) {
            os << "BEGIN:VEVENT" << std::endl;
            os << "DTSTART:" << (*it).first.year() << (*it).first.month() << (*it).first.day() << "T080000" << std::endl;
            os << "DTEND:" << (*it).first.year() << (*it).first.month() << (*it).first.day() << "T090000" << std::endl;
            os << "SUMMARY:" << (*it).second.name << std::endl;
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
    std::multimap<T, Event> events;
    format outformat;
};

}

#endif


