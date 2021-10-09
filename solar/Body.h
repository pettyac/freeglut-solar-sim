#ifndef BODY_H
#define BODY_H

#include <iostream>
#include "vec4f.h"

class Body
{
public:

    double mass;
    vec4f p;    //position
    vec4f v;    //velocity
    float radius;
};

#endif
