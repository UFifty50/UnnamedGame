#ifndef TIME_HPP
#define TIME_HPP

#include <vector>
#include <any>


class Time {
private:
    double last;
    double time() const;

public:
    Time() = default;

    void tick(std::vector<std::any> &registers);
    double elapsed() const;
    void reset();
    double deltaTime();
};

#endif