#pragma once
#include <glad/glad.h>

class VertexArray
{
public:
	VertexArray() = default;
	~VertexArray();
	
	void Bind() const;
	void Unbind() const;
	
	void SetData();
	void DeleteData();

	GLuint getId() const { return m_Id; }
private:
	GLuint m_Id = 0;
};