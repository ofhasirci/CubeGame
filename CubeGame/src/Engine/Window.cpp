#include "Window.h"

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "[Error] GLEW is not initialized." << std::endl;
			return;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		m_Scene = std::make_unique<Game::Scene>(title);

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	}

	Window::~Window()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			m_Scene->OnUpdate(0.0f);
			m_Scene->OnRender();
			m_Scene->OnImGuiRender();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}

}
