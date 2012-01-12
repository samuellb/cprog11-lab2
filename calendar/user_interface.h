#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>
#include <iostream>

#include "calendar.h"

class UserInterface {
    public:
        virtual ~UserInterface();
        virtual void print() = 0;
        
        // Static methods
        static void set_ui(UserInterface &);
        static void call_print();
        
        template<typename T> static T read(std::string text) {
            std::cout << text << " > ";
            
            T input;
            std::cin >> input;
            
            read_newline();
            return input;
        }
        
        static void check_input(bool);

    private:
        static UserInterface *user_interface;
        
        static void read_newline();
};

#endif


