#include <algorithm>
#include <stdio.h>

#include "GLFW/glfw3.h"
//extern GLFWwindow* window; // hack to get around circular dependency

#include "controls.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;


glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
    return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
}

// Initial position : on +Z
glm::vec3 position = glm::vec3(0, 0, 5); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
const float initialFoV = 50.0f;
float FoV = initialFoV;

const float speed = 3.0f; // 3 units / second
const float mouseSpeed = 0.005f;

float clamp(float num, float minNum, float maxNum) {
    return std::max(std::min(maxNum, num), minNum);
}

void computeMatricesFromInputs(GLFWwindow* window) {

    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    auto deltaTime = float(currentTime - lastTime);

    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    // Reset mouse position for next frame
    glfwSetCursorPos(window, width/2, height/2);

    // Compute new orientation
    horizontalAngle += mouseSpeed * float(width/2 - xpos);
    verticalAngle   += mouseSpeed * float(height/2 - ypos);
    verticalAngle = clamp(verticalAngle, -1.7f, 1.42f);
    printf("verticalAngle: %f", verticalAngle);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle), 
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );
    
    // Right vector
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f), 
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    // Worldspace up vector
    glm::vec3 worldUp = glm::vec3(0,1,0);
    
    // Up vector
    glm::vec3 up = glm::cross(right, direction);

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }
    // Move up relative to world space
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += worldUp * deltaTime * speed;
    }
    // Move down relative to world space
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position -= worldUp * deltaTime * speed;
    }

    // Projection matrix : 45?? Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    ViewMatrix = glm::lookAt(
                            position,           // Camera is here
                            position+direction, // and looks here : at the same position, plus "direction"
                            up                  // Head is up (set to 0,-1,0 to look upside-down)
                        );

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    FoV = float(initialFoV - 5 * yoffset);
}