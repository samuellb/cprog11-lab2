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
            T date(year, month, day);
            return add_event(Event(date, s));
        } catch (std::out_of_range) {
            return false;
        }
    }
    
    bool add_event(const Event &event) {
        typename std::multimap<T, Event>::iterator it;
        for (it = events.begin(); it != events.end(); it++) {
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
        typename std::multimap<T, Event>::iterator it;
        for (it = events.begin(); it != events.end(); it++) {
            Event &event = it->second;
            
            if (it->first == date && event.name == s) {
                // remove from parent that this event is related to
                if (event.is_related) {
                    std::cout << "remove parent" << std::endl;
                    detach(event);
                }
                
                // remove related events
                for (auto pair : event.related) {
                    std::cout << "   removed rleated " << pair.first << " " << pair.second << std::endl;
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
                    //auto range = events.equal_range(main.related_by.first);
                    typename std::pair<typename std::multimap<T, Event>::iterator,
                           typename std::multimap<T, Event>::iterator> range = events.equal_range(main.related_by.first);
                    std::cout << "is related by " << main.related_by.first << " "<< main.related_by.second << std::endl;
                    //for (auto it = range.first; it != range.second; ++it) {
                    typename std::multimap<T, Event>::iterator it;
                    for (it = range.first; it != range.second; ++it) {
                        Event &parent = it->second;
                        std::cout << "in" << std::endl;
                        if (parent.name == main.related_by.second) {
                            // Update in vector
                            std::cout << "in parent" << std::endl;
                            //typename std::set<typename std::pair<T, std::string>>::iterator rit;
                            //for (typename std::pair<T, std::string> &event : parent.related) {
                            /*for (auto rit = parent.related.begin(); rit != parent.related.end(); ++rit) {
                                if (rit->first == main.date && rit->second == main.name) {
                                    
                                    //std::pair<T, std::string> &pair = *rit;
                                    //std::pair<T, std::string> &pair = const_cast<std::pair<T, std::string>*>(*rit);
                                    //pair.first = to;
                                    const T &to_ref = (*rit).first;
                                    const_cast<T&>(to_ref) = to;
                                    //(*rit).first = to;
                                    std::cout << "   set to to " << to << std::endl;
                                    found = true;
                                }
                            }*/
                            
                            for (auto rit = parent.related.begin(); rit != parent.related.end(); ++rit) {
                                if (rit->first == main.date && rit->second == main.name) {
                                    std::cout << "   old value " << rit->first << std::endl;
                                    auto modified = *rit;
                                    modified.first = to;
                                    
                                    std::cout << "   set to " << modified.first << std::endl;
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
                    
                    
                    {
                    typename std::pair<typename std::multimap<T, Event>::iterator,
                           typename std::multimap<T, Event>::iterator> range = events.equal_range(main.related_by.first);
                    std::cout << "is related by " << main.related_by.first << " "<< main.related_by.second << std::endl;
                    //for (auto it = range.first; it != range.second; ++it) {
                    typename std::multimap<T, Event>::iterator it;
                    for (it = range.first; it != range.second; ++it) {
                        Event &parent = it->second;
                        std::cout << "in" << std::endl;
                        if (parent.name == main.related_by.second) {
                            for (auto rit = parent.related.begin(); rit != parent.related.end(); ++rit) {
                                if (rit->second == main.name) {
                                    std::cout << "   new value " << rit->first << std::endl;
                                    break;
                                }
                            }
                        }
                    }
                    }
                }
                std::cout << "update related_by" << std::endl;

                // Move related events
                for (auto event : std::set<std::pair<T, std::string>>(main.related)) {
                    T new_date(event.first);
                    new_date += diff;
                    
                    std::cout << "recursive move " <<  event.second << std::endl;
                    move_event(event.first, new_date, event.second, true, to);
                    std::cout << "out " <<  event.second << std::endl;
                }
                
                // Update references to parent
                std::cout << "move parent" << std::endl;
                if (moved_parent) {
                    main.related_by.first = new_parent_date;
                }
                std::cout << "move this" << std::endl;
                                
                // Move this event
                Event main_copy = main;
                std::cout << "erase" << std::endl;
                events.erase(it);
                std::cout << "modify" << std::endl;
                main_copy.date = to;
                std::cout << "insert" << std::endl;
                events.insert(std::make_pair(T(to), main_copy));
                std::cout << "loop" << std::endl;
                
                return true;
            }
        }
        return false;
    }
    
    bool add_related_event(const Date & rel_date, int days,
                           std::string rel_event, std::string new_event) {
        // Find main event
        typename std::pair<typename std::multimap<T, Event>::iterator,
                           typename std::multimap<T, Event>::iterator> range =
            events.equal_range(T(rel_date));
        
        for (typename std::multimap<T, Event>::iterator it = range.first; it != range.second; ++it) {
            Event &rel_obj = it->second; // main object
            if (rel_obj.name == rel_event) {
                
                // Found
                
                // Add
                T new_date(rel_date);
                new_date += days;
                
                Event new_obj(new_date, new_event, rel_obj);
                std::cout << "  adding rel obj to " << rel_obj.name << " :  " << new_obj.name << "    xx " << new_obj.related_by.second << std::endl;
                if (!add_event(new_obj)) return false;
                
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
                os << (*it).first << " : " << (*it).second.name << " -- relby:" << it->second.related_by.first << it->second.related_by.second << "   relateds: " << it->second.related.size() << std::endl;
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


