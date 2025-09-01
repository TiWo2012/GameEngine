#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Window.h"
#include "VbaVbo.h"

// TODO: add a abstraction layer for the window.
// TODO: add a example on how to use the Engine.
int main() 
{
    GLFWwindow* window = create_window("GameEngine Window Example", 800, 600);
    if (window == nullptr) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }


    float vertices[] = {
        // positions        // colors
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    auto [VAO, VBO] = createVBAVBO(vertices, sizeof(vertices));

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
