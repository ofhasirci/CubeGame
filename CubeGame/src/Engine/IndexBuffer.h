#pragma once

#include "BaseBuffer.h"

namespace Engine {
	class IndexBuffer : public BaseBuffer
	{
	private:
		unsigned int m_ElementCount;
	public:
		IndexBuffer(unsigned int count, const unsigned int* data, unsigned int usage);
		~IndexBuffer();

		void Bind() const override;
		void UnBind() const override;

		unsigned int GetElementCount() const;
		void SetElementCount(unsigned int count);

	};

}