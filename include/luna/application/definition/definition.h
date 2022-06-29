#ifndef _MSTL_RENDERER_input_H
#define _MSTL_RENDERER_input_H

#include <string>
#include <vector>
#include "luna/shared/luna_enum.h"
#include "luna/application/definition/parser.h"
#include "luna/application/definition/types.h"

namespace luna
{
    class definition
    {
        friend class parser;
    private:
        int window_width, window_height;
        int relative_window_width, relative_window_height;
        float x_start, y_start, x_end, y_end;

        constraint x, y, width, height;
        LUNA_ENUM xdef, ydef;
        color col;

        float x1, y1, x2, y2; 

        int rel_to_px(float value, int calculating_width);
        void calculate_positions();
        float calculate_single_position(constraint value, LUNA_ENUM axis);

    public:
        definition(std::string definiiton, LUNA_ENUM request_type = EXTERNAL);
        void update(int window_width, int window_height);
        void update(const definition& parent);

        std::vector<float> receive_vertices() const;
    };
}


#endif
