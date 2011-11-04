#ifndef WESTERN_DATE_H
#define WESTERN_DATE_H

#include "date.h"

namespace lab2 {

class WesternDate : public Date {
    
  public:
    WesternDate();
    WesternDate(const Date & d);

    virtual int week_day() const;
    virtual int days_per_week() const;
    virtual int days_this_month() const;
    virtual int months_per_year() const;
    virtual const std::string & week_day_name() const;
    virtual const std::string & month_name() const;

    virtual void add_year(int = 1);
    virtual void add_month(int = 1);

  protected:
    virtual bool leap_year(int) const = 0;
    int days_that_month(int year, int month) const;
    bool leap_year() const;
};

}

#endif

