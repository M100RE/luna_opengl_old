#ifndef _MSTL_RENDERER_UI_panel_H
#define _MSTL_RENDERER_UI_panel_H

#include "luna/core/shape.h"
#include "luna/application/definition/definition.h"

namespace luna
{
    class panel : private shape
    {
    private:
        definition def;
    public:
        panel(const char* definition, LUNA_ENUM type = EXTERNAL);
        void update(int window_width, int window_height);
        void update(const panel& parent);
    };
}

#endif