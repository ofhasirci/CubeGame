#include "VertexArray.h"
#include "GLBullet.h"

namespace Engine {
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_BufferID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_BufferID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_BufferID);
	}
	void VertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb)
	{
		Bind();
		vb.Bind();
		auto attribs = vb.GetAttributes();
		unsigned int offset = 0;
		for (size_t i = 0; i < attribs.size(); i++)
		{
			const auto& attrib = attribs[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized, vb.GetStride(), (const void*)offset);
			offset += attrib.count * VertexBufferAttribute::GetSizeOfType(attrib.type);
		}
	}
}