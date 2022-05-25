#include "renderer/core/shader/shader_parser.h"

#include <fstream>
#include <string>
#include <sstream>

const char* parse_shader(const char* shader_path)
{
    std::ifstream shader_file(shader_path);

    std::stringstream shader_text;

    while(shader_file)
    {
        std::string current_line;
        std::getline(shader_file, current_line);

        shader_text << current_line << "\n";
    }

    int string_length = shader_text.str().length() + 1; 
    char* return_shader_text = new char[shader_text.str().length() + 1];

    for(int i = 0; i < string_length - 1; i++)
    {
        return_shader_text[i] = shader_text.str()[i];
    }
    return_shader_text[string_length - 1] = '\0';

    return return_shader_text;
}