#include <string>
#include <vector>
#include <any>

#include "glfw/glfw3.h"
#include "sprite.hpp"
#include "registers.hpp"
#include "time.hpp"


double Time::time() const {
    return glfwGetTime();
}

void Time::tick(std::vector<std::any> &registers) {
    last = time();
    for (auto const &register_ : registers) {
        for (auto item : std::any_cast<Register<std::any>>(register_)) {
            if (item.type() == typeid(SpriteAnimation)) {
                std::any_cast<SpriteAnimation>(item).tick();
            }
        }
    }
}

double Time::elapsed() const {
    return time() - last;
}

void Time::reset() {
    last = time();
}

double Time::deltaTime() {
    double currentTime = time();
    double deltaTime = currentTime - last;
    last = currentTime;
    return deltaTime;
}
