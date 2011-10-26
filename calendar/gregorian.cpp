namespace lab2 {

Gregorian::Gregorian() {

}

Gregorian::Gregorian(int year, int month, int day) {
    int a = (14 - month) / 12;
    int y = 4800 + year - a;
    int m = month + 12 * a - 3;

    date = day + ((153 * m + 2) / 5) + 365 * y + (y / 4) - (y / 100) + (y / 400) - 32045;
}

Gregorian::Gregorian(const Date &) {

}
    
};

}
