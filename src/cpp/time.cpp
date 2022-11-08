#include <string>
#include <vector>
#include <any>

#include "glfw/glfw3.h"
#include "sprite.hpp"
#include "registers.hpp"

double m_time() {
    return glfwGetTime();
}


class Time {
    double last;
public:
    Time() = default;

    void tick(std::vector<std::any> &registers);

    double elapsed() const {
        return m_time() - last;
    }

    void reset();

    double deltaTime();
};

void Time::tick(std::vector<std::any> &registers) {
    last = m_time();
    for (auto const &register_ : registers) {
        for (auto item : std::any_cast<Register<std::any>>(register_)) {
            if (item.type() == typeid(SpriteAnimation)) {
                std::any_cast<SpriteAnimation>(item).tick();
            }
        }
    }
}

void Time::reset() {
    last = m_time();
}

double Time::deltaTime() {
    double currentTime = m_time();
    double deltaTime = currentTime - last;
    last = currentTime;
    return deltaTime;
}
