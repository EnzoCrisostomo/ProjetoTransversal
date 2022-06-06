#include "Shader.h"
#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>


enum class ShaderType
{
    NONE = -1, 

    VERTEX,
    FRAGMENT,

    TYPECOUNT
};

namespace
{
    std::string GetFileExtension(const ShaderType& type)
    {
        switch (type)
        {
        case ShaderType::VERTEX:
            return ".vert";
            break;
        case ShaderType::FRAGMENT:
            return ".frag";
            break;
        default:
            throw std::runtime_error("Invalid Shader Type.");
            return "ERROR";
            break;
        }
    }
    
    std::string GetShaderName(const ShaderType& type)
    {
        switch (type)
        {
        case ShaderType::VERTEX:
            return "VERTEX";
            break;
        case ShaderType::FRAGMENT:
            return "FRAGMENT";
            break;
        default:
            throw std::runtime_error("Invalid Shader Type.");
            return "ERROR";
            break;
        }
    }

    int CreateShaderType(const ShaderType& type)
    {
        switch (type)
        {
        case ShaderType::VERTEX:
            return glCreateShader(GL_VERTEX_SHADER);;
            break;
        case ShaderType::FRAGMENT:
            return glCreateShader(GL_FRAGMENT_SHADER);;
            break;
        default:
            throw std::runtime_error("Invalid Shader Type.");
            return -1;
            break;
        }
    }
}

Shader::Shader(const std::string shaderFilePath)
{
    LoadFromFile(shaderFilePath);
}

Shader::~Shader()
{
    glDeleteProgram(m_programId);
}

void Shader::LoadFromFile(const std::string shaderFilePath)
{
    m_programId = glCreateProgram();
    CompileShader(shaderFilePath, ShaderType::VERTEX);
    CompileShader(shaderFilePath, ShaderType::FRAGMENT);
    glLinkProgram(m_programId);

    GetUniforms();
}

const GLuint Shader::GetUniform(const char* name) const
{
    return glGetUniformLocation(m_programId, name);;
}

void Shader::GetUniforms()
{
    m_projectionMatrixLocation = glGetUniformLocation(m_programId, "projectionMatrix");
    m_viewMatrixLocation = glGetUniformLocation(m_programId, "viewMatrix");
    m_modelMatrixLocation = glGetUniformLocation(m_programId, "modelMatrix");
}

void Shader::CompileShader(std::string shaderFilePath, ShaderType type) const
{
    std::stringstream sourceCode;
    shaderFilePath += GetFileExtension(type);

    std::cout << shaderFilePath << "\n";

    std::ifstream file(shaderFilePath);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            sourceCode << line << '\n';
        }
    }
    std::string aa = sourceCode.str();
    const char* str = aa.c_str();
    int shaderId = CreateShaderType(type);

    glShaderSource(shaderId, 1, &str, nullptr);
    glCompileShader(shaderId);
    glAttachShader(m_programId, shaderId);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << GetShaderName(type) << "::COMPILATION_FAILED IN (" << shaderFilePath << ")\n" << infoLog << std::endl;
    };

    glDeleteShader(shaderId);
}

void Shader::Bind() const
{
    glUseProgram(m_programId);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::LoadInt(GLuint location, const int value) const
{
    glUniform1i(location, value);
}
             
void Shader::LoadiVec2(GLuint location, const glm::ivec2& values) const
{
    glUniform2i(location, values.x, values.y);
}
           
void Shader::LoadiVec3(GLuint location, const glm::ivec3& values) const
{
    glUniform3i(location, values.x, values.y, values.z);
}
            
void Shader::LoadiVec4(GLuint location, const glm::ivec4& values) const
{
    glUniform4i(location, values.x, values.y, values.z, values.w);
}
            
void Shader::LoadFloat(GLuint location, const float value) const
{
    glUniform1f(location, value);
}
           
void Shader::LoadVec2(GLuint location, const glm::vec2& values) const
{
    glUniform2f(location, values.x, values.y);
}
           
void Shader::LoadVec3(GLuint location, const glm::vec3& values) const
{
    glUniform3f(location, values.x, values.y, values.z);
}
           
void Shader::LoadVec4(GLuint location, const glm::vec4& values) const
{
    glUniform4f(location, values.x, values.y, values.z, values.w);
}

void Shader::LoadMatrix4(GLuint location, const glm::mat4 matrix) const
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::loadProjectionMatrix(const glm::mat4 matrix)
{
    LoadMatrix4(m_projectionMatrixLocation, matrix);
}

void Shader::loadViewMatrix(const glm::mat4 matrix)
{
    LoadMatrix4(m_viewMatrixLocation, matrix);
}

void Shader::loadModelMatrix(const glm::mat4 matrix)
{
    LoadMatrix4(m_modelMatrixLocation, matrix);
}