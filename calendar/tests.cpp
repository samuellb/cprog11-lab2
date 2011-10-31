#include <cxxtest/TestSuite.h>
#include <stdexcept>

#include "date.h"
#include "julian.h"
#include "gregorian.h"

class DateTestSuite : public CxxTest::TestSuite 
{
public:

    // Testcase 1

    // Tests the year/month/day getters.

    void test_1_getters(void)
    {
        static const int dates[][3] = {
            { 2000, 1, 1 },
            { 2000, 1, 20 },
            { 2000, 12, 20 },
        };
        
        for (int c = 0; c < 2; ++c) {
            for (int d = 0; d < 3; ++d) {
                lab2::Date* cal = (c ?
                    static_cast<lab2::Date*>(new lab2::Gregorian(dates[d][0], dates[d][1], dates[d][2])) :
                    static_cast<lab2::Date*>(new lab2::Julian(dates[d][0], dates[d][1], dates[d][2])));
                
                TS_ASSERT_EQUALS(cal->year(), dates[d][0]);
                TS_ASSERT_EQUALS(cal->month(), dates[d][1]);
                TS_ASSERT_EQUALS(cal->day(), dates[d][2]);
                
                delete cal;
            }
        }
    }
    
    
};


