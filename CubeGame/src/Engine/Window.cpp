#include "Window.h"

#include <iostream>

namespace Engine {

	Window::Window(int width, int height, const std::string& title)
	{
		if (!glfwInit())
		{
			std::cout << "[Error] GLFW is not initialized." << std::endl;
			return;
		}

		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window)
		{
			std::cout << "[Error] Window could not be created." << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "[Error] GLEW is not initialized." << std::endl;
			return;
		}

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::Render()
	{
		if (!window)
		{
			std::cout << "[Error] GLFW Window is null, could not be rendered." << std::endl;
			return;
		}

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}

}
