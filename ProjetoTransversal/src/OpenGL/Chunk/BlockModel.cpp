#include "BlockModel.h"

#include "../VertexBufferLayout.h"

BlockModel::BlockModel(const BlockMesh& mesh)
{
	SetData(mesh);
}

BlockModel::~BlockModel()
{
}

void BlockModel::SetData(const BlockMesh& mesh)
{
	if (m_vertexArray.getId() != 0)
		DeleteData();

	m_vertexArray.SetData();

	//TODO Classe para layouts
	//VertexBufferLayout layout;

	m_vertices.SetData<ChunkVertex>(mesh.vertices.data(),
		static_cast<unsigned int>(mesh.vertices.size()));

	//Vertices
	glVertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, sizeof(ChunkVertex), (GLvoid*)offsetof(ChunkVertex, positions));
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, sizeof(ChunkVertex), (GLvoid*)offsetof(ChunkVertex, light));
	glEnableVertexAttribArray(1);
	glVertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(ChunkVertex), (GLvoid*)offsetof(ChunkVertex, textureIndex));
	glEnableVertexAttribArray(2);

	m_indexBuffer.SetData(mesh.indices.data(),
		static_cast<unsigned int>(mesh.indices.size()));

}

void BlockModel::BindVao() const
{
	m_vertexArray.Bind();
}

GLuint BlockModel::GetIndicesCount() const
{
	return m_indexBuffer.GetCount();
}

void BlockModel::DeleteData()
{
	m_vertices.DeleteData();
	m_indexBuffer.DeleteData();
	m_vertexArray.DeleteData();
}
