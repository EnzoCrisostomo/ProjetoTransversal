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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, positions));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
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
