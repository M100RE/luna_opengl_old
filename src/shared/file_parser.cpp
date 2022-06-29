#include "luna/shared/file_parser.h"

#include <fstream>
#include <string>
#include <sstream>

const char* parse_file(const char* shader_path)
{
    std::ifstream file(shader_path);

    std::stringstream file_text;

    while(file)
    {
        std::string current_line;
        std::getline(file, current_line);

        file_text << current_line << "\n";
    }

    int string_length = file_text.str().length() + 1; 
    char* return_shader_text = new char[file_text.str().length() + 1];

    for(int i = 0; i < string_length - 1; i++)
    {
        return_shader_text[i] = file_text.str()[i];
    }
    return_shader_text[string_length - 1] = '\0';

    return return_shader_text;
}