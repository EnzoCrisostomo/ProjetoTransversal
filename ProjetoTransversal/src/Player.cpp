#include "Player.h"
#include "Options/Options.h"
#include <iostream>

Player::Player()
	: m_speed(Options::playerSpeed),
	  m_gamemode(Options::playerGamemode),
	  m_elapsedTime(0.0f),
	  m_window(nullptr),

	  m_cameraFront(glm::vec3( 0.0f,  0.0f, -1.0f)),
	  m_cameraUp   (glm::vec3( 0.0f,  1.0f,  0.0f)),
	  m_position   (glm::vec3( 0.0f,  80.0f,  3.0f )),
	  m_rotation   (glm::vec3( 0.0f,  0.0f,  0.0f )),

	  m_projectionMatrix (glm::mat4(1)),
	  m_viewMatrix (glm::mat4(1))
{
	CreateProjectionMatrix();
}

void Player::Update(GLFWwindow* window, double elapsedTime)
{
	m_window = window;
	m_elapsedTime = elapsedTime;
	HandleKeyboardInput();
	HandleMouseInput();
	//std::cout << "Player: x[" << m_position.x << "] y[" << m_position.y << "] z[" << m_position.z << "]\n";
}

void Player::CreateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(glm::radians(Options::fov), (Options::windowWidth / Options::windowHeight), 0.1f, 500.0f);
}

void Player::HandleKeyboardInput()
{
	float distanceTraveled = m_speed * m_elapsedTime;

	if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		distanceTraveled *= 5;

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_position += distanceTraveled * m_cameraFront;

	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_position -= distanceTraveled * m_cameraFront;

	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_position -= distanceTraveled * glm::normalize(glm::cross(m_cameraFront, m_cameraUp));

	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_position += distanceTraveled * glm::normalize(glm::cross(m_cameraFront, m_cameraUp));

	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_position += distanceTraveled * m_cameraUp;

	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		m_position -= distanceTraveled * m_cameraUp;

	// @teste
	if (glfwGetKey(m_window, GLFW_KEY_H) == GLFW_PRESS)
		Options::teste = !Options::teste;
}

void Player::HandleMouseInput()
{
	static double yaw = -90.0;
	static double pitch = 0.0;

	static double lastX = 400.0;
	static double lastY = 300.0;

	double xPos, yPos;
	glfwGetCursorPos(m_window, &xPos, &yPos);

	double xOffset = xPos - lastX;
	double yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	double sensitivity = Options::mouseSensibility;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw   += xOffset;
	pitch += yOffset;

	if (pitch > 89.5)
		pitch = 89.5;
	if (pitch < -89.5)
		pitch = -89.5;

	glm::dvec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_cameraFront = glm::normalize(direction);
	//std::cout << "Camera Front: x[" << m_cameraFront.x << "] y[" << m_cameraFront.y << "] z[" << m_cameraFront.z << "]\033[F";

	m_viewMatrix = glm::lookAt(m_position, m_position + m_cameraFront, m_cameraUp);
}
