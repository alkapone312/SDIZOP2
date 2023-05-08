#include "app/alghorithms/AlghorithmResult.h"

using namespace SDIZO;

AlghorithmResult::AlghorithmResult(UserInterface* ui) {
    this->ui = ui;
}

void AlghorithmResult::addToResult(std::string s) {
    this->result->pushBack(s);
}

void AlghorithmResult::printResult() {
    for(result->first(); result->isItem(); result->next()) {
        ui->info(result->getActual()->value);
    }
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