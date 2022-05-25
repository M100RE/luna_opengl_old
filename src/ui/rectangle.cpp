#include "renderer/ui/rectangle.h"
#include <iostream>

unsigned int inds[] = 
{
    0, 1, 2,
    0, 3, 2
};

rectangle::rectangle(rect_pos position, color col, pos_def bounds, int window_width, int window_height)
    : window_width(window_width), window_height(window_height),
    definite_position(position), definite_bounds(bounds), definite_color(col),
    body(calculate_position(position), 8 * sizeof(float), inds, 6 * sizeof(unsigned int), "../basic.vert", "../basic.frag")
{
}

float rectangle::calculate_single_position(float pos, NUM_TYPE type, bool x_y)
{
    switch(type)
    {
        case REL: return pos;
        case PX: return pos / ((x_y) ? window_height : window_width) * 2 - 1;
        case PER: return pos / 50 - 1;
        default: return -10000;
    }
}

float* rectangle::calculate_position(rect_pos position)
{
    float raw_vertices[4];

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            int current_index = i * 2 + j;
            raw_vertices[current_index] = calculate_single_position(position.positions[current_index], position.types[current_index], j);
        }
    }

    for(int i = 2; i < 4; i++)
    {
        //raw_vertices[i] = raw_vertices[i] + raw_vertices[i-2];
    }

    if(!definite_bounds.up_bound)
    {
        raw_vertices[1] *= -1;
        raw_vertices[3] *= -1;
    }
    if(definite_bounds.right_bound)
    {
        raw_vertices[0] *= -1;
        raw_vertices[2] *= -1;
    }

    float* vertices = new float[]
    {
        raw_vertices[0], raw_vertices[3],
        raw_vertices[2], raw_vertices[3],
        raw_vertices[2], raw_vertices[1],
        raw_vertices[0], raw_vertices[1]
    };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            std::cout << vertices[i*2+j] << ", ";
        }
        std::cout << "\n";
    }
    float* result = new float[8]
    {
        -0.1, -0.1,
        0.1, -0.1,
        0.1, 0.1,
        -0.1, 0.1
    };

    return vertices;
}

void rectangle::resize(rect_pos position)
{
    float* vertices = calculate_position(position);
    body.change_vertices(vertices, 8 * sizeof(float));
}

void rectangle::update(int window_width, int window_height)
{
    if(this->window_width != window_width || this->window_height != window_height)
    {
        this->window_width = window_width;
        this->window_height = window_height;
        resize(definite_position);
    }

    body.draw();
}