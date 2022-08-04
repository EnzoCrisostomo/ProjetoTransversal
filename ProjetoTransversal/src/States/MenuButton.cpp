#include "MenuButton.h"
#include "Options/Options.h"

MenuButton::MenuButton( const glm::vec2& position,
						const glm::vec2& dimensions,
						void(*function)(),
						const std::string& text,
						const std::string& bgTexturePath,
						const float scale)
	:	m_position(position),
		m_dimensions(dimensions),
		m_function(function),
		m_text(text),
		m_bgTexturePath(bgTexturePath),
		m_scale(scale)
{
}

bool MenuButton::IsHovered(const double& mouseX, const double& mouseY)
{
	double minX = (Options::windowWidth / 2.0)  + m_position.x - (m_dimensions.x * m_scale / 2.0);
	double maxX = (Options::windowWidth / 2.0)  + m_position.x + (m_dimensions.x * m_scale / 2.0);
	double minY = (Options::windowHeight / 2.0) - m_position.y - (m_dimensions.y * m_scale / 2.0);
	double maxY = (Options::windowHeight / 2.0) - m_position.y + (m_dimensions.y * m_scale / 2.0);

	return (mouseX > minX && mouseX < maxX) && (mouseY > minY && mouseY < maxY);
}
