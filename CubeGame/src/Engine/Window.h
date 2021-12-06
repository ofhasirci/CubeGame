#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <functional>
#include <memory>

#include "Scene.h"

namespace Engine {

	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window();

		void Render();

	private:
		int m_Width;
		int m_Height;
		GLFWwindow* window = nullptr;
		std::unique_ptr<Game::Scene> m_Scene;

		float lastTime = 0.0f;
		float GetDeltaTime();

		static void cursor_position_callback(GLFWwindow* window, double x, double y);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	};

}