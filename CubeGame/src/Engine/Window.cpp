#include "Window.h"

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Common/Controls.h"

namespace Engine {

	Window::Window(int width, int height, const std::string& title)
		: m_Width(width), m_Height(height)
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

		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);

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

			float deltaTime = GetDeltaTime();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			m_Scene->OnUpdate(deltaTime);
			m_Scene->OnRender(GetProjectionMatrix(), GetViewMatrix());
			m_Scene->OnImGuiRender();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}

	float Window::GetDeltaTime()
	{
		double time = glfwGetTime();
		float deltaTime = float(time - lastTime);
		lastTime = time;
		return deltaTime;
	}

	void Window::cursor_position_callback(GLFWwindow* window, double x, double y)
	{
		if (!IsMouseButtonPressed)
		{
			return;
		}
		int invert_y = (540 - y) - 1;
		MovePosition(x, invert_y);
	}

	void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			int invert_y = (540 - y) - 1;
			StartPosition(x, invert_y);
			IsMouseButtonPressed = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
			IsMouseButtonPressed = false;
		}
	}

}
