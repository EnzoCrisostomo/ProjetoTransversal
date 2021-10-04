#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class GuiShader
{
public:
	GuiShader() = default;
	GuiShader(const char* shaderFilePath);
	~GuiShader();

	void LoadFromFile(const char* shaderFilePath);

	void Bind() const;
	void Unbind() const;

	void LoadInt(GLuint location, const int value) const;
	void LoadInt(GLuint location, const glm::ivec2& values) const;
	void LoadInt(GLuint location, const glm::ivec3& values) const;
	void LoadInt(GLuint location, const glm::ivec4& values) const;
	void LoadFloat(GLuint location, const float value) const;
	void LoadFloat(GLuint location, const glm::vec2& values) const;
	void LoadFloat(GLuint location, const glm::vec3& values) const;
	void LoadFloat(GLuint location, const glm::vec4& values) const;

	void LoadMatrix4(GLuint location, const glm::mat4 matrix) const;

	void loadProjectionMatrix(const glm::mat4 matrix);
private:
	GLuint m_programId = 0;
	GLuint m_projectionMatrixLocation = 0;

	void GetUniforms();
	void CompileShaders(const char* shaderFilePath, std::stringstream sourceArray[]) const;
};

