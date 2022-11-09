#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "registers.hpp"
#include "sprite.hpp"
#include "time.hpp"

extern Time gameTime;
extern std::vector<std::any> registers;
extern Register<std::any*> animationRegister;

#endif
