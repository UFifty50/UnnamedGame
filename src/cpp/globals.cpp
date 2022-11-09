#include <vector>

#include "registers.hpp"
#include "sprite.hpp"
#include "time.hpp"

Time gameTime = Time();
Register<std::any*> animationRegister = Register<std::any*>();
std::vector<std::any> registers = std::vector<std::any>();
