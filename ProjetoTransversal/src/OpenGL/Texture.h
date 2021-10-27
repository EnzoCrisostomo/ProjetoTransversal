#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& filePath);

	~Texture();

	void loadFromFile(const std::string& filePath);
	void BindTexture() const;

private:
	GLuint m_id = 0;
};

