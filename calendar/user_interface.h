#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>

#include "calendar.h"

class UserInterface {
    public:
        virtual ~UserInterface();
        virtual void print() = 0;
        
        // Static methods
        static void set_ui(UserInterface &);
        static void call_print();
        
        static int read(std::string);
        static void check_input(bool);

    private:
        static UserInterface *user_interface;
};

#endif


