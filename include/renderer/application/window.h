#ifndef _MSTL_RENDERER_WINDOW_H
#define _MSTL_RENDERER_WINDOW_H

#include <GLFW/glfw3.h>

class window
{
private:
    GLFWwindow* _window;
    int _width;
    int _height;
public:
    window(int width, int height, const char* title);

    const GLFWwindow* window_ptr() const;
    bool window_should_close() const;   
    int width() const;
    int height() const;

    void set_framebuffer_size_callback(void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height));

    void swap_buffers();
};

#endif