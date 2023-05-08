#pragma once
#include <string>
#include "ui/UserInterface.h"
#include "structures/DoubleSidedList.h"
#include "utils/Timer.h"

namespace SDIZO {
    class AlghorithmResult {
    private:
        DoubleSidedList<std::string>* result = new DoubleSidedList<std::string>();
        Timer* t = new Timer();
        UserInterface* ui;
    public:
        AlghorithmResult(UserInterface* ui);
        void addToResult(std::string);
        void printResult();
        void startTime();
        void stopTime();
        int getTime();
    };
};