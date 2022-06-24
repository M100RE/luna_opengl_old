#ifndef _MSTL_RENDERER_CONSTRAINTS_H
#define _MSTL_RENDERER_CONSTRAINTS_H

#include <string>
#include <vector>

class constraints
{
    enum CONSTRAINTS_ENUM
    {
//------static definitions
        PX,
        PER,   
        REL,   
//------relative definitions
        RPX,
        RPER,   
        RREL,   
//------string parsing definitions
        DIRECT, 
        EXTERNAL,
//------positioning definitions
        RIGHT,
        LEFT,
        UP,
        DOWN
    };

private:
    int initial_width;
    int initial_height;

    int window_width;
    int window_height;

    std::vector<float> x, y, width, height;
    std::vector<CONSTRAINTS_ENUM> type_x, type_y, type_width, type_height;
    CONSTRAINTS_ENUM xdef, ydef;

    int x1, y1, x2, y2; 

    /*temp*/std::string print_enum(CONSTRAINTS_ENUM num);
    
    void calculate_positions();
    std::string& remove_spaces(std::string& str);
    int locate_minus_plus(std::string argument, int start);
    std::string parse_external_request(std::string definition);
public:
    constraints(std::string definition);
    constraints();
    void parse_constraints(std::string definition, CONSTRAINTS_ENUM request_type = EXTERNAL);
    void update(int window_width, int window_height);
};

#endif