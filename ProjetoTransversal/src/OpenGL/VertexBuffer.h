#pragma once
#include <iostream>

class VertexBuffer
{
public:
	VertexBuffer() = default;
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;

	template<typename T>
	void SetData(const T* data, unsigned int size)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), static_cast<const void*>(data), GL_STATIC_DRAW);
	}

	void DeleteData();

private:
	unsigned int m_id = 0;
};