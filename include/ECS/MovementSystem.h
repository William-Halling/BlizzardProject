#pragma once
#include <span>
#include "TransformComponent.h"


constexpr uint32_t MAX_ENTITIES = 10000;

namespace Engine::ECS
{
	class MovementSystem
	{
		public:
			static void Update(std::span<TransformComponent> transforms, float deltaTime) noexcept;
	};
}

