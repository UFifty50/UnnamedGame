#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <array>
#include <utility>
#include <vector>

#include "GL/glew.h"

#include "core.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

constexpr unsigned int FOURCC_DXT1 = 0x31545844;
constexpr unsigned int FOURCC_DXT3 = 0x33545844;
constexpr unsigned int FOURCC_DXT5 = 0x35545844;

Texture loadPNG(const char* imagePath) {
    printf("Reading image %s", imagePath);

    int width;
    int height;
    int channels;
    unsigned char const* data = stbi_load(imagePath, &width, &height, &channels, 0);

    if (data == nullptr) {
        printf("Failed to load image %s", imagePath);
        exit(-1);
    }
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free((void*)data);

    printf("Loaded image %s", imagePath);

    return Texture {width, height, textureID};
}

Texture loadBMP(const char* imagePath) {
    printf("Reading image %s\n", imagePath);

    unsigned char header[54];
    unsigned int dataPos;
    int imageSize;
    int width;
    int height;
    unsigned char* data;

    FILE* file = fopen(imagePath, "rb");
    if (!file) {
        printf("%s could not be opened.\nPress any key to continue...", imagePath);
        getchar();
        exit(-1);
    }

    if (fread(header, 1, 54, file) != 54) {
        printf("%s is not a correct BMP file.\n", imagePath);
        fclose(file);
        exit(-1);
    }

    if (header[0] != 'B' || header[1] != 'M') {
        printf("%s is not a correct BMP file.\n", imagePath);
        fclose(file);
        exit(-1);
    }

    //TODO: check bppp

    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    if (imageSize == 0) imageSize = width*height*3;
    if (dataPos == 0) dataPos = 54;

    data = new unsigned char[imageSize];
    fread(data, 1, imageSize, file);
    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    delete[] data;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    return Texture {width, height, textureID};
}

Texture loadDDS(const char* imagePath) {

    unsigned char header[124];

    FILE *fp; 


    fp = fopen(imagePath, "rb"); 
    if (fp == nullptr){
        printf("%s could not be opened.\nPress any key to continue...", imagePath);
        getchar(); 
        return Texture::empty();
    }

    char filecode[4];
    fread(filecode, 1, 4, fp); 
    if (strncmp(filecode, "DDS ", 4) != 0) { 
        fclose(fp);
        return Texture::empty();
    }

    fread(&header, 124, 1, fp); 

    int height = *(int*)&(header[8]);
    int width = *(int*)&(header[12]);
    int linearSize = *(int*)&(header[16]);
    int mipMapCount = *(int*)&(header[24]);
    int fourCC = *(int*)&(header[80]);

 
    unsigned char* buffer;
    unsigned int bufsize;

    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
    fread(buffer, 1, bufsize, fp); 

    fclose(fp);

    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4; 
    unsigned int format;
    switch (fourCC) { 
        case FOURCC_DXT1: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
            break; 
        case FOURCC_DXT3: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
            break; 
        case FOURCC_DXT5: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
            break; 
        default: 
            free(buffer); 
            return Texture::empty(); 
    }

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);    
    
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
    unsigned int offset = 0;

    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
    { 
        unsigned int size = ((width+3) / 4) * ((height+3) / 4) * blockSize; 
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
            0, size, buffer + offset); 
     
        offset += size; 
        width /= 2; 
        height /= 2; 

        if(width < 1) width = 1;
        if(height < 1) height = 1;

    } 

    free(buffer); 

    return Texture {width, height, textureID};
}
