#include "renderer/core/buffers/vao.h"
#include <glad/glad.h>

VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &id);
}

void VAO::bind()
{
    glBindVertexArray(id);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::data(const int index, const int components_per_vertex, const int datatype, const int normalized, const int stride, const void* offset)
{
    glVertexAttribPointer(index, components_per_vertex, datatype, normalized, stride, offset);
    glEnableVertexAttribArray(index);
}

unsigned int VAO::receive_id()
{
    return id;
}
