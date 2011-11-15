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
        std::set<std::pair<T, std::string>> related;
        
        bool is_related;
        std::pair<T, std::string> related_by;
        
        bool birthday;
        
        Event(T d, std::string s, bool bday=false) :
            date(d),
            name(s),
            related(),
            is_related(false),
            related_by(),
            birthday(bday) { }
        
        Event(T d, std::string s, const Event &relby, bool bday=false) :
            date(d),
            name(s),
            related(),
            is_related(true),
            related_by(std::make_pair(relby.date, relby.name)),
            birthday(bday) { }
        
        friend std::ostream & operator<<(std::ostream & os, const Event &event) {
            os << event.name;
            if (event.birthday) {
                os << " ";
                bool birth = true;
                if (event.is_related) {
                    int age = event.date.year() - event.related_by.first.year();
                    if (age > 0) {
                        os << age;
                        os << " years";
                        birth = false;
                    }
                }
                
                if (birth) {
                    os << "was born";
                }
            }
            return os;
        }
    };

    Calendar() : date(), events(), outformat(list) { }
    
    template<typename U> Calendar(const Calendar<U> & cal) :
        date(cal.date),
        events(),
        outformat(cal.outformat) {

        for (auto it = cal.events.begin(); it != cal.events.end(); ++it) {
            events.insert(std::pair<T, Event>(it->first, it->second));
        }
    }
    
    template<typename U> Calendar & operator=(const Calendar<U> & cal) {
        
        date = cal.date;
        outformat = cal.outformat;
        events.clear();

        for (auto it = cal.events.begin(); it != cal.events.end(); ++it) {
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
            T date(year, month, day);
            return add_event(Event(date, s));
        } catch (std::out_of_range) {
            return false;
        }
    }
    
    bool add_event(const Event &event) {
        for (auto it = events.begin(); it != events.end(); ++it) {
            if (it->first == event.date && it->second.name == event.name) {
                return false;
            }
        }

        events.insert(std::pair<T, Event>(event.date, event));
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
        for (auto it = events.begin(); it != events.end(); ++it) {
            Event &event = it->second;
            
            if (it->first == date && event.name == s) {
                // remove from parent that this event is related to
                if (event.is_related) {
                    detach(event);
                }
                
                // remove related events
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
        auto range = events.equal_range(event.date);
        
        for (auto it = range.first; it != range.second; ++it) {
            Event &rel_obj = it->second;
            if (rel_obj.name == event.name) {
                rel_obj.related.erase(std::make_pair(event.date, event.name));
                return;
            }
        }
    }

    bool move_event(const Date & from, const Date & to, std::string event) {
        return move_event(from, to, event, false, date);
    }

    bool move_event(const Date & from, const Date & to, std::string event,
                    bool moved_parent, const Date& new_parent_date) {
        int diff = to - from;
        
        // Find main event
        auto range = events.equal_range(T(from));
        for (auto it = range.first; it != range.second; ++it) {
            Event &main = it->second;
            if (main.name == event) {
                // Update reference in parent
                if (main.is_related) {
                    bool found = false;
                    auto range = events.equal_range(main.related_by.first);
                    for (auto it = range.first; it != range.second; ++it) {
                        Event &parent = it->second;
                        if (parent.name == main.related_by.second) {
                            // Update in vector
                            for (auto rit = parent.related.begin(); rit != parent.related.end(); ++rit) {
                                if (rit->first == main.date && rit->second == main.name) {
                                    auto modified = *rit;
                                    modified.first = to;
                                    
                                    parent.related.insert(modified);
                                    parent.related.erase(rit);
                                    found = true;
                                    break;
                                }
                            }
                        }
                    }
                    
                    if (!found) {
                        throw std::logic_error("should not happen");
                    }
                }

                // Move related events
                for (auto event : std::set<std::pair<T, std::string>>(main.related)) {
                    T new_date(event.first);
                    new_date += diff;
                    
                    move_event(event.first, new_date, event.second, true, to);
                }
                
                // Update references to parent
                if (moved_parent) {
                    main.related_by.first = new_parent_date;
                }
                
                // Move this event
                Event main_copy = main;
                events.erase(it);
                main_copy.date = to;
                events.insert(std::make_pair(T(to), main_copy));
                return true;
            }
        }
        return false;
    }
    
    bool add_related_event(const Date & rel_date, int days,
                           std::string rel_event, std::string new_event,
                           bool bday=false) {
        // Find main event
        auto range = events.equal_range(T(rel_date));
        
        for (auto it = range.first; it != range.second; ++it) {
            Event &rel_obj = it->second; // main object
            if (rel_obj.name == rel_event) {
                
                // Found
                
                // Add
                T new_date(rel_date);
                new_date += days;
                
                Event new_obj(new_date, new_event, rel_obj, bday);
                if (!add_event(new_obj)) return false;
                
                // Add relation
                rel_obj.related.insert(std::make_pair(new_date, new_event));
                
                return true;
            }
        }
        return false;
        
    }
    
    bool add_yearly_event(const Date & date, std::string name, int num_recur=100) {
        // First one
        if (!add_event(Event(date, name))) return false;
        
        T d(date);
        bool ok = true;
        for (int i = 0; i < num_recur; ++i) {
            d.add_year(1);
            if (!add_related_event(date, d - date, name, name))
                ok = false;
        }
        
        return ok;
    }
    
    bool add_weekly_event(const Date & date, std::string name, int num_recur=100) {
        // First one
        if (!add_event(Event(date, name))) return false;
        
        T d(date);
        bool ok = true;
        for (int i = 0; i < num_recur; ++i) {
            d += d.days_per_week();
            if (!add_related_event(date, d - date, name, name))
                ok = false;
        }
        
        return ok;
    }
    
    bool add_birthday(const Date & birth_date, std::string name, int years_in_future=15) {        
        // First one
        if (!add_event(Event(birth_date, name, true))) return false;
        
        bool ok = true;
        int years = date.year() - birth_date.year() + years_in_future;
        
        for (int i = 1; i < years; ++i) {
            T d(birth_date);
            d.add_year(i);
            if (!add_related_event(birth_date, d - birth_date, name, name, true))
                ok = false;
        }
        
        return ok;
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

        for (auto it = events.begin(); it != events.end(); ++it) {
            os << it->first << " : " << it->second << std::endl;
        }
        os << std::endl;

        return os;
    }

    std::ostream & format_list(std::ostream & os) const {
        for (auto it = events.begin(); it != events.end(); ++it) {
            if (it->first > date) {
                os << it->first << " : " << it->second << std::endl;
            }
        }

        return os;
    }

    std::ostream & format_icalendar(std::ostream & os) const {
        os << "BEGIN:VCALENDAR" << std::endl;
        os << "VERSION:2.0" << std::endl;
        os << "PRODID:saker" << std::endl;
        for (auto it = events.begin(); it != events.end(); ++it) {
            os << "BEGIN:VEVENT" << std::endl;
            os << "DTSTART:" << it->first.year();
            os << std::setfill('0') << std::setw(2) << it->first.month() << std::resetiosflags(std::ios::left);
            os << std::setfill('0') << std::setw(2) << it->first.day() << std::resetiosflags(std::ios::left) << "T080000" << std::endl;
            os << "DTEND:" << it->first.year();
            os << std::setfill('0') << std::setw(2) << it->first.month() << std::resetiosflags(std::ios::left);
            os << std::setfill('0') << std::setw(2) << it->first.day() << std::resetiosflags(std::ios::left) << "T090000" << std::endl;
            os << "SUMMARY:" << it->second << std::endl;
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


