#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <memory>

#include "core.hpp"

class Sprite;
class SpriteSheet {
    int textureID;
    int textureWidth;
    int textureHeight;
    int spriteWidth;
    int spriteHeight;

public:
    SpriteSheet(const char* fname, IMGMODE imgType, int sWidth, int sHeight);
  //  ~SpriteSheet();

    void renderSprite(float x, float y, int idx) const;
    Sprite getSprite(int idx) const;
};

class Sprite {
    const SpriteSheet* sheet;
    int index;

public:
    Sprite(const SpriteSheet* sheet, int index);

    void render(float x, float y) const;
    int getIndex() const;
};

class SpriteAnimation {
    const SpriteSheet* spriteSheet;
    int frameCount;
    float frameDuration;
    Sprite currentFrame;
    Sprite startFrame;
    std::unique_ptr<Sprite> nextFrame;

public:
    SpriteAnimation(SpriteSheet const* sheet, int frameCount, float frameDuration, Sprite startFrame);
    ~SpriteAnimation();

    void render(float x, float y) const;
    void tick();
    void stopAnimation() const;
};


#endif
