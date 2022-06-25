#ifndef _MSTL_RENDERER_UI_panel_H
#define _MSTL_RENDERER_UI_panel_H

#include "renderer/core/shape.h"
#include "renderer/application/definition.h"

class panel : private shape
{
private:
    definition def;
float place_holder[8] = 
{
    0, 0,
    0, 0,
    0, 0,
    0, 0
};

unsigned int indices[8]
{
    0, 1, 2,
    0, 3, 1
};
public:
    panel(const char* definition, RENDERER_ENUM type = EXTERNAL);
    void update(int window_width, int window_height);
};

#endif