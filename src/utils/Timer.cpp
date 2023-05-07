#include "utils/Timer.h"

using namespace SDIZO;

Timer::Timer() {}

Timer::~Timer() {}

void Timer::start() {
    this->startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    this->stopTime = std::chrono::high_resolution_clock::now();
}

int Timer::getResult() {
    auto int_us = std::chrono::duration_cast<std::chrono::nanoseconds>(this->stopTime - this->startTime);
    return int_us.count();
}