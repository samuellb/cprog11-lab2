
#include "western_date.h"

namespace lab2 {


int WesternDate::week_day() const {
    // TODO fix
    return (mod_julian_day() + 42) % 7;
}

int WesternDate::days_per_week() const {
    return 7;
}

int WesternDate::months_per_year() const {
    return 12;
}

const std::string & WesternDate::week_day_name() const {
    static const std::string day_names[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
    };
    return day_names[week_day()];
}


}


