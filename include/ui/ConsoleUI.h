#pragma once
#include "ui/UserInterface.h"

namespace SDIZO {
    class ConsoleUI : public SDIZO::UserInterface {
        private:
            std::string* options;
        public:
            ConsoleUI();
            ~ConsoleUI();
            int getNumber();
            std::string getString();
            void menu(std::string* options);
            void info(std::string messsage);
            void error(std::string errorMessage);
            void message(std::string message);
            void wait();

        private:
            int stringToNumber(std::string value);
    };
}