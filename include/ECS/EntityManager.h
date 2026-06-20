#pragma once

#include "TransformComponent.h"
#include <vector>

namespace Engine::ECS
{
	class EntityManager
	{
	private:
		std::vector<EntityID> m_FreeIndices;
		uint32_t m_NextIndex{ 0 };

	public:
		EntityManager();

		EntityID CreateEntity() noexcept;
		void DestroyEntity(EntityID id) noexcept;
	};
}