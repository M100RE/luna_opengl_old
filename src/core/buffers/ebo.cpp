#include "luna/core/buffers/ebo.h"

#include <glad/glad.h>

EBO::EBO()
{
    glGenBuffers(1, &id);
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::data(const void* indices, const int size, const int usage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
}
