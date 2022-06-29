#ifndef _LUNA_TYPES_H
#define _LUNA_TYPES_H

namespace luna
{
    struct constraint
    {
        float absolute_value; //in px
        float relative_value; //in rel
        constraint(float absolute_value, float relative_value);
        constraint();
    };

    struct color
    {
        float r, g, b, a;
    };
}

#endif