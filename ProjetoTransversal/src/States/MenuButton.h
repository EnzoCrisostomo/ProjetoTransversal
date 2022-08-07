#pragma once
#include "Options/Options.h"
#include <glm/glm.hpp>
#include <string>

template<typename ParentType>
class MenuButton
{
public:
	MenuButton(const glm::vec2& position,
		const glm::vec2& dimensions,
		ParentType* parent,
		void(ParentType::* function)(),
		const std::string& text = "Button",
		const std::string& bgTexturePath = "",
		const float scale = 1.0)
		:
		m_position(position),
		m_dimensions(dimensions),
		m_parent(parent),
		m_function(function),
		m_text(text),
		m_bgTexturePath(bgTexturePath),
		m_scale(scale)
	{
	}

	void Update(const double& mouseX, const double& mouseY, const bool& click)
	{
		bool hovered = IsHovered(mouseX, mouseY);
		if (hovered && click)
			(m_parent->*m_function)();
	}

private:
	bool IsHovered(const double& mouseX, const double& mouseY)
	{
		double minX = (Options::windowWidth / 2.0) + m_position.x - (m_dimensions.x * m_scale / 2.0);
		double maxX = (Options::windowWidth / 2.0) + m_position.x + (m_dimensions.x * m_scale / 2.0);
		double minY = (Options::windowHeight / 2.0) - m_position.y - (m_dimensions.y * m_scale / 2.0);
		double maxY = (Options::windowHeight / 2.0) - m_position.y + (m_dimensions.y * m_scale / 2.0);

		return (mouseX > minX && mouseX < maxX) && (mouseY > minY && mouseY < maxY);
	}

public:
	glm::vec2 m_position;
	glm::vec2 m_dimensions;
	ParentType* m_parent;
	void(ParentType::*m_function)();
	std::string m_text;
	std::string m_bgTexturePath;
	float m_scale = 1.0f;
};

