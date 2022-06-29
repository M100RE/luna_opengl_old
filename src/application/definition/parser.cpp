//#include "renderer/application/parser.h"
#include "luna/application/definition/parser.h"
#include "luna/shared/file_parser.h"

#include <algorithm>
#include <type_traits>
#include <vector>
#include <iostream>

std::string& luna::parser::remove_spaces(std::string& str)
{
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

std::string luna::parser::parse_external_request(std::string definition)
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

int luna::parser::locate_operators(std::string argument, int start)
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

void luna::parser::extract_value(std::string value, float& number, LUNA_ENUM& type)
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
    LUNA_ENUM mapped_types[] = {PX, PER, PER, REL}; 
    
    for(int j = 0; j < sizeof(valid_types) / sizeof(std::string); j++)
    {
        if(string_type == valid_types[j])
        {
            type = mapped_types[j];
        }
    }
}


void luna::parser::extract_definition(std::string& definition, LUNA_ENUM request_type)
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

std::string luna::parser::get_argument(std::string definition, std::string argument)
{ 
    int argument_index = definition.find(argument);
    if(argument_index == std::string::npos)
    {
        return "--argument_not_found--";
    }
    int argument_start = definition.find(':', argument_index) + 1;
    int argument_end = definition.find(';', argument_index);
    return definition.substr(argument_start, argument_end - argument_start);
}

luna::constraint luna::parser::convert_constraint(std::string argument)
{
    float absolute_sum = 0;
    float relative_sum = -1;

    int value_start = 0;
    int value_end = argument.length();

    bool still_values = true;

    while(still_values)
    {
        value_end = locate_operators(argument, value_start + 1);
        if(value_end < 1)
        {
            still_values = false;
            value_end = argument.length();
        }
        std::string value = argument.substr(value_start, value_end - value_start);

        float number;
        LUNA_ENUM type;
        extract_value(value, number, type);

        switch(type)
        {
            case PX: absolute_sum += number; break;
            case PER: relative_sum += number / 50; break;
            case REL: relative_sum += number; break;
        }

        value_start = value_end;
    }
    return constraint(absolute_sum, relative_sum);
}

LUNA_ENUM luna::parser::convert_posdef(std::string argument)
{
    std::string arguments[] = {"left", "right", "up", "down"};     
    LUNA_ENUM mapped_values[] = {LEFT, RIGHT, UP, DOWN};

    for(int i = 0; i < sizeof(arguments) / sizeof(arguments[0]); i++)
    {
        if(arguments[i] == argument)
        {
            return mapped_values[i];
        }
    }
    return ERROR;
}