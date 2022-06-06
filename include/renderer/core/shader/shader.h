#ifndef _SHADER_H
#define _SHADER_H

class shader_program
{
private:
    unsigned int id;
    unsigned int vertex_id;
    unsigned int fragment_id;
    const char* vertex_source;
    const char* fragment_source;
public:
    shader_program(const char* vertex_path, const char* fragment_path);
    void compile();
    void link();
    void use();
    void uniform1i(const char* name, const int value);
    void uniform2i(const char* name, const int value0, const int value1);
    void uniform3i(const char* name, const int value0, const int value1, const int value2);
    void uniform4i(const char* name, const int value0, const int value1, const int value2, const int value3);
    void uniform1f(const char* name, const float value);
    void uniform2f(const char* name, const float value0, const float value1);
    void uniform3f(const char* name, const float value0, const float value1, const float value2);
    void uniform4f(const char* name, const float value0, const float value1, const float value2, const float value3);
};

#endif
