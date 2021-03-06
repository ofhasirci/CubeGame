#pragma once

#include <string>
#include <memory>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

		glm::mat4 view = glm::mat4(1.0f);
		int viewRotationIndex = 0;
		float viewAngles[3] = { 0.0f, 0.0f, 0.0f };
		glm::vec3 viewAxis = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::mat4 model = glm::mat4(1.0f);
		int modelRotationIndex = 0;
		float modelAngles[3] = { 0.0f, 0.0f, 0.0f };
		glm::vec3 modelAxis = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::vec3 cubePositions[8] = {
			glm::vec3(-0.7f, -0.5f, -0.2f),
			glm::vec3( 0.5f, -0.5f, -0.2f),
			glm::vec3( 0.5f,  0.7f, -0.2f),
			glm::vec3(-0.7f,  0.7f, -0.2f),

			glm::vec3(-0.7f, -0.5f, 1.0f),
			glm::vec3( 0.5f, -0.5f, 1.0f),
			glm::vec3( 0.5f,  0.7f, 1.0f),
			glm::vec3(-0.7f,  0.7f, 1.0f)
		};
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