#ifndef JULIAN_DATE_H
#define JULIAN_DATE_H

#include "western_date.h"

namespace lab2 {

class Julian : public WesternDate {
    
  public:    
    Julian();
    Julian(int, int, int);
    Julian(const Date &);

    using Date::operator++;
    using Date::operator--;

    inline Julian operator++(int) {
        Julian d = *this;
        ++date;
        return d;
    }
    inline Julian operator--(int) {
        Julian d = *this;
        --date;
        return d;
    }

    virtual void calc() const;
    virtual void set_date(int, int, int);
};

}

#endif
