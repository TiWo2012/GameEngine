#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // Link shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::use() const {
    glUseProgram(ID);
}

unsigned int Shader::getID() const {
    return ID;
}

std::string Shader::loadShaderSource(const std::string& filepath) {
    std::ifstream file(filepath);
    std::stringstream buffer;
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
    }
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    const char* src = source.c_str();
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    checkCompileErrors(shader, (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));
    return shader;
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Shader Compilation Error [" << type << "]:\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Program Linking Error:\n" << infoLog << std::endl;
        }
    }
}

// Uniforms
void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
