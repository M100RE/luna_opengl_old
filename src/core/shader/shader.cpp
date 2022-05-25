#include "renderer/core/shader/shader.h"
#include "renderer/core/shader/shader_parser.h"

#include <glad/glad.h>
#include <iostream>

shader_program::shader_program(){}

shader_program::shader_program(const char* vertex_path, const char* fragment_path)
{
    id = glCreateProgram();

    vertex_id = glCreateShader(GL_VERTEX_SHADER);
    fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

    vertex_source = parse_shader(vertex_path);
    fragment_source = parse_shader(fragment_path);

    glShaderSource(vertex_id, 1, &vertex_source, NULL);
    glShaderSource(fragment_id, 1, &fragment_source, NULL);
}

void shader_program::compile()
{
    glCompileShader(vertex_id);
    int success;
    char info_log[512];
    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_id, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    glCompileShader(fragment_id);
    
    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_id, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    }
}

void shader_program::link()
{
    glAttachShader(id, vertex_id);
    glAttachShader(id, fragment_id);
    glLinkProgram(id);

    int success;
    char info_log[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
}

void shader_program::use()
{
    glUseProgram(id);
}

void shader_program::uniform1i(const char* name, const int value)
{
    glUniform1i(glGetUniformLocation(id, name), value);
}

void shader_program::uniform2i(const char* name, const int value0, const int value1)
{
    glUniform2i(glGetUniformLocation(id, name), value0, value1);
}

void shader_program::uniform3i(const char* name, const int value0, const int value1, const int value2)
{
    glUniform3i(glGetUniformLocation(id, name), value0, value1, value2);
}

void shader_program::uniform4i(const char* name, const int value0, const int value1, const int value2, const int value3)
{
    glUniform4i(glGetUniformLocation(id, name), value0, value1, value2, value3);
}

void shader_program::uniform1f(const char* name, const float value)
{
    glUniform1f(glGetUniformLocation(id, name), value);
}

void shader_program::uniform2f(const char* name, const float value0, const float value1)
{
    glUniform2f(glGetUniformLocation(id, name), value0, value1);
}

void shader_program::uniform3f(const char* name, const float value0, const float value1, const float value2)
{
    glUniform3f(glGetUniformLocation(id, name), value0, value1, value2);
}

void shader_program::uniform4f(const char* name, const float value0, const float value1, const float value2, const float value3)
{
    glUniform4f(glGetUniformLocation(id, name), value0, value1, value2, value3);
}
