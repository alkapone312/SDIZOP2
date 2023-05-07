#include "utils/RandomNumberGenerator.h"

using namespace SDIZO;

RandomNumberGenerator::RandomNumberGenerator(int min, int max) {
    std::random_device randomizer;
    std::mt19937 generator(randomizer());
    this->generator = generator;
    this->dist = new std::uniform_int_distribution<>(min, max);
}

RandomNumberGenerator::~RandomNumberGenerator() {}

int RandomNumberGenerator::nextInt() {
    return this->dist->operator()(this->generator);
}