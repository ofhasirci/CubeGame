#include "IndexBuffer.h"

#include "GLBullet.h"

namespace Engine {
	IndexBuffer::IndexBuffer(unsigned int count, const unsigned int* data, unsigned int usage)
		: m_ElementCount(count)
	{
		ASSERT(sizeof(unsigned int) == sizeof(GLuint));

		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void IndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int IndexBuffer::GetElementCount() const
	{
		return m_ElementCount;
	}

	void IndexBuffer::SetElementCount(unsigned int count)
	{
		m_ElementCount = count;
	}
}