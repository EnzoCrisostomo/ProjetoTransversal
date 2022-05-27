#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& filePath, int mipLevel);

	~Texture();

	void loadFromFile(const std::string& filePath, int mipLevel);
	void BindTexture() const;

private:
	GLuint m_id = 0;
};

