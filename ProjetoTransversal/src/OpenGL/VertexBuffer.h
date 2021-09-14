#pragma once
#include <iostream>

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	void SetData(const void* data, unsigned int size);
	void DeleteData();

private:
	unsigned int m_Id = 0;
};