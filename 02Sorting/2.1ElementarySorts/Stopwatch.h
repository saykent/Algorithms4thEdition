#ifndef ALGORITHMS4THEDITION_STOPWATCH_H
#define ALGORITHMS4THEDITION_STOPWATCH_H

#include <chrono>

class Stopwatch
{
public:
    Stopwatch(): start_{std::chrono::high_resolution_clock::now()} {}

    double elapsedTime()
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - start_;

        return elapsed.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

#endif //ALGORITHMS4THEDITION_STOPWATCH_H
