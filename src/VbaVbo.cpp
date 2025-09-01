#include <glad/glad.h>
#include <utility>
#include "VbaVbo.h"

std::pair<uint32_t, uint32_t> createVBAVBO(float* vertices, uint32_t size)
{
    std::pair<uint32_t, uint32_t> VaoVbo = std::make_pair(0, 0);
    
    glGenVertexArrays(1, &VaoVbo.first);
    glGenBuffers(1, &VaoVbo.second);

    glBindVertexArray(VaoVbo.first);

    glBindBuffer(GL_ARRAY_BUFFER, VaoVbo.second);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VaoVbo;
}