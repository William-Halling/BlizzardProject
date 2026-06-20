#include "AsyncAssetManager.h"
#include <thread>
#include <future>


namespace Engine::Assets
{
	uint64_t AsyncAssetManager::RequestAssetTexture(const std::string& path)
	{
		uint64_t hash = std::hash<std::string>{}(path);

		{
			std::lock_guard<std::mutex> lock(m_RegistryMutex);
	
			if (m_Registry.find(hash) != m_Registry.end())
			{
				return hash;
			}
			
			m_Registry[hash] = TextureResource{ 0, 0, 0, false };
		}

			// Clean out old completed tasks before spinning up new ones
		UpdatePendingTasks();

			// Moving the future into our manager vector keeps it alive asynchronously
		auto workerTask = std::async(std::launch::async, [this, path, hash]() {
			TextureResource resource = LoadTextureFromDisk(path);

		
			std::lock_guard<std::mutex> lock(m_RegistryMutex);
			m_Registry[hash] = resource;
		});

		m_ActiveTasks.push_back(std::move(workerTask));

		return hash;
	}


	TextureResource AsyncAssetManager::LoadTextureFromDisk(const std::string& path)
	{
			// Simulate structural file system I/O latency
		std::this_thread::sleep_for(std::chrono::milliseconds(60));

			// Return generated mock graphics payload values
		return TextureResource{ 4294967295, 1024, 1024, true };
	}


	bool AsyncAssetManager::IsTextureReady(uint64_t hash) noexcept
	{
		std::lock_guard<std::mutex> lock(m_RegistryMutex);
		auto it = m_Registry.find(hash);

		return (it != m_Registry.end() && it->second.isLoaded);
	}


	TextureResource AsyncAssetManager::GetTexture(uint64_t hash) noexcept
	{
		std::lock_guard<std::mutex> lock(m_RegistryMutex);
		auto it = m_Registry.find(hash);

		if (it != m_Registry.end())
		{
			return it->second;
		}

		return TextureResource{};
	}

	
	void AsyncAssetManager::UpdatePendingTasks() noexcept
	{
		for (auto it = m_ActiveTasks.begin(); it != m_ActiveTasks.end();)
		{
			if (it->wait_for(std::chrono::seconds(0)) == std::future_status::ready)
			{
				it = m_ActiveTasks.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}