#include "PersistentVertexBuffer.h"
#include <cstring>


namespace Engine::Graphics
{
	PersistentVertexBuffer::PersistentVertexBuffer(size_t sizeInBytes)
		: m_BufferSize(sizeInBytes)
	{
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		/// Imutable storage creation flags 
		GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
		glBufferStorage(GL_ARRAY_BUFFER, m_BufferSize, nullptr, flags);


		/// Map the device pointer permanently into the CPU application address space
		m_MappedDevicePointer = glMapBufferRange(GL_ARRAY_BUFFER, 0, m_BufferSize, flags);
	}


	PersistentVertexBuffer::~PersistentVertexBuffer() noexcept
	{
		if (m_MappedDevicePointer)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		if (m_VBO)
		{
			glDeleteBuffers(1, &m_VBO);
		}
	}


	PersistentVertexBuffer::~PersistentVertexBuffer() noexcept
	{
		if (m_MappedDevicePointer)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		if (m_VBO)
		{
			glDeleteBuffers(1, &m_VBO);
		}
	}


	void PersistentVertexBuffer::WriteData(const void* data, size_t size, size_t offset) noexcept
	{
			/// Critical boundary check preventing GPU memory corruption out-of-bounds
		if (offset + size <= m_BufferSize && m_MappedDevicePointer)
		{
			std::memcpy(static_cast<char*>(m_MappedDevicePointer) + offset, data, size);
		}
	}
}