#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

namespace Utils{
    float getRandomFloat(float min, float max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(gen);
    }
}

#endif // RANDOM_HPP