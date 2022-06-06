#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

enum class ShaderType;

class Shader
{
public:
	Shader(const std::string shaderFilePath);
	~Shader();

	void LoadFromFile(const std::string shaderFilePath);
	const GLuint GetUniform(const char* name) const;

	void Bind() const;
	void Unbind() const;

	void LoadInt(GLuint location, const int value) const;
	void LoadiVec2(GLuint location, const glm::ivec2& values) const;
	void LoadiVec3(GLuint location, const glm::ivec3& values) const;
	void LoadiVec4(GLuint location, const glm::ivec4& values) const;
	void LoadFloat(GLuint location, const float value) const;
	void LoadVec2(GLuint location, const glm::vec2& values) const;
	void LoadVec3(GLuint location, const glm::vec3& values) const;
	void LoadVec4(GLuint location, const glm::vec4& values) const;

	void LoadMatrix4(GLuint location, const glm::mat4 matrix) const;

	void loadProjectionMatrix(const glm::mat4 matrix);
	void loadViewMatrix(const glm::mat4 matrix);
	void loadModelMatrix(const glm::mat4 matrix);
private:
	GLuint m_programId = 0;
	GLuint m_projectionMatrixLocation = 0;
	GLuint m_viewMatrixLocation = 0;
	GLuint m_modelMatrixLocation = 0;

	void GetUniforms();
	void CompileShaders(const std::string shaderFilePath, std::stringstream sourceArray[]) const;
	void CompileShader(const std::string shaderFilePath, ShaderType type) const;
};

