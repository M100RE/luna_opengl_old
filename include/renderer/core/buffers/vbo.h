#ifndef _VBO_H
#define _VBO_H

class VBO
{
private:
    unsigned int id;
public:
    VBO();
    ~VBO();
    void bind();
    void unbind();
    void data(const void* vertices, const int size, const int usage);
};

#endif
