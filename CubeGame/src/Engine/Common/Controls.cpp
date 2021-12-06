#include "Controls.h"

#include <iostream>

namespace Engine {

	double m_startPosX, m_startPosY;
	float m_InitialFOV = 45.0f;
	glm::vec3 m_Eye = glm::vec3(0, 0, 8);

	glm::vec3 startPos = glm::vec3(0, 0, 1);
	glm::vec3 currentPos = glm::vec3(0, 0, 1);

	glm::mat4 mainQuat = glm::mat4(1);
	glm::mat4 lastQuat = glm::mat4(1);
	glm::mat4 nextQuat = glm::mat4(1);

	float m_Radius = fminf(960.0f / 2, 540.0f / 2);

	glm::mat4 m_ViewMatrix = glm::lookAt(m_Eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFOV), 960.0f / 540.0f, 0.1f, 100.0f);

	static void Quaternion(float* q, float x, float y, float z, float w)
	{
		float x2 = x * x;
		float y2 = y * y;
		float z2 = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;
		float wx = w * x;
		float wy = w * y;
		float wz = w * z;

		q[0] = 1 - 2 * y2 - 2 * z2;
		q[1] = 2 * xy + 2 * wz;
		q[2] = 2 * xz - 2 * wy;

		q[4] = 2 * xy - 2 * wz;
		q[5] = 1 - 2 * x2 - 2 * z2;
		q[6] = 2 * yz + 2 * wx;

		q[8] = 2 * xz + 2 * wy;
		q[9] = 2 * yz - 2 * wx;
		q[10] = 1 - 2 * x2 - 2 * y2;
	}

	/*Controls::Controls()
	{
		m_ViewMatrix = glm::lookAt(m_Eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFOV), 960.0f / 540.0f, 0.1f, 100.0f);

		m_Radius = fminf(960.0f / 2, 540.0f / 2);
	}

	Controls::~Controls()
	{
	}*/

	/*void ComputeMatricesFromInputs(GLFWwindow* window, float deltaTime)
	{
		glfwGetCursorPos(window, &m_startPosX, &m_startPosY);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS)
		{
			return;
		}

		glm::vec3 p1 = CalculateSphereCoords(m_startPosX, m_startPosY);

		double currentPosX, currentPosY;
		glfwGetCursorPos(window, &currentPosX, &currentPosY);

		glm::vec3 p2 = CalculateSphereCoords(currentPosX, currentPosY);

		glm::vec3 rotationAxis = glm::cross(p1, p2);

		float rotationAngle = acosf(glm::dot(p1, p2));

		m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(rotationAngle) * 2, glm::vec3(-rotationAxis.x, -rotationAxis.y, -rotationAxis.z));

	}*/

	void RotateView()
	{
		m_ViewMatrix = m_ViewMatrix * mainQuat;
	}

	glm::mat4 GetProjectionMatrix()
	{
		return m_ProjectionMatrix;
	}

	glm::mat4 GetViewMatrix()
	{
		return m_ViewMatrix;
	}

	void StartPosition(float x, float y)
	{
		startPos = CalculateSphereCoords(x, y);
	}

	void MovePosition(float x, float y)
	{
		currentPos = CalculateSphereCoords(x, y);
		if (currentPos == startPos)
		{
			mainQuat = lastQuat;
			return;
		}

		float cos2a = glm::dot(startPos, currentPos);
		std::cout << "cos(angle) : " << cos2a << "\n";
		float sina = sqrt((1.0 - cos2a) * 0.5);
		std::cout << "cos(sina) : " << sina << "\n";
		float cosa = sqrt((1.0 + cos2a) * 0.5);
		glm::vec3 cross = glm::normalize(glm::cross(startPos, currentPos)) * sina;
		// quaternaion
		std::cout << "x, y, z, w : " << cross.x << " " << cross.y << " " << cross.z << " " << cosa << "\n";
		auto res = cross.x * cross.x + cross.y * cross.y + cross.z * cross.z + cosa * cosa;
		std::cout << "res: " << res << std::endl;

		if (res == 1)
		{
			Quaternion(&nextQuat[0][0], cross.x, cross.y, 0, cosa);
		}

		// quatnext
		mainQuat = lastQuat * nextQuat;

		RotateView();
	}

	glm::vec3 CalculateSphereCoords(float x, float y)
	{
		glm::vec3 point = glm::unProject(glm::vec3(x, y, 0), glm::mat4(1), m_ProjectionMatrix, glm::vec4(0, 0, 960, 540));
		point = point * (-1.0f);
		glm::vec3 m = point - m_Eye;
		float a = glm::dot(m, m);
		float b = glm::dot(m_Eye, m);
		float root = glm::dot(b, b) - glm::dot(a, (glm::dot(m_Eye, m_Eye) - m_Radius));
		if (root <= 0)
		{
			std::cout << "root = " << root << "\n";
			return glm::normalize(point);
		}
		float t = (0.0 - b - sqrt(root)) / a;
		return glm::normalize(m_Eye + (m * t));
	}



}