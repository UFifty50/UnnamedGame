#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "core.hpp"


Texture loadPNG(const char* imagePath);
Texture loadBMP(const char* imagePath);
Texture loadDDS(const char* imagePath);

#endif
