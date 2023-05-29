#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include "ui/UserInterface.h"
#include "utils/Timer.h"

namespace SDIZO {
    class AlghorithmResult {
    private:
        std::vector<std::string> result = {};
        Timer* t = new Timer();
        UserInterface* ui = UserInterface::getInstance();
        int mstSum = 0;
        bool negativeCycle = false;
    public:
        AlghorithmResult();
        void addToResult(std::string);
        void sortStrings(bool (*compare)(std::string, std::string));
        void printResult();
        void printTime();
        void startTime();
        void stopTime();
        int getMSTSum();
        void addToMSTSum(int value);
        void markNegativeCycle();
        int getTime();
    };
};