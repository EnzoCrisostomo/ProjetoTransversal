#include "VertexBuffer.h"
#include "glad/glad.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	SetData(data, size);
}

void VertexBuffer::SetData(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_Id);
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	DeleteData();
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::DeleteData()
{
	glDeleteBuffers(1, &m_Id);
	m_Id = 0;
}