#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <iostream>

#include "action.h"
#include "user_interface.h"

class Menu : public Action {
    public:
        Menu(std::string n) : Action(n), items() {}
        virtual ~Menu() {}

        void add(Action & action) {
            items.push_back(&action);
        }

        virtual void run() {
            while (true) {
                print();
                std::cout << "\nDitt val: ";

                unsigned int input;
                std::cin >> input;
                UserInterface::read_newline();

                if (input > 0 && input <= items.size()) {
                    items[input-1]->run();
                } else if (input == 0) {
                    break;
                }
            }
        }

    private:
        std::vector<Action*> items;

        void print() const {
            UserInterface::call_print();
            
            std::cout << get_name() << std::endl;
            std::cout << std::string(get_name().size(), '=') << std::endl;
            for (unsigned int i = 0; i < items.size(); ++i) {
                std::cout << (i+1) << ". " << items[i]->get_name() << std::endl;
            }
            std::cout << "0. Tillbaka/Avsluta" << std::endl;
        }
};

#endif
