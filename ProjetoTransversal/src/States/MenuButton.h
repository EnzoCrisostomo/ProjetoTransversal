#pragma once
#include <glm/glm.hpp>
#include <string>

class MainMenuState;

class MenuButton
{
public:
	MenuButton( const glm::vec2& position,
				const glm::vec2& dimensions,
				void(MainMenuState::*function)(),
				const std::string& text = "Button",
				const std::string& m_bgTexturePath = "",
				const float scale = 1.0);

	bool IsHovered(const double& mouseX, const double& mouseY);

	glm::vec2 m_position;
	glm::vec2 m_dimensions;
	void(MainMenuState::*m_function)();
	std::string m_text;
	std::string m_bgTexturePath;
	float m_scale = 1.0f;


	bool m_hovered = false;
	bool m_clicked = false;
};

