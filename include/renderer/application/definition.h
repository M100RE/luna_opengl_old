#ifndef _MSTL_RENDERER_input_H
#define _MSTL_RENDERER_input_H

#include <string>
#include <vector>
#include "renderer/shared/renderer_enum.h"

struct constraint
{
    float value;
    RENDERER_ENUM type;
    constraint(float value, RENDERER_ENUM type);
    float receive_rel_value(int calculating_width, int relative_calculating_width);
};

class definition
{
private:
    int window_width, window_height;
    int relative_window_width, relative_window_height;
    float x_start, y_start;

    std::vector<constraint> x, y, width, height;
    RENDERER_ENUM xdef, ydef;
    float r, g, b, a;

    float _x1, _y1, _x2, _y2; 

//--string editing
    std::string& remove_spaces(std::string& str);
    int locate_operators(std::string argument, int start);
    void extract_value(std::string value, float& number, RENDERER_ENUM& type);
    void extract_definition(std::string& input, RENDERER_ENUM request_type);
    std::string get_argument(std::string input, std::string argument, int& argument_start, int& argument_end);
    std::string parse_external_request(std::string input);
    void parse_constraints(std::string definition);
    void parse_alignment(std::string definition);
    void parse_color(std::string definition);
//--end

    int rel_to_px(float value, int calculating_width);
    void calculate_positions();
public:
    definition(std::string input, RENDERER_ENUM request_type = EXTERNAL);
    void parse_definition(std::string definition, RENDERER_ENUM request_type = EXTERNAL);
    void update(int x_start, int y_start, int window_width, int window_height);
    void update(const definition& parent);
    float x1() const;
    float y1() const;
    float x2() const;
    float y2() const;

    std::vector<float> receive_vertices() const;
};

#endif
