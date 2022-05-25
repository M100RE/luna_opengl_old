#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer/core/shape.h"
#include "renderer/ui/rectangle.h"
#include <iostream>

int window_width = 400;
int window_height = 400;

float vertices[]
{
0.979079, -1.96117, 
1.95816, -1.96117, 
1.95816, -0.980583, 
0.979079, -0.980583
};

float vertices2[]
{
    -0.1f, -0.1f,
    0.1f, -0.1f,
    0.1f, 0.1f,
    -0.1f, 0.1f
};

unsigned int indices[]
{
    0, 1, 2,
    0, 3, 2
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
    std::cout << window_width << "\n";
}

int main()
{
    glfwInit();    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "title", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    gladLoadGL();
    glViewport(0, 0, 500, 500);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    rectangle features(rect_pos(0, 0, 50, 100, PX, PX, PX, PER), color(1, 1, 1, 1), pos_def(false, false), window_width, window_height);
    rectangle files(rect_pos(53, 0, 170, 100, PX, PX, PX, PER), color(1, 1, 1, 1), pos_def(false, false), window_width, window_height);
    rectangle menu(rect_pos(0, 0, 15, 70, PX, PX, PER, PER), color(1, 1, 1, 1), pos_def(false, true), window_width, window_height);
    rectangle button(rect_pos(48, 48, 53, 53, PER, PER, PER, PER), color(1, 1, 1, 1), pos_def(false, false), window_width, window_height);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        features.update(window_width, window_height);
        files.update(window_width, window_height);
        menu.update(window_width, window_height);
        button.update(window_width, window_height);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}