#ifndef GREGORIAN_DATE_H
#define GREGORIAN_DATE_H

namespace lab2 {

class Julian : public WesternDate {
    
  public:    
    Julian();
    Julian(int, int, int);
    Julian(const Date &);
    
};

}

#endif
