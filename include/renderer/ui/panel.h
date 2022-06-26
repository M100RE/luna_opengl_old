#ifndef _MSTL_RENDERER_UI_panel_H
#define _MSTL_RENDERER_UI_panel_H

#include "renderer/core/shape.h"
#include "renderer/application/definition.h"

class panel : private shape
{
private:
    definition def;
public:
    panel(const char* definition, RENDERER_ENUM type = EXTERNAL);
    void update(int window_width, int window_height);
};

#endif