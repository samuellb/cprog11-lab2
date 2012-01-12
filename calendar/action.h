#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
    public:
        Action(std::string n) : name(n) {}
        virtual ~Action() {}

        inline virtual std::string get_name() const { return name; }
        virtual void run() {}

    protected:
        const std::string name;
};

#endif
