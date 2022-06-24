#ifndef _MSTL_RENDERER_input_H
#define _MSTL_RENDERER_input_H

#include <string>
#include <vector>

enum DEFINITION_ENUM
{
//------static inputs
    PX,
    PER,   
    REL,   
//------relative inputs
    RPX,
    RPER,   
    RREL,   
//------string parsing inputs
    DIRECT, 
    EXTERNAL,
//------positioning inputs
    RIGHT,
    LEFT,
    UP,
    DOWN
};
class definition
{
private:
    int initial_width;
    int initial_height;

    int window_width;
    int window_height;

    std::vector<float> x, y, width, height;
    std::vector<DEFINITION_ENUM> type_x, type_y, type_width, type_height;
    DEFINITION_ENUM xdef, ydef;
    float r, g, b, a;

    int x1, y1, x2, y2; 

//--string editing
    std::string& remove_spaces(std::string& str);
    int locate_operators(std::string argument, int start);
    void extract_value(std::string value, float& number, DEFINITION_ENUM& type);
    void extract_definition(std::string& input, DEFINITION_ENUM request_type);
    std::string get_argument(std::string input, std::string argument, int& argument_start, int& argument_end);
    std::string parse_external_request(std::string input);
//--end

    void calculate_positions();
public:
    definition(std::string input);
    /*temp*/definition();
    void parse_definition(std::string definition, DEFINITION_ENUM request_type = EXTERNAL);
    void update(int window_width, int window_height);
};

#endif
