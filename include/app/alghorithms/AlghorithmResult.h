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
    public:
        AlghorithmResult();
        void addToResult(std::string);
        void sortStrings(bool (*compare)(std::string, std::string));
        void printResult();
        void startTime();
        void stopTime();
        int getTime();
    };
};