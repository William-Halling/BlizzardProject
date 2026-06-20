#pragma once

#include <span>
#include "RenderComponent.h"
#include "TransformComponent.h"


namespace Engine::Graphics
{
	class RenderSystem
	{
		public:
			static void Render(std::span<const Engine::ECS::TransformComponent> transforms, std::span<const RenderComponent> renderables) noexcept;
	};
}


