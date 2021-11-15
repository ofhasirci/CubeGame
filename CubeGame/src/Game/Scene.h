#pragma once

#include <string>
#include <memory>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"


namespace Game {
	class Scene
	{
	private:
		std::string m_SceneName;
		std::unique_ptr<Engine::VertexArray> m_VA;
		std::unique_ptr<Engine::VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Engine::IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Engine::Shader> m_Shader;

		Engine::Renderer renderer;
		float angle = 0.0f;
		bool axis[3] = { true, false, false };
	public:
		Scene() {}
		Scene(const std::string& sceneName);
		~Scene();

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();
		virtual void OnImGuiRender();

		std::string GetSceneName() const { return m_SceneName; }

	};
}