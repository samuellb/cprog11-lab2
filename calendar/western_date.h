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

  protected:
    virtual bool leap_year(int year) const = 0;
    bool leap_year() const;
};

}

#endif

