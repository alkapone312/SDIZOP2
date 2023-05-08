#pragma once
#include <string>
#include "ui/UserInterface.h"
#include "structures/DoubleSidedList.h"
#include "utils/Timer.h"

namespace SDIZO {
    class AlghorithmResult {
    private:
        DoubleSidedList<std::string>* result;
        Timer* t = new Timer();
        UserInterface* ui = UserInterface::getInstance();
    public:
        AlghorithmResult();
        void addToResult(std::string);
        void printResult();
        void startTime();
        void stopTime();
        int getTime();
    };
};