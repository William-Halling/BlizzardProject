#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include <sol/sol.hpp>
#include <entt/entt.hpp>
#include "Components.h"

class ScriptManager
{
    public:
    sol::state lua;

    void init(entt::registry& registry)
    {
            // Load standard Lua libraries (math, string, etc.)
        lua.open_libraries(sol::lib::base);


            // 🔗 Binding: Define the "Health" type for Lua
        lua.new_usertype<Health>("Health", "current", &Health::current, "max", &Health::max);


            // 🛠️ Utility: Create a function Lua can call to find an entity's health
        lua.set_function("get_health", [&](entt::entity e) -> Health&
        {
            return registry.get<Health>(e);
        }
        );
    }
};

#endif