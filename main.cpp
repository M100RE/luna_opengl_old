#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer/ui/panel.h"
#include "renderer/application/window.h"
#include <iostream>
#include <string>

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
    
    panel parent = "parent, ../panels.luna";
    panel child = "child, ../panels.luna";
    
    while(!main_frame.window_should_close())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.6f);
        glClear(GL_COLOR_BUFFER_BIT);

        parent.update(window_width, window_height);
        child.update(parent);

        main_frame.swap_buffers();
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
