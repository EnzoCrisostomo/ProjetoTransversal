#pragma once

#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "BlockMesh.h"

class BlockModel
{
public:
	BlockModel() = default;
	BlockModel(const BlockMesh& mesh);
	~BlockModel();

	void SetData(const BlockMesh& mesh);
	void DeleteData();
	void BindVao() const;
	GLuint GetIndicesCount() const;

private:
	VertexBuffer m_vertices;
	IndexBuffer m_indexBuffer;
	VertexArray m_vertexArray;

};