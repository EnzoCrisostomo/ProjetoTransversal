#pragma once
#include <glad/glad.h>
#include <vector>

namespace {
	template<typename T>
	struct FalseStruct : std::false_type
	{ };
}

struct VertexBufferElement
{
	VertexBufferElement(unsigned int type, unsigned int count, unsigned int normalized, unsigned int offset)
		: m_type(type), m_count(count), m_normalized(normalized), m_offset(offset) {}

	unsigned int m_type;
	unsigned int m_count;
	unsigned int m_normalized;
	unsigned int m_offset;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() = default;
	~VertexBufferLayout() = default;

	template<typename T>
	void Push(int count)
	{
		static_assert(FalseStruct<T>::value, "this function has to be implemented for desired type");
	}
	template<>
	void Push<float>(int count)
	{
		m_elements.emplace_back(GL_FLOAT, count, GL_FALSE, m_offset);
		m_stride += sizeof(GLfloat) * count;
		m_offset += sizeof(GLfloat) * count;
	}
	template<>
	void Push<unsigned int>(int count)
	{
		m_elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE, m_offset);
		m_stride += sizeof(GLuint) * count;
		m_offset += sizeof(GLfloat) * count;
	}
	template<>
	void Push<unsigned char>(int count)
	{
		m_elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE, m_offset);
		m_stride += sizeof(GLubyte) * count;
		m_offset += sizeof(GLfloat) * count;
	}

	void setLayout()
	{
		for (unsigned int i = 0; i < m_elements.size(); i++)
		{
			glVertexAttribPointer(i, m_elements[i].m_count, m_elements[i].m_type,
				m_elements[i].m_normalized, m_stride, (void*)m_elements[i].m_offset);
			glEnableVertexAttribArray(i);
		}
	}

private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride = 0;
	unsigned int m_offset = 0;
};