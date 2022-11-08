#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include "GL/glew.h"

#include "texture.hpp"
//#include "core.hpp"

class Sprite;
class SpriteSheet {
    int textureID;
    int textureWidth;
    int textureHeight;
    int spriteWidth;
    int spriteHeight;

public:
    SpriteSheet(const char* fname, IMGMODE imgType, int sWidth, int sHeight);

    void renderSprite(float x, float y, int idx) const;
    
    Sprite getSprite(int idx) const;
};

class Sprite {
    const SpriteSheet* sheet;
    int index;

public:
    Sprite(const SpriteSheet* sheet, int index) : sheet(sheet), index(index) {}

    void render(float x, float y) const {
        sheet->renderSprite(x, y, index);
    }

    int getIndex() const {
        return index;
    }
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

    void render(float x, float y) const {
        currentFrame.render(x, y);
    }

    void tick();

    void stopAnimation() const {
    }
};

SpriteAnimation::SpriteAnimation(SpriteSheet const* sheet, int frameCount, float frameDuration, Sprite startFrame)
: spriteSheet(sheet), frameCount(frameCount), frameDuration(frameDuration), currentFrame(startFrame), startFrame(startFrame) {
    nextFrame = std::make_unique<Sprite>(spriteSheet, (startFrame.getIndex() + 1) % frameCount);
}

void SpriteAnimation::tick() {
    if (nextFrame == nullptr) {
        currentFrame = startFrame;
    } else {
        currentFrame = *nextFrame;
    }
    nextFrame = std::make_unique<Sprite>(spriteSheet, (currentFrame.getIndex() + 1) % frameCount);
}

SpriteSheet::SpriteSheet(const char* fname, IMGMODE imgType, int sWidth, int sHeight)
: spriteWidth(sWidth), spriteHeight(sHeight) {  
        Texture img;
        switch (imgType) {
            case BMP:
                img = loadBMP(fname);
                break;
            case DDS:
                img = loadDDS(fname);
                break;
            case PNG:
                img = loadPNG(fname);
                break;
            default:
                printf("Unknown image type: %d", imgType);
                exit(-1);
        }
        textureID = img.textureID;
        textureWidth = img.width;
        textureHeight = img.height; 
}

void SpriteSheet::renderSprite(float x, float y, int idx) const {
    const auto vertexes = std::vector<float> {
        x, y,
        x + spriteWidth, y,
        x + spriteWidth, y + spriteHeight,
        x, y + spriteHeight
    };
    
    const float texWidth = float(spriteWidth) / textureWidth;
    const float texHeight = float(spriteHeight) / textureHeight;
    const int texPerRow = textureWidth / spriteWidth;
    const float texX = float(idx % texPerRow) * texWidth;
    const float texY = float(idx / texPerRow + 1) * texHeight;
    const auto texCoords = std::vector<float> {
        texX, texY,
        texX + texWidth, texY,
        texX + texWidth, texY + texHeight,
        texX, texY + texHeight
    };

    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertexes.data());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());
    glDrawArrays(GL_QUADS, 0, 4);
}

Sprite SpriteSheet::getSprite(int idx) const {
    return Sprite(this, idx);
}
