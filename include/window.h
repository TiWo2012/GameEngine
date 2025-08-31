#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
#include <iostream>

// TODO: move glfw, opengl and glad initialization to separate file/function
GLFWwindow* create_window(const std::string& title, int width, int height);