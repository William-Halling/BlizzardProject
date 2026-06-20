#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include <mutex>
#include <cstdint>
#include <future>


namespace Engine::Assets
{
	struct TextureResource
	{
		uint64_t runtimeHandle{ 0 };
		int width{ 0 };
		int height{ 0 };
		bool isLoaded{ false };
	};


	class AsyncAssetManager
	{
		private:

			std::vector<std::future<void>> m_ActiveTasks;
			std::unordered_map<uint64_t, TextureResource> m_Registry;
			std::mutex m_RegistryMutex;


			TextureResource LoadTextureFromDisk(const std::string& path);

		public:
				/*****************
			 	 * 
				 * 
				 *****************/
			AsyncAssetManager() = default;


				/*****************
				 *
				 *
				 *****************/
			~AsyncAssetManager() = default;


				/*****************
				 * Triggers asset loading on a worker thread and immediately hands back an asset hash
				 *
				 *****************/
			uint64_t RequestAssetTexture(const std::string & path);


				/*****************
				 * 
				 *****************/
			bool IsTextureReady(uint64_t hash) noexcept;


				/*****************
				 *
				 *****************/
			TextureResource GetTexture(uint64_t hash) noexcept;


				/*****************
				 *
				 *****************/
			void UpdatePendingTasks() noexcept;
	};
}
