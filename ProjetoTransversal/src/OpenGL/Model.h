#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"

class Model
{
public:
	Model() = default;
	Model(const Mesh& mesh);
	~Model();

	void SetData(const Mesh& mesh);
	void DeleteData();
	void BindVao() const;
	GLuint GetIndicesCount() const;

private:
	VertexBuffer m_vertices;
	IndexBuffer m_indexBuffer;
	VertexArray m_vertexArray;

};