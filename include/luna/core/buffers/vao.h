#ifndef _VAO_H
#define _VAO_H

class VAO
{
private:
    unsigned int id;
public:
    VAO();
    ~VAO();
    void bind();
    void unbind();
    void data(const int index, const int components_per_vertex, const int datatype, const int normalized, const int stride, const void* offset);
    unsigned int receive_id();
};

#endif
