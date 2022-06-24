#ifndef _MSTL_RENDERER_UI_panel_H
#define _MSTL_RENDERER_UI_panel_H

#include "renderer/core/shape.h"

enum NUM_TYPE
{
    PX,
    PER,
    REL
};

struct rect_pos
{
    float positions[4];
    NUM_TYPE types[4];
    
    rect_pos(float x1, float y1, float x2, float y2, 
            NUM_TYPE type_x1, NUM_TYPE type_y1, NUM_TYPE type_x2, NUM_TYPE type_y2)
    {
        positions[0] = x1;
        positions[1] = y1;
        positions[2] = x2;
        positions[3] = y2;

        types[0] = type_x1;
        types[1] = type_y1;
        types[2] = type_x2;
        types[3] = type_y2;
    }
};

struct color
{
    float r, g, b, a;

    color(float r, float g, float b, float a)
        : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a)
    {}
};

struct pos_def
{
    bool up_bound, right_bound;

    pos_def(bool up_bound, bool right_bound)
    : up_bound(up_bound), right_bound(right_bound)
    {}
};

class panel : public shape
{
private:
    int window_width, window_height;
    rect_pos definite_position;
    pos_def definite_bounds;
    color definite_color;

    float calculate_single_position(float pos, NUM_TYPE type, bool x_y); 
    float* calculate_position(rect_pos position);
    void resize(rect_pos position);

public:
    panel(rect_pos position, color col, pos_def bounds, int window_width, int window_height);

    rect_pos get_pos();

    void update(int window_width, int window_height);
    void update(const panel& parent);
};

#endif