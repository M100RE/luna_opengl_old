#ifndef _SHAPE_H
#define _SHAPE_H

#include "buffers/vbo.h"
#include "buffers/vao.h"
#include "shader.h"
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

    float* current_vertices; 
    unsigned int* current_indices;
public:
    shape(const float* vertices, const int vertices_size, const unsigned int* indices, const int indices_size, const char* vertex_path, const char* fragment_path);
    void draw();
    void change_vertices(const void* vertices, const int vertices_size);
    shader_program receive_shader();

    ~shape();
};

#endif