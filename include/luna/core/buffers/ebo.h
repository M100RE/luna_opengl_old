#ifndef _EBO_H
#define _EBO_H

class EBO
{
private:
    unsigned int id;
public:
    EBO();
    void bind();
    void unbind();
    void data(const void* indices, const int size, const int usage);
};

#endif
