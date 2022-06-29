#include "luna/ui/panel.h"
#include <iostream>

float place_holder[] = 
{
    -0.1, -0.1,
    0.1, 0.1,
    -0.1, 0.1
};

unsigned int indices[]
{
    0, 1, 2,
    2, 0, 3
};

luna::panel::panel(const char* definition, LUNA_ENUM type)
    : shape(place_holder, 8 * sizeof(float), indices, 6 * sizeof(unsigned int), "../../src/ui/panel/panel.vert", "../../src/ui/panel/panel.frag"),
    def(definition, type)
{}

void luna::panel::update(int window_width, int window_height)
{
    def.update(window_width, window_height);
    std::vector<float> vertices = def.receive_vertices();
    change_vertices(vertices.data(), vertices.size() * sizeof(float));
    draw();
}

void luna::panel::update(const panel& parent)
{
    def.update(parent.def);
    std::vector<float> vertices = def.receive_vertices();
    change_vertices(vertices.data(), vertices.size() * sizeof(float));

    draw();
}
