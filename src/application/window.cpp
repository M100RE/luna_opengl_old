#include "luna/application/window.h"

window::window(int width, int height, const char* title)
    : _width(width), _height(height),
    _window(glfwCreateWindow(width, height, title, nullptr, nullptr))
{ 
    glfwMakeContextCurrent(_window);
}

const GLFWwindow* window::window_ptr() const
{
    return _window;
}

GLFWwindow* window::window_ptr()
{
    return _window;
}

bool window::window_should_close() const
{
    return glfwWindowShouldClose(_window);
}

int window::width() const
{
    return _width;
}

int window::height() const
{
    return _height;
}

void window::set_framebuffer_size_callback(void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height))
{
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

void window::swap_buffers()
{
    glfwSwapBuffers(_window);
}