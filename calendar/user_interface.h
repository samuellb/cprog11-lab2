#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "calendar.h"

class UserInterface {
    public:
        virtual ~UserInterface();
        virtual void print() = 0;
        
        // Static methods
        static void set_ui(UserInterface &);
        static void call_print();

    private:
        static UserInterface *user_interface;
};

#endif


