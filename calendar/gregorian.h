#ifndef GREGORIAN_DATE_H
#define GREGORIAN_DATE_H

namespace lab2 {

class Gregorian : public WesternDate {
    
  public:    
    Gregorian();
    Gregorian(int, int, int);
    Gregorian(const Date &);
    
};

}

#endif
