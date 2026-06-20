#pragma once
#include "TransformComponent.h"

#include <cstdint>


namespace Engine::Graphics
{
    struct RenderComponent
    {
        Engine::ECS::EntityID owner{ Engine::ECS::INVALID_ENTITY };
        uint64_t textureHandle{ 0 };
        uint32_t vertexOffset{ 0 };
        uint32_t vertexCount{ 0 };
        bool isVisible{ true };
    };
}
