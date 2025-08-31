#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

// TODO: move glfw, opengl and glad initialization to separate file/function
GLFWwindow* create_window(const std::string& title, int width, int height)
{
        if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return nullptr;
    }
    
    glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return nullptr;
    }

    return window;
}