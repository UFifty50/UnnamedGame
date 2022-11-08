#ifndef CORE_HPP
#define CORE_HPP

enum IMGMODE {
	DDS,
	BMP,
	TGA,
	PNG,
};

struct Texture {
    int width, height;
    unsigned int textureID;

    static Texture empty() {
        return Texture {0, 0, 0};
    }
};

struct Object {
    unsigned int x, y;
    Texture texture;

    static Object empty() {
        return Object {0, 0, Texture::empty()};
    }

    static Object init(unsigned int x, unsigned int y, Texture texture) {
        return Object {x, y, texture};
    }
};

#endif
