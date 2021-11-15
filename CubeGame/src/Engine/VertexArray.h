#pragma once
#include "BaseBuffer.h"
#include "VertexBuffer.h"

namespace Engine {
	class VertexArray : public BaseBuffer
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const override;
		void UnBind() const override;

		void AddBuffer(const VertexBuffer& vb);

	private:

	};
}