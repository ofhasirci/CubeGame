#pragma once

namespace Engine {

	class BaseBuffer
	{
	protected:
		unsigned int m_BufferID = -1;
	public:
		BaseBuffer() {};
		virtual ~BaseBuffer() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};
}