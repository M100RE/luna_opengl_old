#ifndef _LUNA_PARSER_H
#define _LUNA_PARSER_H

#include <string>
#include "luna/shared/luna_enum.h"
#include "luna/application/definition/definition.h"
#include "luna/application/definition/types.h"

namespace luna
{
    class parser
    {
        friend class definition;

    public:
        parser() = delete;

        static std::string& remove_spaces(std::string& str);
        static int locate_operators(std::string argument, int start);
        static void extract_value(std::string value, float& number, LUNA_ENUM& type);
        static void extract_definition(std::string& input, LUNA_ENUM request_type);
        static std::string get_argument(std::string input, std::string argument);
        static std::string parse_external_request(std::string input);
        template <typename T>
        static T get_argument_value(std::string definition, std::string argument_name, T(*conversion_function)(std::string))
        {
            return conversion_function(get_argument(definition, argument_name));
        }

        static constraint convert_constraint(std::string argument);
        static LUNA_ENUM convert_posdef(std::string argument);
        static color convert_color(std::string argument);
    };
}

#endif