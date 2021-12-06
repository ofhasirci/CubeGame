#pragma once

#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

	/*class Controls
	{
	public:
		Controls();
		~Controls();

		void ComputeMatricesFromInputs(GLFWwindow* window, float deltaTime);
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

		void StartPosition(float x, float y);

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		float m_InitialFOV = 45.0f;
		glm::vec3 m_Eye = glm::vec3(0, 5, 10);

		glm::vec3 startPos = glm::vec3(0, 0, 1);
		glm::vec3 currentPos = glm::vec3(0, 0, 1);

		double m_startPosX, m_startPosY;

		float m_Radius = 0;

		glm::vec3 CalculateSphereCoords(float x, float y);
	};*/

	// extern void ComputeMatricesFromInputs(GLFWwindow* window, float deltaTime);
	extern void RotateView();
	extern glm::mat4 GetProjectionMatrix();
	extern glm::mat4 GetViewMatrix();

	extern void StartPosition(float x, float y);
	extern void MovePosition(float x, float y);
	extern glm::vec3 CalculateSphereCoords(float x, float y);

	static bool IsMouseButtonPressed = false;

}