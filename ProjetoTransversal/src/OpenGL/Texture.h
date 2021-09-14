#pragma once


#include <iostream>
#include <glad/glad.h>

class Texture
{
public:
	Texture() = default;
	Texture(const std::string& filePath);

	~Texture();

	void loadFromFile(const std::string& filePath);
	void BindTexture() const;

private:
	GLuint m_id = 0;
};

