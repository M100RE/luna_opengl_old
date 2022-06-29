#include "luna/application/definition/definition.h"
#include "luna/shared/file_parser.h"
#include <iostream>
#include <algorithm>

luna::definition::definition(std::string definition, LUNA_ENUM request_type)
{
    parser::extract_definition(definition, request_type);
    x = parser::get_argument_value(definition, "x", parser::convert_constraint);
    y = parser::get_argument_value(definition, "y", parser::convert_constraint);
    width = parser::get_argument_value(definition, "width", parser::convert_constraint);
    height = parser::get_argument_value(definition, "height", parser::convert_constraint);
    xdef = parser::get_argument_value(definition, "xdef", parser::convert_posdef);
    ydef = parser::get_argument_value(definition, "ydef", parser::convert_posdef);
}

void luna::definition::update(int window_width, int window_height)
{
    x_start = -1;
    y_start = -1;
    x_end = 1;
    y_end = 1;
    relative_window_width = this->window_width = window_width;
    relative_window_height = this->window_height = window_height;
    this->x_start = x_start;
    this->y_start = y_start; 

    calculate_positions();
} 

void luna::definition::update(const definition& parent)
{
    relative_window_width = (((1 + parent.x2) / 2) - ((1 + parent.x1) / 2)) * parent.window_width;
    relative_window_height = (((1 + parent.y2) / 2) - ((1 + parent.y1) / 2)) * parent.window_height;
    window_width = parent.window_width;
    window_height = parent.window_height;

    x_start = parent.x1;
    y_start = parent.y1;
    x_end = parent.x2;
    y_end = parent.y2;

    calculate_positions();
}

float luna::definition::calculate_single_position(constraint value, LUNA_ENUM axis)
{
    int relative_calculating_distance = (axis == WIDTH) ? relative_window_width : relative_window_height;
    int calculating_distance = (axis == WIDTH) ? window_width : window_height;

    float absolute_result = value.absolute_value / (calculating_distance >> 1);
    float relative_result = (value.relative_value + 1) * ((float)relative_calculating_distance / calculating_distance) - 1;

    return absolute_result + relative_result;
}

void luna::definition::calculate_positions()
{
    x1 = calculate_single_position(x, WIDTH); 
    x2 = calculate_single_position(width, WIDTH); 
    y1 = calculate_single_position(y, HEIGHT); 
    y2 = calculate_single_position(height, HEIGHT); 

    if(xdef == RIGHT)
    {
        x1 = -x1 - x2 + x_end - x_start - 3;
    }
    if(ydef == UP)
    {
        y1 = -y1 - y2 + y_end - y_start - 3;
    }
    x1 += 1 + x_start;
    y1 += 1 + y_start;

    y2 += 1 + y1;
    x2 += 1 + x1;

}

std::vector<float> luna::definition::receive_vertices() const
{
    return
    {
        x1, y1,
        x2, y1,
        x2, y2,
        x1, y2
    };
}

/*
float luna::constraint::receive_rel_value(int calculating_width, int relative_calculating_width)
{
    switch(type)
    {
        case REL: return value;
        case PX: return (value / (calculating_width >> 1)) - 1;
        case PER: 
        {
            return (value / 50) * ((float)relative_calculating_width / calculating_width) - 1;
        }
        default: return -1000;
    }
}
*/