#include "app/alghorithms/AlghorithmResult.h"

using namespace SDIZO;
using std::to_string;

AlghorithmResult::AlghorithmResult() {}

void AlghorithmResult::addToResult(std::string s) {
    result.push_back(s);
}

void AlghorithmResult::sortStrings(bool (*compare)(std::string, std::string)) {
    std::sort(result.begin(), result.end(), compare);
}

void AlghorithmResult::printResult() {
    for(std::string s : result) {
        ui->info(s);
    }

    if(mstSum != 0) {
        ui->info("MST = " + to_string(mstSum));
    }
}

void AlghorithmResult::printTime() {
    ui->info("Elapsed time: " + std::to_string(getTime()));
}

void AlghorithmResult::startTime() {
    t->start();
}

void AlghorithmResult::stopTime() {
    t->stop();
}

int AlghorithmResult::getTime() {
    return t->getResult();
}


int AlghorithmResult::getMSTSum() {
    return this->mstSum;    
}

void AlghorithmResult::addToMSTSum(int value) {
    this->mstSum += value;
}
