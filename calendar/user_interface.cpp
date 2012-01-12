#include <iostream>

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


