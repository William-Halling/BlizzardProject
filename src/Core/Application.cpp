#include "Application.h"
#include "MovementSystem.h"
#include "RenderSystem.h"


namespace Engine::Core
{
	Application::Application()
		: m_Window({ 1920, 1080, "AAA Engine Base", 4, 4 })
		, m_TransformStorage(ECS::MAX_ENTITIES)
		, m_VBO(ECS::MAX_ENTITIES * sizeof(ECS::TransformComponent))
	{
		m_RenderStorage.reserve(ECS::MAX_ENTITIES);
		m_LastFrameTime = std::chrono::high_resolution_clock::now();

		InitializeScene();
	}


	void Application::InitializeScene()
	{
		
		ECS::EntityID entity0 = m_EntityManager.CreateEntity();

		if (entity0 != ECS::INVALID_ENTITY)
		{
			m_TransformStorage[entity0] = ECS::TransformComponent{ entity0, { 0.0f, 0.0f, 0.0f }, {}, { 1.0f, 1.0f, 1.0f } };
			m_RenderStorage.push_back(Graphics::RenderComponent{ entity0, 0, 0, 6, true });
		}

		ECS::EntityID entity1 = m_EntityManager.CreateEntity();

		if (entity1 != ECS::INVALID_ENTITY)
		{
			m_TransformStorage[entity1] = ECS::TransformComponent{ entity1, { 5.0f, 2.0f, 0.0f }, {}, { 1.0f, 1.0f, 1.0f } };
			m_RenderStorage.push_back(Graphics::RenderComponent{ entity1, 0, 0, 6, true });
		}

		
		m_FloorTextureHash = m_AssetManager.RequestAssetTexture("assets/textures/floor.png");
	}


	void Application::ProcessInput() noexcept
	{
		m_Window.PollEvents();
	}


	void Application::FixedUpdate(float deltaTime) noexcept
	{
		ECS::MovementSystem::Update(m_TransformStorage, deltaTime);
	}


	void Application::Render() noexcept
	{
		// Sync local simulation updates into mapped persistent GPU driver memory space
		m_VBO.WriteData(m_TransformStorage.data(), m_TransformStorage.size() * sizeof(ECS::TransformComponent), 0);

		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Graphics::RenderSystem::Render(m_TransformStorage, m_RenderStorage);

		m_Window.SwapBuffers();
	}


	void Application::Run()
	{
		while (!m_Window.ShouldClose())
		{
			auto currentFrameTime = std::chrono::high_resolution_clock::now();
			double frameTime = std::chrono::duration<double>(currentFrameTime - m_LastFrameTime).count();
			m_LastFrameTime = currentFrameTime;

			// Cap extreme frame spikes (e.g. during debugging breakpoints)
			if (frameTime > 0.1) frameTime = 0.1;
			m_AccumulatedTime += frameTime;

			ProcessInput();

			
			if (m_AssetManager.IsTextureReady(m_FloorTextureHash))
			{
				auto resolvedTexture = m_AssetManager.GetTexture(m_FloorTextureHash);
				if (!m_RenderStorage.empty())
				{
					m_RenderStorage[0].textureHandle = resolvedTexture.runtimeHandle;
				}
			}

				
			while (m_AccumulatedTime >= TARGET_TIME_STEP)
			{
				FixedUpdate(static_cast<float>(TARGET_TIME_STEP));
				m_AccumulatedTime -= TARGET_TIME_STEP;
			}

			Render();
		}
	}
}