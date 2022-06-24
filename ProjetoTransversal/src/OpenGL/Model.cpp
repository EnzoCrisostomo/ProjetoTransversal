#include "Model.h"

#include "VertexBufferLayout.h"

Model::Model(Mesh& mesh)
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

	m_vertexPositions.SetData(mesh.vertices.data(),
		static_cast<unsigned int>(mesh.vertices.size()));

	//VertexPos
	glVertexAttribPointer(0, 1, GL_UNSIGNED_INT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//layout.Push<float>(3);
	//layout.setLayout();

	//m_vertexTextureCoordinates.SetData(mesh.textureCoordinates.data(),
	//	static_cast<unsigned int>(mesh.textureCoordinates.size()));

	////Vertex Texture Coords
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	//glEnableVertexAttribArray(1);
	////layout.Push<float>(3);
	////layout.setLayout();

	//m_vertexLightValue.SetData(mesh.lightValues.data(),
	//	static_cast<unsigned int>(mesh.lightValues.size()));
	//glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	//glEnableVertexAttribArray(2);

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
	m_vertexPositions.DeleteData();
	m_vertexTextureCoordinates.DeleteData();
	m_vertexLightValue.DeleteData();

	m_indexBuffer.DeleteData();
	
	m_vertexArray.DeleteData();
}
