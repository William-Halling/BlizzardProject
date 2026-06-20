#include "MovementSystem.h"

namespace Engine::ECS
{
	void MovementSystem::Update(std::span<TransformComponent> transforms, float deltaTime) noexcept
	{
		for (auto& transform : transforms)
		{
			if (transform.owner == INVALID_ENTITY)
			{
				continue;
			}

			transform.position[0] += 0.5f * deltaTime;
		}
	}
}
