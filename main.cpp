#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer/ui/panel.h"
#include "renderer/application/window.h"
#include <iostream>
#include <string>
#include "renderer/application/constraints.h"

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

    main_frame.set_framebuffer_size_callback(framebuffer_size_callback);

    panel content(rect_pos(0, 0, 100, 100, PX, PX, PER, PER), color(32, 34, 34, 1), pos_def(false, false), window_width, window_height);
    panel button(rect_pos(48, 48, 50, 50, PER, PER, PX, PX), color(0, 122, 204, 0.5), pos_def(false, false), window_width, window_height);
    panel features(rect_pos(0, 0, 50, 100, PX, PX, PX, PER), color(62, 62, 66, 1), pos_def(true, false), window_width, window_height);
    panel files(rect_pos(50, 0, 170, 100, PX, PX, PX, PER), color(45, 45, 48, 1), pos_def(false, false), window_width, window_height);
    panel menu(rect_pos(0, 0, 150, 700, PX, PX, PX, PX), color(37, 37, 38, 1), pos_def(true, true), window_width, window_height);

    //panel example(rect_pos(100, 100, 50, 50, PX, PX, PX, PX), color(255, 255, 255, 1), pos_def(false, true), window_width, window_height);

    constraints example;
    example.parse_constraints("main_panel; ../panels.def");
    
    while(!main_frame.window_should_close())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        content.update(window_width, window_height);
        button.update(window_width, window_height);
        menu.update(window_width, window_height);
        features.update(window_width, window_height);
        files.update(window_width, window_height);

        main_frame.swap_buffers();
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
