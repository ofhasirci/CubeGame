#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Engine {
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void Clear() const;
		void ClearColor(float r, float g, float b, float a) const;
		void EnableDepthTest();
	};
}