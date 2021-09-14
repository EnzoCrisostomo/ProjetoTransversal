#include "Shader.h"
#include <fstream>
#include <sstream>
#include <exception>

enum class ShaderType
{
    NONE = -1, 
    VERTEX, FRAGMENT, 
    
    TYPECOUNT
};

Shader::Shader(const char* shaderFilePath)
{
    LoadFromFile(shaderFilePath);
}

Shader::~Shader()
{
    glDeleteProgram(m_programId);
}

void Shader::LoadFromFile(const char* shaderFilePath)
{
    ShaderType type = ShaderType::NONE;
    std::stringstream sourceArray[(int)ShaderType::TYPECOUNT];

    std::ifstream file(shaderFilePath);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                if (line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else
            {
                sourceArray[(int)type] << line << '\n';
            }
        }
    }
    else
    {
        std::cerr << "Cannot open shader file!\n";
        throw std::runtime_error("Failed to load shader!");
        return;
    }
    m_programId = glCreateProgram();
    CompileShaders(shaderFilePath, sourceArray);
    glLinkProgram(m_programId);

    GetUniforms();
}

void Shader::GetUniforms()
{
    m_projectionMatrixLocation = glGetUniformLocation(m_programId, "projectionMatrix");
    m_viewMatrixLocation = glGetUniformLocation(m_programId, "viewMatrix");
    m_modelMatrixLocation = glGetUniformLocation(m_programId, "modelMatrix");
}

void Shader::CompileShaders(const char* shaderFilePath, std::stringstream sourceArray[]) const
{
    for (int i = 0; i < (int)ShaderType::TYPECOUNT; i++)
    {
        std::string x = sourceArray[i].str();
        const char* actual = x.c_str();
        if (i == (int)ShaderType::VERTEX)
        {
            int vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &actual, nullptr);
            glCompileShader(vertexShader);
            glAttachShader(m_programId, vertexShader);

            int success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED IN (" << shaderFilePath << ")\n" << infoLog << std::endl;
            };

            glDeleteShader(vertexShader);
        }
        else if (i == (int)ShaderType::FRAGMENT)
        {
            int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &actual, nullptr);
            glCompileShader(fragmentShader);
            glAttachShader(m_programId, fragmentShader);

            int success;
            char infoLog[512];
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED IN (" << shaderFilePath << ")\n" << infoLog << std::endl;
            };

            glDeleteShader(fragmentShader);
        }

    }
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
             
void Shader::LoadInt(GLuint location, const glm::ivec2& values) const
{
    glUniform2i(location, values.x, values.y);
}
           
void Shader::LoadInt(GLuint location, const glm::ivec3& values) const
{
    glUniform3i(location, values.x, values.y, values.z);
}
            
void Shader::LoadInt(GLuint location, const glm::ivec4& values) const
{
    glUniform4i(location, values.x, values.y, values.z, values.w);
}
            
void Shader::LoadFloat(GLuint location, const float value) const
{
    glUniform1f(location, value);
}
           
void Shader::LoadFloat(GLuint location, const glm::vec2& values) const
{
    glUniform2f(location, values.x, values.y);
}
           
void Shader::LoadFloat(GLuint location, const glm::vec3& values) const
{
    glUniform3f(location, values.x, values.y, values.z);
}
           
void Shader::LoadFloat(GLuint location, const glm::vec4& values) const
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

