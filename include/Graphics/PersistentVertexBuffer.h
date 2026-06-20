#pragma once
#include <glad/glad.h>
#include <cstddef>



namespace Engine::Graphics
{
	class PersistentVertexBuffer
	{
		private:
			GLuint m_VBO{ 0 };
			void* m_MappedDevicePointer{ nullptr };
			size_t m_BufferSize{ 0 };


		public:
			explicit PersistentVertexBuffer(size_t sizeInBytes);
			~PersistentVertexBuffer() noexcept;

				/// enforced on first declaration: Hard delete copy operations to protect GPU boundaries
			PersistentVertexBuffer(const PersistentVertexBuffer&) = delete;
			
			PersistentVertexBuffer& operator=(const PersistentVertexBuffer&) = delete;


			void WriteData(const void* data, size_t size, size_t offset) noexcept;
	};
}