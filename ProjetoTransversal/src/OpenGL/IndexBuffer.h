#pragma once
#include <iostream>
class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const { return m_count; }
	void SetData(const unsigned int* data, unsigned int count);
	void DeleteData();

private:
	unsigned int m_Id = 0;
	unsigned int m_count = 0;
};