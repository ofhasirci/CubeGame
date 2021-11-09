#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Engine {

	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window();

		void Render();

	private:
		GLFWwindow* window = nullptr;
	};

}