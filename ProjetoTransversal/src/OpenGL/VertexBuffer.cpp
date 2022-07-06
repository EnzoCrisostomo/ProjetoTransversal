#include <glad/glad.h>
#include "VertexBuffer.h"
#include "Vertex.h"

template<typename T>
void VertexBuffer::SetData(const T* data, unsigned int size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), static_cast<const void*>(data), GL_STATIC_DRAW);
}

template<>
void VertexBuffer::SetData<GLfloat>(const GLfloat* data, unsigned int size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), static_cast<const void*>(data), GL_STATIC_DRAW);
}

template<>
void VertexBuffer::SetData<GLuint>(const GLuint* data, unsigned int size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLuint), static_cast<const void*>(data), GL_STATIC_DRAW);
}

template<>
void VertexBuffer::SetData<Vertex>(const Vertex* data, unsigned int size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), static_cast<const void*>(data), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	DeleteData();
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::DeleteData()
{
	glDeleteBuffers(1, &m_id);
	m_id = 0;
}