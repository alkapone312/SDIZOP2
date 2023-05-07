#pragma once
#include <random>

namespace SDIZO {
    class RandomNumberGenerator {
    private:
        std::mt19937 generator;
        std::uniform_int_distribution<>* dist;
    public:
        RandomNumberGenerator(int min = 0, int max = 2147483646);
        ~RandomNumberGenerator();
        int nextInt();
    };
}