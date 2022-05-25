#ifndef _SHAPE_H
#define _SHAPE_H

#include "buffers/vbo.h"
#include "buffers/vao.h"
#include "shader/shader.h"
#include "buffers/ebo.h"

class shape
{
private:
    VAO vao;
    VBO vbo;
    EBO ebo;
    shader_program program;
    bool elements;
    int size;

    void* current_vertices; 
    void* current_indices;
public:
    shape(const void* vertices, const int vertices_size, const void* indices, const int indices_size, const char* vertex_path, const char* fragment_path);
    shape();
    void draw();
    void change_vertices(const void* vertices, const int vertices_size);
    shader_program receive_shader();
};

#endif