#include "EntityManager.h"
#include "MovementSystem.h"


namespace Engine::ECS
{
	EntityManager::EntityManager()
	{
		m_FreeIndices.reserve(MAX_ENTITIES);
	}

	EntityID EntityManager::CreateEntity() noexcept
	{
		if (!m_FreeIndices.empty())
		{
			EntityID id = m_FreeIndices.back();
			m_FreeIndices.pop_back();

			return id;
		}

		if (m_NextIndex < MAX_ENTITIES)
		{
			return m_NextIndex++;
		}

		return INVALID_ENTITY;
	}


	void EntityManager::DestroyEntity(EntityID id) noexcept
	{
		if (id != INVALID_ENTITY && id < MAX_ENTITIES)
		{
			m_FreeIndices.push_back(id);
		}
	}
}