#include "renderer/core/shape.h"

#include <glad/glad.h>

shape::shape(){}

shape::shape(const void* vertices, const int vertices_size, const void* indices, const int indices_size, const char* vertex_path, const char* fragment_path)
    : program(vertex_path, fragment_path)
{
    elements = indices != nullptr;
    size = elements ? indices_size : vertices_size;

    program.compile();
    program.link();

    vao.bind();
    vbo.bind();

    vbo.data(vertices, vertices_size, GL_STATIC_DRAW);
    vao.data(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    
    if(elements)
    {
        ebo.bind();
        ebo.data(indices, indices_size, GL_STATIC_DRAW);
        ebo.unbind();
    }

    vbo.unbind();
    vao.unbind();
}

void shape::change_vertices(const void* vertices, const int vertices_size)
{
    vao.bind();
    vbo.bind();
    vbo.data(vertices, vertices_size, GL_STATIC_DRAW);
    vbo.unbind();
    vao.unbind();
}

void shape::draw()
{
    program.use();
    vao.bind();
    ebo.bind();
    if(elements)
    {
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, size);
    }
    vao.unbind();
    ebo.unbind();
}

shader_program shape::receive_shader()
{
    program.use();
    return program;
}
