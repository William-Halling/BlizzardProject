#pragma once

#include "Window.h"
#include "TransformComponent.h"
#include "EntityManager.h"
#include "RenderComponent.h"
#include "PersistentVertexBuffer.h"
#include "AsyncAssetManager.h"
#include <vector>


namespace Engine::Core
{
	class Application
	{
		private:
			Window m_Window;
			ECS::EntityManager m_EntityManager;
			Graphics::PersistentVertexBuffer m_VBO;

			std::vector<ECS::TransformComponent> m_TransformStorage;
			std::vector<Graphics::RenderComponent> m_RenderStorage;

			double m_AccumulatedTime{ 0.0 };
			std::chrono::high_resolution_clock::time_point m_LastFrameTime;
			static constexpr double TARGET_TIME_STEP = 1.0 / 60.0;

			uint64_t m_FloorTextureHash{ 0 };

			void InitializeScene();
			void ProcessInput() noexcept;
			void FixedUpdate(float deltaTime) noexcept;
			void Render() noexcept;

		public:
			Application();
			~Application() = default;

			// Deleted copies to safeguard internal hardware VBO/Window handles
			Application(const Application&) = delete;
			Application& operator=(const Application&) = delete;

			void Run();
	};
}

