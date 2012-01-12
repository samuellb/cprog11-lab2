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
                
        static void check_input(bool);

    private:
        static UserInterface *user_interface;
};

namespace UIRead { // can't use template specialization inside a class
    
    void read_newline();

    // inline is needed to prevent linkage errors (multiple definition)
    template<typename T> inline T read(std::string text) {
        std::cout << text << " > ";
        
        T input;
        std::cin >> input;
        
        read_newline();
        return input;
    }
    
    template<> inline std::string read<std::string>(std::string text) {
        std::cout << text << " > ";
        
        std::string input;
        std::getline(std::cin, input); // read one line (not just a single word)
        return input;
    }

}

#endif


