#ifndef _MSTL_RENDERER_UI_panel_H
#define _MSTL_RENDERER_UI_panel_H

#include "renderer/core/shape.h"
#include "renderer/application/definition.h"

struct color
{
    float r, g, b, a;

    color(float r, float g, float b, float a)
        : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a)
    {}
};

class panel : private shape
{
private:
    definition def;
    color definite_color;
public:
    panel(const char* definition, DEFINITION_ENUM type = EXTERNAL);
};

#endif