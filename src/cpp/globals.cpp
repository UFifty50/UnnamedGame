#include <vector>

#include "registers.hpp"
#include "sprite.hpp"
#include "time.hpp"

Time gameTime = Time();
Register<SpriteAnimation> animationRegister = Register<SpriteAnimation>();
std::vector<std::any> registers = std::vector<std::any>();
