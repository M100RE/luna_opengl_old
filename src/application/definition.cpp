#include "renderer/application/definition.h"
#include "renderer/shared/file_parser.h"
#include <iostream>
#include <algorithm>

definition::definition()
{

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

void definition::extract_value(std::string value, float& number, DEFINITION_ENUM& type)
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
    std::string valid_types[] = {"px", "per", "%", "rel", "rpx", "rper", "r%", "rrel"};
    DEFINITION_ENUM mapped_types[] = {PX, PER, PER, REL, RPX, RPER, RPER, RREL}; 
    
    for(int j = 0; j < sizeof(valid_types) / sizeof(std::string); j++)
    {
        if(string_type == valid_types[j])
        {
            type = mapped_types[j];
        }
    }
}
void definition::extract_definition(std::string& definition, DEFINITION_ENUM request_type)
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

void definition::parse_definition(std::string definition, DEFINITION_ENUM request_type)
{
    extract_definition(definition, request_type);

    std::string arguments[] = {"x", "y", "width", "height"};
    std::vector<float>* argument_attributes[] = {&x, &y, &width, &height};
    std::vector<DEFINITION_ENUM>* type_attributes[] = {&type_x, &type_y, &type_width, &type_height};
    
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
                DEFINITION_ENUM type;
                extract_value(value, number, type);

                argument_attributes[i]->push_back(number);
                type_attributes[i]->push_back(type);

                value_start = value_end;
            };
        }
    }
} 