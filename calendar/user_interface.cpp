#include "user_interface.h"

// current user interface object
UserInterface *UserInterface::user_interface;

UserInterface::~UserInterface() {
}

void UserInterface::set_ui(UserInterface & ui) {
    user_interface = &ui;
}

void UserInterface::call_print() {
    user_interface->print();
}

void UserInterface::check_input(bool ok) {
    if (!ok) {
        std::string s;
        std::cout << "FEL! Ogiltigt val!" << std::endl;
        std::getline(std::cin, s); // wait for another newline
    }
}

void UserInterface::read_newline() {
    std::string s;
    std::getline(std::cin, s); // read newline from input (>> does not read it)
}


