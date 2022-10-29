//
// Created by Taylor Sanders on 4/9/22.
//

#ifndef PROJECT_3_RANDOM_H
#define PROJECT_3_RANDOM_H
#include <random>

class Random {
    static std::mt19937 random;

public:
    static int Int(int min, int max);
    static float Float(float min, float max);
};

#endif //PROJECT_3_RANDOM_H
