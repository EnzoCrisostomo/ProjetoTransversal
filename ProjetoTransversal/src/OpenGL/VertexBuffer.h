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
	void SetData(const T* data, unsigned int size);

	void DeleteData();

private:
	unsigned int m_id = 0;
};