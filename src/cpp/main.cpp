#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "globals.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "sprite.hpp"
#include "time.hpp"
#include "registers.hpp"
#include "core.hpp"

using namespace glm;


void updateObject(Object &object, int x, int y) {
    object.x = x;
    object.y = y;
}

int main() {
    GLFWwindow* win = window(1024, 768, "Tutorial 05 - Texturing", nullptr, nullptr);
    
    if (win == nullptr) {
        return -1;
    }

    glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  //  glfwSetScrollCallback(win, (GLFWscrollfun)scrollCallback);
    glfwPollEvents();
    glfwSetCursorPos(win, 1024/2, 768/2);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);

    glm::mat4 projection = glm::ortho(0, 1024, 768, 0);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = loadShaders("shaders/Vshader1.vert", "shaders/Fshader1.frag");
    GLuint textureID = glGetUniformLocation(programID, "textureSampler");
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    
  //  bool res = loadOBJ("obj/suzanne.obj", vertices, uvs, DDS);
    SpriteSheet spriteSheet("textures/sprite1.png", PNG, 8, 10);
    Sprite sprite1 = spriteSheet.getSprite(2);
    SpriteAnimation animation1(&spriteSheet, 5, 10, sprite1);
    animationRegister.registerItem(animation1);
    //Object sprite = loadSprite("textures/uvmap.DDS", vertices, uvs, IMGMODE::DDS);
  
  /*  GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    glUseProgram(programID);
*/
    registers.push_back(&animationRegister);
    gameTime.reset();
    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);

        gameTime.tick(registers);

        glUniform1i(textureID, 0); /*

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer); */
        glVertexAttribPointer(
            1,                  // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
/*
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1); */
        
        glfwSwapBuffers(win);
        glfwPollEvents();

    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(win) == 0); /*

    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer); */
    glDeleteProgram(programID);
  //  glDeleteTextures(1, &spriteSheet.textureID);
    glDeleteVertexArrays(1, &VertexArrayID);
    glfwTerminate();

    return 0;
}
