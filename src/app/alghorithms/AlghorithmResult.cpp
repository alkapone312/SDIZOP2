#include "app/alghorithms/AlghorithmResult.h"

using namespace SDIZO;

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