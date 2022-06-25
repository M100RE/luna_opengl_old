#include "renderer/ui/panel.h"
#include <iostream>


panel::panel(const char* definition, RENDERER_ENUM type)
    : shape(place_holder, sizeof(place_holder), indices, sizeof(indices), "../src/ui/panel/panel.vert", "../src/ui/panel/panel.frag")
{

}

void panel::update(int window_width, int window_height)
{
    /*
    def.update(window_width, window_height);
    float vertices[] = 
    {
        def.x1(), def.y1(),
        def.x2(), def.y1(),
        def.x2(), def.y2(),
        def.x1(), def.y2()
    };
    change_vertices(vertices, sizeof(vertices));
    */
}