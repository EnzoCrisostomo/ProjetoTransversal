#include <glad/glad.h>
#include "VertexArray.h"


VertexArray::~VertexArray()
{
	DeleteData();
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_Id);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::SetData()
{
	glGenVertexArrays(1, &m_Id);
	glBindVertexArray(m_Id);
}

void VertexArray::DeleteData()
{
	glDeleteVertexArrays(1, &m_Id);
	m_Id = 0;
}