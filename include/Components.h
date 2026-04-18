#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <string>

struct Health
{
    float current;
    float max;
};


float ScriptComponent
{
    std::string updateFunc;
}

#endif