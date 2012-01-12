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
        template<typename T> static inline T read(std::string text);
        static void read_newline();

    private:
        static UserInterface *user_interface;
};

// can't use template specialization inside a class


// inline is needed to prevent linkage errors (multiple definition)
template<typename T> inline T UserInterface::read(std::string text) {
    std::cout << text << " > ";
    
    T input;
    std::cin >> input;
    
    read_newline();
    return input;
}

template<> inline std::string UserInterface::read<std::string>(std::string text) {
    std::cout << text << " > ";
    
    std::string input;
    std::getline(std::cin, input); // read one line (not just a single word)
    return input;
}


#endif


