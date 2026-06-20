#pragma once
#include <cstdint>

namespace Engine::ECS 
{
	using EntityID = uint32_t;
	constexpr EntityID INVALID_ENTITY = 0xFFFFFFFF;


	struct TransformComponent
	{
		EntityID owner{ INVALID_ENTITY }; // Explicit tracking
		float position[3]{ 0.0f, 0.0f, 0.0f };
		float rotation[3]{ 0.0f, 0.0f, 0.0f };
		float scale[3]{ 1.0f, 1.0f, 1.0f };
	};
}