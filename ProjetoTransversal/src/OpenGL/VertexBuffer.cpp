#include <glad/glad.h>
#include "VertexBuffer.h"
#include "Vertex.h"
#include "Chunk/ChunkVertex.h"

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