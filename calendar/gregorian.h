#ifndef GREGORIAN_DATE_H
#define GREGORIAN_DATE_H

#include "western_date.h"

namespace lab2 {

class Gregorian : public WesternDate {
    
  public:    
    Gregorian();
    Gregorian(int, int, int);
    Gregorian(const Date &);

    using Date::operator++;
    using Date::operator--;

    inline Gregorian operator++(int) { 
        Gregorian d = *this; 
        ++date;
        return d;
    }
    inline Gregorian operator--(int) {
        Gregorian d = *this;
        --date;
        return d;
    }

    virtual void calc() const;
    virtual void set_date(int, int, int);
};

}

#endif
