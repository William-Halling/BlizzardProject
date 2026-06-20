#include "RenderSystem.h"
#include <iostream>

namespace Engine::Graphics
{
	void RenderSystem::Render(std::span<const Engine::ECS::TransformComponent> transforms, std::span<const RenderComponent> renderables) noexcept
	{
		for (size_t i = 0; i < renderables.size(); ++i)
		{
			const auto& renderable = renderables[i];

			if (renderable.owner == Engine::ECS::INVALID_ENTITY || !renderable.isVisible)
			{
				continue;
			}

			const auto& matchingTransform = transforms[renderable.owner];
			std::cout << "Rendering Entity " << renderable.owner << " at X: " << matchingTransform.position[0] << "\n";
		}
	}
}
