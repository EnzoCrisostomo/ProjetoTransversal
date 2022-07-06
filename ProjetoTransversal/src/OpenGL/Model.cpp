#include "Model.h"

#include "VertexBufferLayout.h"

Model::Model(const Mesh& mesh)
{
	SetData(mesh);
}

Model::~Model()
{
}

void Model::SetData(const Mesh& mesh)
{
	if (m_vertexArray.getId() != 0)
		DeleteData();

	m_vertexArray.SetData();

	//TODO Classe para layouts
	//VertexBufferLayout layout;

	m_vertices.SetData<Vertex>(mesh.vertices.data(),
		static_cast<unsigned int>(mesh.vertices.size()));

	//Vertices
	glVertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, positions));
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, light));
	glEnableVertexAttribArray(1);
	glVertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureIndex));
	glEnableVertexAttribArray(2);

	m_indexBuffer.SetData(mesh.indices.data(),
		static_cast<unsigned int>(mesh.indices.size()));

}

void Model::BindVao() const
{
	m_vertexArray.Bind();
}

GLuint Model::GetIndicesCount() const
{
	return m_indexBuffer.GetCount();
}

void Model::DeleteData()
{
	m_vertices.DeleteData();

	m_indexBuffer.DeleteData();
	
	m_vertexArray.DeleteData();
}
