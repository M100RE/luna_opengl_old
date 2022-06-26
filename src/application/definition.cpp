#include "renderer/application/definition.h"
#include "renderer/shared/file_parser.h"
#include <iostream>
#include <algorithm>

constraint::constraint(float value, RENDERER_ENUM type)
    : value(value), type(type)
{}

definition::definition(std::string input, RENDERER_ENUM request_type)
{
    parse_definition(input, request_type);
}

float constraint::receive_rel_value(int calculating_width)
{
    switch(type)
    {
        case REL: return value; break;
        case PX: return (value / calculating_width) * 2 - 1; break;
        case PER: return (value / 100) * 2 - 1; break;
        default: return -1000;
    }
}

std::string& definition::remove_spaces(std::string& str)
{
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

std::string definition::parse_external_request(std::string definition)
{
    char allowed_splitters[] = {';', ','};
    int split;
    remove_spaces(definition);
    for(int i = 0; i < sizeof(allowed_splitters) / sizeof(char); i++)
    {
        int temp = definition.find(allowed_splitters[i]);
        if(temp != std::string::npos)
        {
            split = temp;
            break;
        }
    }
    std::string name = definition.substr(0, split);
    std::string file_name = definition.substr(split + 1);

    std::string file_content = parse_file(file_name.c_str());
    remove_spaces(file_content);

    int def_pos = file_content.find(name);
    int start = file_content.find('{', def_pos) + 1;
    int end = file_content.find('}', def_pos);

    std::string final_definition = file_content.substr(start, end - start);
    return final_definition;
}

int definition::locate_operators(std::string argument, int start)
{
    for(int i = start; i < argument.length(); i++)
    {
        if(argument.at(i) == '-' || argument.at(i) == '+')
        {
            return i;
        }
    }
    return -1;
}

void definition::extract_value(std::string value, float& number, RENDERER_ENUM& type)
{
    int type_start;
    for(int j = 1; j < value.length(); j++)
    {
        if(!std::isdigit(value.at(j)) && value.at(j) != '.')
        {
            type_start = j;
            break;
        }
    }
    number = std::stod(value.substr(0, type_start));

    std::string string_type = value.substr(type_start);
    std::string valid_types[] = {"px", "per", "%", "rel"};
    RENDERER_ENUM mapped_types[] = {PX, PER, PER, REL}; 
    
    for(int j = 0; j < sizeof(valid_types) / sizeof(std::string); j++)
    {
        if(string_type == valid_types[j])
        {
            type = mapped_types[j];
        }
    }
}
void definition::extract_definition(std::string& definition, RENDERER_ENUM request_type)
{
    if(request_type == EXTERNAL)
    {
        definition = parse_external_request(definition);
    }
    else
    {
        remove_spaces(definition);
    }
}

std::string definition::get_argument(std::string definition, std::string argument, int& argument_start, int& argument_end)
{ 
    int argument_index = definition.find(argument);
    if(argument_index == std::string::npos)
    {
        return "--argument_not_found--";
    }
    argument_start = definition.find(':', argument_index) + 1;
    argument_end = definition.find(';', argument_index);
    return definition.substr(argument_start, argument_end - argument_start);
}

void definition::parse_constraints(std::string definition)
{
    std::string arguments[] = {"x", "y", "width", "height"};
    std::vector<constraint>* argument_attributes[] = {&x, &y, &width, &height};
    
    for(int i = 0; i < sizeof(arguments) / sizeof(std::string); i++)
    {
        int argument_end, argument_start;
        std::string argument = get_argument(definition, arguments[i], argument_start, argument_end);
        if(argument != "--argument_not_found--")
        {
            int value_start = 0;
            int value_end = argument_end - argument_start;

            bool still_values = true;
            int counter = 0;
            while(still_values)
            {
                counter++;
                value_end = locate_operators(argument, value_start + 1);
                if(value_end < 0)
                {
                    still_values = false;
                    value_end = argument_end - argument_start;
                }
                std::string value = argument.substr(value_start, value_end - value_start);

                float number;
                RENDERER_ENUM type;
                extract_value(value, number, type);

                argument_attributes[i]->push_back(constraint(number, type));

                value_start = value_end;
            }; 
 
        }
    }
} 

void definition::parse_alignment(std::string definition)
{
    std::string arguments[] = {"xdef", "ydef"};
    RENDERER_ENUM* mapped_arguments[] = {&xdef, &ydef};
    
    std::string valid_types[] = {"down", "up", "right", "left"};
    RENDERER_ENUM mapped_types[] = {DOWN, UP, RIGHT, LEFT}; 

    for(int i = 0; i < sizeof(arguments) / sizeof(std::string); i++)
    {
        int argument_end, argument_start;
        std::string argument = get_argument(definition, arguments[i], argument_start, argument_end);
        if(argument != "--argument_not_found--")
        {
            for(int j = 0; j < sizeof(valid_types) / sizeof(std::string); j++)
            {
                if(argument == valid_types[j])
                {
                    *mapped_arguments[i] = mapped_types[j];
                }
            }
        }
    }
}

void definition::parse_color(std::string definition)
{
    std::string arguments[] = {"r", "g", "b", "a"};
    float* mapped_arguments[] ={&r, &g, &b, &a};

    for(int i = 0; i < sizeof(arguments) / sizeof(std::string); i++)
    {
        int argument_end, argument_start;
        std::string argument = get_argument(definition, arguments[i], argument_start, argument_end);
        if(argument != "--argument_not_found--")
        {

        }
    }
}

void definition::parse_definition(std::string definition, RENDERER_ENUM request_type)
{
    extract_definition(definition, request_type);
    parse_constraints(definition);
    parse_alignment(definition);

    for(int i = 0; i < x.size(); i++)
    {
        std::cout << x[i].value << " " << x[i].type << "\n";
    }
    for(int i = 0; i < y.size(); i++)
    {
        std::cout << y[i].value << " " << y[i].type << "\n";
    }
    for(int i = 0; i < width.size(); i++)
    {
        std::cout << width[i].value << " " << width[i].type << "\n";
    }
    for(int i = 0; i < height.size(); i++)
    {
        std::cout << height[i].value << " " << height[i].type << "\n";
    }
    std::cout << xdef << "\n";
    std::cout << ydef << "\n";
}

void definition::calculate_positions()
{
    std::vector<constraint>* arguments[] = {&x, &y, &width, &height};
    float* mapped_types[] = {&_x1, &_y1, &_x2, &_y2};
    
    for(int i = 0; i < 4; i++)
    {
        int calculating_width = (i % 2 == 0) ? window_width : window_height;
        float sum = (*arguments[i])[0].receive_rel_value(calculating_width);

        for(int j = 1; j < arguments[i]->size(); j++)
        {
            sum += 1 + (*arguments[i])[j].receive_rel_value(calculating_width);
        }
        *mapped_types[i] = sum;
    }
    _x1 += 1 + x_start;
    _y1 += 1 + y_start;
    _x2 += 1 + _x1;
    _y2 += 1 + _y1;

    if(ydef == UP)
    {
        _y1 *= -1;
        _y2 *= -1;    
    }
    if(xdef == RIGHT)
    {
        _x1 *= -1;
        _x2 *= -1;
    }
}

void definition::update(int x_start, int y_start, int window_width, int window_height)
{
    this->window_width = window_width;
    this->window_height = window_height;
    this->x_start = x_start;
    this->y_start = y_start;

    calculate_positions();
}

std::vector<float> definition::receive_vertices() const
{
    return 
    {
        _x1, _y1,
        _x2, _y1,
        _x2, _y2,
        _x1, _y2 
    };
}