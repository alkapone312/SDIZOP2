#pragma once
#include <iostream>

namespace SDIZO {
    class UserInterface {
    private:
        static UserInterface* instance;
    protected:
        UserInterface();
    public:
        ~UserInterface();
        static UserInterface* getInstance();
        static void setInstance(UserInterface* instance);
        virtual int getNumber() = 0;
        virtual std::string getString() = 0;
        virtual void menu(std::string* options) = 0;
        virtual void info(std::string messsage) = 0;
        virtual void error(std::string errorMessage) = 0;
        virtual void message(std::string errorMessage) = 0;
        virtual void wait() = 0;
    };
}