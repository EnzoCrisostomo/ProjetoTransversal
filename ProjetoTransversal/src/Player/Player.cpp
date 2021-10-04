#include "World/World.h"
#include "Player.h"
#include "Options/Options.h"
#include "Math/Ray.h"
#include <iostream>
#include <iomanip>
bool temp_pulou = false;
namespace 
{
	BlockId selectedBlock = BlockId::DarkPlanks;
	constexpr double tolerance = 0.000001;
}

Player::Player()
	: m_speed(Options::playerSpeed),
	  m_gamemode(Options::playerGamemode),
	  m_elapsedTime(0.0),
	  m_window(nullptr),
	  m_isGrounded(false),

	  m_cameraFront		(glm::dvec3( 0.0,  0.0  , -1.0 )),
	  m_cameraUp		(glm::dvec3( 0.0,  1.0  ,  0.0 )),
	  m_position		(glm::dvec3( 5.0,  100.0,  5.0 )),
	  m_velocity		(glm::dvec3( 0.0,  0.0	 ,  0.0 )),
	  m_acceleration	(glm::dvec3( 0.0,  0.0  ,  0.0 )),

	  m_dimensions		(glm::dvec3( 0.3,  1.6  ,  0.3 )),

	  m_projectionMatrix (glm::dmat4(1)),
	  m_viewMatrix (glm::dmat4(1))
{
	CreateProjectionMatrix();
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	int num = static_cast<int>(selectedBlock);

	if (yoffset > 0)
		num++;
	else if (yoffset < 0)
		num--;

	if (num >= static_cast<int>(BlockId::blockCount))
		num = 1;
	else if (num < 1)
		num = static_cast<int>(BlockId::blockCount) - 1;

	selectedBlock = static_cast<BlockId>(num);
	//std::cout << "Numero: [" << num << "] Bloco: [" << (int)selectedBlock << "]\n";
	//std::cout << "Y: [" << yoffset << "] X: [" << xoffset << "]\n";
}

void Player::Update(World* world, double elapsedTime)
{
	m_elapsedTime = elapsedTime;

	HandleMouseInput();
	PlaceAndBreakBlocks(world);
	glm::dvec3 direction = HandleKeyboardInput();
	HandleMovement(world, direction);

	if(Options::teste)
		std::cout << "Position: x[" << m_position.x << "] y[" << m_position.y << "] z[" << m_position.z << "]\n";
	//std::cout << std::setprecision(4) << "Position: x[" << m_position.x << "] y[" << m_position.y << "] z[" << m_position.z << "]\n";
	//std::cout << "Velocity: x[" << m_velocity.x << "] y[" << m_velocity.y << "] z[" << m_velocity.z << "]\n";
	//std::cout << "Acceleration: x[" << m_acceleration.x << "] y[" << m_acceleration.y << "] z[" << m_acceleration.z << "]\n";
}

void Player::SetWindow(GLFWwindow* window)
{
	if (window)
	{
		m_window = window;
		glfwSetScrollCallback(window, scrollCallback);
	}
}

const bool Player::WillBreakBlock() const
{
	static double oldTime = glfwGetTime();
	static bool holdingMouse = false;

	double now = glfwGetTime();
	bool mousePressed = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

	if (mousePressed && (oldTime - now < -0.3 || !holdingMouse))
	{
		oldTime = now;
		holdingMouse = mousePressed;
		return true;
	}
	holdingMouse = mousePressed;
	return false;
}

const bool Player::WillPlaceBlock() const
{
	static double oldTime = glfwGetTime();
	static bool holdingMouse = false;

	double now = glfwGetTime();
	bool mousePressed = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

	if (mousePressed && (oldTime - now < -0.2 || !holdingMouse))
	{
		oldTime = now;
		holdingMouse = mousePressed;
		return true;
	}
	holdingMouse = mousePressed;
	return false;
}

const bool Player::WillGetBlock(BlockId block) const
{
	static double oldTime = glfwGetTime();
	static bool holdingMouse = false;

	double now = glfwGetTime();
	bool mousePressed = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

	if (mousePressed && (oldTime - now < -0.2 || !holdingMouse))
	{
		oldTime = now;
		holdingMouse = mousePressed;
		selectedBlock = block;
		return true;
	}
	holdingMouse = mousePressed;
	return false;
}

const bool Player::Pular() const
{
	static double oldTime = glfwGetTime();
	static bool holdingSpace = false;

	double now = glfwGetTime();
	bool spacePressed = glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS;

	if (spacePressed && (oldTime - now < -0.4 || !holdingSpace) && m_isGrounded)
	{
		oldTime = now;
		holdingSpace = spacePressed;
		return true;
	}
	holdingSpace = spacePressed;

	return false;
}
const BlockId Player::getBlockHoldingId() const
{
	return selectedBlock;
}

void Player::CreateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(glm::radians(Options::fov), (Options::windowWidth / Options::windowHeight), 0.1, 500.0);
}

void Player::HandleMovement(World* world, glm::dvec3 direction)
{
	//TODO menos aceleração quando se movendo no ar
	m_isGrounded = false;

	if (m_gamemode == 1)
		direction *= 4.0;
	if (m_gamemode == 2)
		direction *= 8.0;

	m_acceleration = { 0.0, 0.0, 0.0 };
	m_acceleration += direction.x * glm::normalize(glm::dvec3{ m_cameraFront.x, 0, m_cameraFront.z });
	m_acceleration += direction.z * glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
	m_acceleration += direction.y * m_cameraUp;
	m_acceleration *= m_speed;

	//gravidade
	if (m_gamemode == 0 && !temp_pulou)
	{
		m_acceleration.y -= 50.0 * m_elapsedTime;
	}
	temp_pulou = false;

	m_velocity += m_acceleration;

	auto correctedVelocity = m_velocity * m_elapsedTime;
	if (correctedVelocity.y > 1.2)
		correctedVelocity.y = 1.2;

	m_position.x += correctedVelocity.x;
	if(m_gamemode != 2)
		CheckCollision(world, { correctedVelocity.x, 0, 0 });
	m_position.y += correctedVelocity.y;
	if (m_gamemode != 2)
		CheckCollision(world, { 0, correctedVelocity.y, 0 });
	m_position.z += correctedVelocity.z;
	if (m_gamemode != 2)
		CheckCollision(world, { 0, 0, correctedVelocity.z });

	if (m_position.y <= -128.0)
		m_position.y = 255.0;


	//TODO ajeitar desaceleração do player dependente do FPS
	m_velocity.x *= 0.90;
	m_velocity.z *= 0.90;
	if (m_gamemode != 0)
		m_velocity.y *= 0.90;

	if (direction == glm::dvec3{ 0, 0, 0 })
	{
		if (m_velocity.x < 0.01 && m_velocity.x > -0.01)
			m_velocity.x = 0.0;
		if (m_velocity.z < 0.01 && m_velocity.z > -0.01)
			m_velocity.z = 0.0;
	}

	if (m_velocity.y >	100.0)
		m_velocity.y = 100.0;
	if (m_velocity.y < -100.0)
		m_velocity.y = -100.0;
}

glm::dvec3 Player::HandleKeyboardInput()
{
	glm::dvec3 direction = { 0.0, 0.0, 0.0 };

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		direction.x++;
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		direction.x--;
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		direction.z++;
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		direction.z--;
	if(direction != glm::dvec3{0.0, 0.0, 0.0})
		direction = glm::normalize(direction);
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		direction *= 2.0;
	if (m_gamemode == 0)
	{
		if (Pular())
		{
			m_isGrounded = false;
			direction.y += 25.0;
			temp_pulou = true;
		}
	}
	else
	{
		if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
			direction.y++;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			direction.y--;
	}
	static bool temp = true;
	if (glfwGetKey(m_window, GLFW_KEY_F1) == GLFW_PRESS)
	{
		if (temp)
		{
			m_gamemode++;
			if (m_gamemode >= 3)
			{
				m_gamemode = 0;
			}
		}
		temp = false;
	}
	else
		temp = true;


	// @teste
	static bool teste = true;
	if (glfwGetKey(m_window, GLFW_KEY_H) == GLFW_PRESS)
	{
		if (teste)
			Options::teste = !Options::teste;
		teste = false;
	}
	else
		teste = true;

	return direction;
}

void Player::PlaceAndBreakBlocks(World* world)
{
	glm::vec3 lastRayPos = Floor(GetPosition());
	for (Ray ray(GetPosition(), GetCameraFront()); ray.GetLenght() < 10; ray.Step(0.01))
	{
		glm::ivec3 blockPos = Floor(ray.GetEnd());
		BlockId blockId = world->GetBlock(blockPos);
		Block blockData = BlockDatabase::Get().GetBlockInfo(blockId);
		if (blockData.IsSolid())
		{
			//m_gizmo = blockPos;
			if (!WillGetBlock(blockId)) {
				if (WillBreakBlock())
				{
					world->SetBlock(blockPos, BlockId::Air);
				}
				if (WillPlaceBlock())
				{
					if (!CollidingWithBlock(Floor(lastRayPos)) || !BlockDatabase::Get().GetBlockInfo(getBlockHoldingId()).IsSolid()) {
						world->SetBlock(Floor(lastRayPos), getBlockHoldingId());
					}
				}
			}
			break;
		}
		else {
			//TODO tirar a gambiarra do wireframe de bloco selecionado
			//m_gizmo = { 4000000, 4000000, 4000000 };
		}
		lastRayPos = ray.GetEnd();
	}
}

//TODO ainda está um pouco bugado
bool Player::CollidingWithBlock(const glm::ivec3 blockPos) const
{
	if (Floor(m_position + glm::dvec3{ -m_dimensions.x, -m_dimensions.y, -m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{ -m_dimensions.x, -m_dimensions.y,  m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{ -m_dimensions.x,  0.2		   , -m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{ -m_dimensions.x,  0.2		   ,  m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{  m_dimensions.x, -m_dimensions.y, -m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{  m_dimensions.x, -m_dimensions.y,  m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{  m_dimensions.x,  0.2		   , -m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{  m_dimensions.x,  0.2		   ,  m_dimensions.z }) == blockPos)
		return true;

	//checar no meio do player
	if (Floor(m_position + glm::dvec3{  m_dimensions.x, -0.9		   , -m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{  m_dimensions.x, -0.9		   ,  m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{ -m_dimensions.x, -0.9		   , -m_dimensions.z }) == blockPos)
		return true;
	if (Floor(m_position + glm::dvec3{ -m_dimensions.x, -0.9		   ,  m_dimensions.z }) == blockPos)
		return true;

	return false;
}

void Player::NewCollisionDetect(World* world, glm::dvec3 velocity)
{
}

void Player::CheckCollision(World* world, const glm::dvec3 vel)
{
	int iter = 0;
	for(int x = floor(m_position.x - m_dimensions.x); x < m_position.x + m_dimensions.x; x++)
	for(int y = floor(m_position.y - m_dimensions.y); y < m_position.y + 0.2		   ; y++)
	for(int z = floor(m_position.z - m_dimensions.z); z < m_position.z + m_dimensions.z; z++)
	{
		iter++;
		auto blockPos = glm::ivec3{ x, y, z };
		BlockId bloco = world->GetBlock(blockPos);

		auto rs = BlockDatabase::Get().GetBlockInfo(bloco);
		auto temp = m_position;
		/*std::cout << "======================================================\n";
		if (rs.GetName() == "DarkPlanks")
		{
			std::cout << "!!!: " << '\n';
		}
		std::cout << rs.GetName() << '\n';
		std::cout << "Iteration: " << iter << '\n';
		std::cout << "OldPos: x[" << temp.x << "] y[" << temp.y << "] z[" << temp.z << "]\n";
		std::cout << "vars: x[" << x << "] y[" << y << "] z[" << z << "]\n";
		std::cout << "BlockPos: x[" << blockPos.x << "] y[" << blockPos.y << "] z[" << blockPos.z << "]\n";
		std::cout << "Calc: x[" << m_position.x - m_dimensions.x << "] y[" << m_position.y - m_dimensions.y << "] z[" << m_position.z - m_dimensions.z << "]\n";
		std::cout << "VEL: x[" << vel.x << "] y[" << vel.y << "] z[" << vel.z << "]\n";
		std::cout << "NewPos: x[" << m_position.x << "] y[" << m_position.y << "] z[" << m_position.z << "]\n";
		std::cout << "======================================================\n";*/

		if (bloco == BlockId::Air)
			continue;

		if (rs.IsSolid())
		{
			if (vel.y > 0) {
				m_position.y = y - 0.2 - tolerance;
				m_velocity.y = 0;
			}
			else if (vel.y < 0) {
				m_isGrounded = true;
				m_position.y = y + m_dimensions.y + 1 + tolerance;
				m_velocity.y = 0;
			}

			if (vel.x > 0) {
				m_position.x = x - m_dimensions.x - tolerance;
				m_velocity.x = 0;
			}
			else if (vel.x < 0) {
				m_position.x = x + m_dimensions.x + 1 + tolerance;
				m_velocity.x = 0;
			}

			if (vel.z > 0) {
				m_position.z = z - m_dimensions.z - tolerance;
				m_velocity.z = 0;
			}
			else if (vel.z < 0) {
				m_position.z = z + m_dimensions.z + 1 + tolerance;
				m_velocity.z = 0;
			}
		}
	}
}


void Player::HandleMouseInput()
{
	static double yaw = -90.0;
	static double pitch = 0.0;

	static double lastX = 0;
	static double lastY = 0;

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

	//TODO achar algoritimo mais preciso
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
