#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer/ui/panel.h"
#include "renderer/application/window.h"
#include <iostream>
#include <string>
#include "renderer/application/definition.h"

int window_width = 400;
int window_height = 400;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

int main()
{
    glfwInit();    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window main_frame(window_width, window_height, "title");
    
    gladLoadGL();
    glViewport(0, 0, window_width, window_height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    main_frame.set_framebuffer_size_callback(framebuffer_size_callback);

    //panel example(rect_pos(100, 100, 50, 50, PX, PX, PX, PX), color(255, 255, 255, 1), pos_def(false, true), window_width, window_height);

    definition example;
    
    while(!main_frame.window_should_close())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.6f);
        glClear(GL_COLOR_BUFFER_BIT);

        main_frame.swap_buffers();
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
