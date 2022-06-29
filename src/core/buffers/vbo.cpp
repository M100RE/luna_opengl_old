#include "luna/core/buffers/vbo.h"
#include <glad/glad.h>
#include <iostream>

VBO::VBO()       
{
    glGenBuffers(1, &id);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &id);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::data(const void* vertices, const int size, const int usage = GL_STATIC_DRAW)
{
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
}
