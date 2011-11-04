#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

namespace lab2 {

class Date {
    
  public:

    Date();
    Date(int d);
    Date(const Date &);
    
    inline int year() const { calc(); return calc_year; }
    inline int month() const { calc(); return calc_month; }
    inline int day() const { calc(); return calc_day; }
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
    
    inline int mod_julian_day() const { return date - 2400001; }
    
    friend std::ostream & operator<<(std::ostream & os, const Date &);
    
    virtual ~Date();
    
  protected:
   
    virtual void calc() const = 0;
    virtual void set_date(int, int, int) = 0;

    /**
     * Internal representation of a date, in days since the "julian day", which
     * is January 1st, 4713 BC.
     */
    int date;

    mutable int calculated_date;
    mutable int calc_year, calc_month, calc_day;

};

}

#endif


