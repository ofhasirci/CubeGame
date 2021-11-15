#include "Renderer.h"
 
#include "GLBullet.h"

namespace Engine {

	Renderer::Renderer()
	{
	}
	Renderer::~Renderer()
	{
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();
		glDrawElements(GL_TRIANGLES, ib.GetElementCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::ClearColor(float r, float g, float b, float a) const
	{
		glClearColor(r, b, g, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void Renderer::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}