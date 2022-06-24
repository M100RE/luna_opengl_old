#include "renderer/application/constraints.h"
#include "renderer/shared/file_parser.h"
#include <iostream>
#include <algorithm>

constraints::constraints()
{

}

std::string constraints::print_enum(CONSTRAINTS_ENUM num)
{
    switch(num)
    {
        case PX: return "PX";
        case RPX: return "RPX";
        case PER: return "PER";
        case RPER: return "RPER";
        case REL: return "REL";
        case RREL: return "RREL";
    }
}

std::string& constraints::remove_spaces(std::string& str)
{
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

std::string constraints::parse_external_request(std::string definition)
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

int constraints::locate_minus_plus(std::string argument, int start)
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

void constraints::parse_constraints(std::string definition, CONSTRAINTS_ENUM request_type)
{
    if(request_type == EXTERNAL)
    {
        definition = parse_external_request(definition);
    }
    else
    {
        remove_spaces(definition);
    }
    std::cout << definition << "\n";

    std::string arguments[] = {"x", "y", "width", "height"};
    std::vector<float>* argument_attributes[] = {&x, &y, &width, &height};
    std::vector<CONSTRAINTS_ENUM>* type_attributes[] = {&type_x, &type_y, &type_width, &type_height};
    
    for(int i = 0; i < sizeof(arguments) / sizeof(std::string); i++)
    {
        int argument_index = definition.find(arguments[i]);
        int argument_start = definition.find(':', argument_index) + 1;
        int argument_end = definition.find(';', argument_index);
        std::string argument = definition.substr(argument_start, argument_end - argument_start);

        int value_start = 0;
        int value_end = argument_end - argument_start;

        bool still_values = true;
        int counter = 0;
        do
        {
            counter++;
            value_end = locate_minus_plus(argument, value_start + 1);
            if(value_end < 0)
            {
                still_values = false;
                value_end = argument_end - argument_start;
            }
            std::string value = argument.substr(value_start, value_end - value_start);
            
            int type_start;
            for(int j = 1; j < value.length(); j++)
            {
                if(!std::isdigit(value.at(j)) && value.at(j) != '.')
                {
                    type_start = j;
                    break;
                }
            }
            float number = std::stod(value.substr(0, type_start));
            argument_attributes[i]->push_back(number);

            std::string type = value.substr(type_start);
            std::string valid_types[] = {"px", "per", "%", "rel", "rpx", "rper", "r%", "rrel"};
            CONSTRAINTS_ENUM mapped_types[] = {PX, PER, PER, REL, RPX, RPER, RPER, RREL}; 
            
            for(int j = 0; j < sizeof(valid_types) / sizeof(std::string); j++)
            {
                if(type == valid_types[j])
                {
                    type_attributes[i]->push_back(mapped_types[j]);
                }
            }
            
            value_start = value_end;
        }while(still_values);
    }

    for(int i = 0; i < x.size(); i++)
    {
        std::cout << "x" << i << ": " << x[i] << print_enum(type_x[i]) << "\n";
    }
    for(int i = 0; i < y.size(); i++)
    {
        std::cout << "y" << i << ": " << y[i] << print_enum(type_y[i]) << "\n";
    }
    for(int i = 0; i < width.size(); i++)
    {
        std::cout << "width" << i << ": " << width[i] << print_enum(type_width[i]) << "\n";
    }
    for(int i = 0; i < height.size(); i++)
    {
        std::cout << "height" << i << ": " << height[i] << print_enum(type_height[i]) << "\n";
    }
} 