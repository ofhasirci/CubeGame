#include "Scene.h"

#include "GLBullet.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

namespace Game {
	Scene::Scene(const std::string& sceneName)
		: m_SceneName(sceneName)
	{
		float vertices[] =
		{	// X, Y, Z           R, G, B, A
			// Back
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,

			// Front
			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			
			// Left
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,

			// Right
			 0.5f, -0.5f, -0.5f, 1.0f, 0.2f, 0.15f, 1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 0.2f, 0.15f, 1.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 0.2f, 0.15f, 1.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.2f, 0.15f, 1.0f,

			 // Bottom
			-0.5f, -0.5f, -0.5f, 0.45f, 0.25f, 0.15f, 1.0f,
			 0.5f, -0.5f, -0.5f, 0.45f, 0.25f, 0.15f, 1.0f,
			 0.5f, -0.5f,  0.5f, 0.45f, 0.25f, 0.15f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.45f, 0.25f, 0.15f, 1.0f,

			// Top
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		unsigned int indices[] =
		{
			// Back
			0, 1, 2,
			2, 3, 0,

			// Front
			4, 5, 6,
			6, 7, 4,

			// Left
			8, 9, 10,
			10, 11, 8,

			// Right
			12, 13, 14,
			14, 15, 12,

			// Bottom
			16, 17, 18,
			18, 19, 16,

			// Top
			20, 21, 22,
			22, 23, 20
		};

		m_VA = std::make_unique<Engine::VertexArray>();

		m_VertexBuffer = std::make_unique<Engine::VertexBuffer>(4 * 6 * 7 * sizeof(float), vertices, GL_STATIC_DRAW);
		m_VertexBuffer->Push<float>(3);
		m_VertexBuffer->Push<float>(4);

		m_VA->AddBuffer(*m_VertexBuffer);

		m_IndexBuffer = std::make_unique<Engine::IndexBuffer>(6 * 6, indices, GL_STATIC_DRAW);

		m_Shader = std::make_unique<Engine::Shader>("res/shaders/ShaderVertex.glsl", "res/shaders/ShaderFragment.glsl");
	}

	Scene::~Scene()
	{
	}

	void Scene::OnUpdate(float deltaTime)
	{
	}

	void Scene::OnRender()
	{
		renderer.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		renderer.EnableDepthTest();

		// 960, 540
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -5.0f));
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3((float)axis[0], (float)axis[1], (float)axis[2]));
		glm::mat4 mvp = proj * view * model;

		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("u_MVP", mvp);
		
		renderer.Draw(*m_VA, *m_IndexBuffer, *m_Shader);
	}

	void Scene::OnImGuiRender()
	{
		ImGui::Begin("Cube Control");
		ImGui::Checkbox("X", &axis[0]); ImGui::SameLine();
		ImGui::Checkbox("Y", &axis[1]); ImGui::SameLine();
		ImGui::Checkbox("Z", &axis[2]); ImGui::SameLine();
		ImGui::SliderAngle("Rotate", &angle);
		ImGui::End();
	}
}

