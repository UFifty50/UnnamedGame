#ifndef TIME_HPP
#define TIME_HPP

#include <vector>
#include <any>

#include "sprite.hpp"
#include "registers.hpp"

double m_time();

class Time {
    double last;
public:
    Time() = default;

    void tick(std::vector<std::any> &registers);

    double elapsed() const;

    void reset();

    double deltaTime();
};

#endif