#include "Scene.h"

#include "GLBullet.h"

#include "imgui/imgui.h"

#include <iostream>

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

		view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -15.0f));
		view = glm::rotate(view, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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
		glm::mat4 m_view = glm::rotate(view, glm::radians(viewAngles[viewRotationIndex]), viewAxis);

		for (size_t i = 0; i < 8; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(modelAngles[modelRotationIndex]), modelAxis);
			glm::mat4 mvp = proj * m_view * model;

			m_Shader->Bind();
			m_Shader->SetUniformMatrix4f("u_MVP", mvp);

			renderer.Draw(*m_VA, *m_IndexBuffer, *m_Shader);
		}
	}

	void Scene::OnImGuiRender()
	{
		ImGui::Begin("Cube Control");

		ImGui::Text("Cube Rotation");
		if (ImGui::DragFloat("Model X", &modelAngles[0], 0.1f, -180.0f, 180.f))
		{
			modelRotationIndex = 0;
			modelAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		}

		if (ImGui::DragFloat("Model Y", &modelAngles[1], 0.1f, -180.0f, 180.f))
		{
			modelRotationIndex = 1;
			modelAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		}

		if (ImGui::DragFloat("Model Z", &modelAngles[2], 0.1f, -180.0f, 180.f))
		{
			modelRotationIndex = 2;
			modelAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		}

		ImGui::Spacing();

		ImGui::Text("View Rotation");
		if (ImGui::DragFloat("View X", &viewAngles[0], 0.1f, -180.0f, 180.f))
		{
			viewRotationIndex = 0;
			viewAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		}

		if (ImGui::DragFloat("View Y", &viewAngles[1], 0.1f, -180.0f, 180.f))
		{
			viewRotationIndex = 1;
			viewAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		}

		if (ImGui::DragFloat("View Z", &viewAngles[2], 0.1f, -180.0f, 180.f))
		{
			viewRotationIndex = 2;
			viewAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		}

		ImGui::End();
	}
}

