#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

namespace lab2 {

class Date {
    
  public:
    
    Date(int d) : date(d) { }
    
    virtual int year() const = 0;
    virtual int month() const = 0;
    virtual int day() const = 0;
    virtual int week_day() const = 0;
    virtual int days_per_week() const = 0;
    virtual int days_this_month() const = 0;
    virtual int months_per_year() const = 0;
    virtual const std::string & week_day_name() const = 0;
    virtual const std::string & month_name() const = 0;
    
    inline Date & operator++() { ++date; return *this; }
    inline Date & operator--() { --date; return *this; }
    inline Date & operator+=(const int & days) { date += days; return *this; }
    inline Date & operator-=(const int & days) { date -= days; return *this; }
    
    virtual void add_year(int = 1) = 0;
    virtual void add_month(int = 1) = 0;
    
    inline bool operator==(const Date & other) const  { return date == other.date; }
    inline bool operator!=(const Date & other) const  { return date != other.date; }
    
    inline bool operator<(const Date & other) const { return date < other.date; }
    inline bool operator<=(const Date & other) const { return date <= other.date; }
    inline bool operator>(const Date & other) const { return date > other.date; }
    inline bool operator>=(const Date & other) const { return date >= other.date; }
    
    inline int operator-(const Date & other) const { return date - other.date; }
    
    inline int mod_julian_day() const { return date; }
    
    friend std::ostream & operator<<(std::ostream & os, const Date &);
    
    virtual ~Date() = 0;
    
  private:
    
    /**
     * Internal representation of a date, in days since the "modified julian
     * day", which is november 17th, 1858.
     */
    int date;
    
};

}

#endif

