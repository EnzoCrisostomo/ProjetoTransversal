#include "ChunkMesh.h"
#include "Options/Options.h"
#include <iostream>

ChunkMesh::~ChunkMesh()
{
}

//Adiciona os vertices de uma face para a mesh
void ChunkMesh::AddBlockFace(const std::vector<GLfloat>& blockFace,
							 const std::vector<GLfloat>& textureCoords,
							 const glm::ivec3& chunkPosition,
							 const glm::ivec3& blockPosition)
{
	//Vertex Positions
	for (int i = 0, index = 0; i < 4; i++)
	{
		this->vertexPositions.push_back(blockFace[index] + chunkPosition.x * Options::chunkSize + blockPosition.x);
		index++;
		this->vertexPositions.push_back(blockFace[index] + chunkPosition.y * Options::chunkSize + blockPosition.y);
		index++;
		this->vertexPositions.push_back(blockFace[index] + chunkPosition.z * Options::chunkSize + blockPosition.z);
		index++;
	}
	//Texture coords
	this->textureCoordinates.insert(this->textureCoordinates.end(), textureCoords.begin(), textureCoords.end());

	//Indices
	this->indices.insert(this->indices.end(),
		{
			m_indicesCount,
			m_indicesCount + 1,
			m_indicesCount + 2,

			m_indicesCount + 2,
			m_indicesCount + 3,
			m_indicesCount
		});
	m_indicesCount += 4;
}

//Carrega a mesh para a placa de video
void ChunkMesh::BufferMesh()
{
	m_model.SetData((Mesh)*this);

	this->vertexPositions.clear();
	this->textureCoordinates.clear();
	this->indices.clear();

	this->vertexPositions.shrink_to_fit();
	this->textureCoordinates.shrink_to_fit();
	this->indices.shrink_to_fit();

	m_indicesCount = 0;
}

const Model& ChunkMesh::GetModel() const
{
	return m_model;
}
