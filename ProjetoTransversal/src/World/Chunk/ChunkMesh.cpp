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
		m_blocksMesh.vertexPositions.push_back(blockFace[index] + chunkPosition.x * Options::chunkSize + blockPosition.x);
		index++;
		m_blocksMesh.vertexPositions.push_back(blockFace[index] + chunkPosition.y * Options::chunkSize + blockPosition.y);
		index++;
		m_blocksMesh.vertexPositions.push_back(blockFace[index] + chunkPosition.z * Options::chunkSize + blockPosition.z);
		index++;
	}
	//Texture coords
	m_blocksMesh.textureCoordinates.insert(m_blocksMesh.textureCoordinates.end(), textureCoords.begin(), textureCoords.end());

	//Indices
	m_blocksMesh.indices.insert(m_blocksMesh.indices.end(),
		{
			m_blocksIndicesCount,
			m_blocksIndicesCount + 1,
			m_blocksIndicesCount + 2,

			m_blocksIndicesCount + 2,
			m_blocksIndicesCount + 3,
			m_blocksIndicesCount
		});
	m_blocksIndicesCount += 4;
}

void ChunkMesh::AddVegetationBlock(const std::vector<GLfloat>& textureCoords, const glm::ivec3& chunkPosition, const glm::ivec3& blockPosition)
{
	const std::vector<GLfloat>& blockFace =
	{
		0, 0, 1,
		1, 0, 0,
		1, 1, 0,
		0, 1, 1, 
	
		1, 0, 1,
		0, 0, 0,
		0, 1, 0,
		1, 1, 1,
	};
	//Vertex Positions
	for (int i = 0, index = 0; i < 8; i++)
	{
		m_vegetationMesh.vertexPositions.push_back(blockFace[index] + chunkPosition.x * Options::chunkSize + blockPosition.x);
		index++;
		m_vegetationMesh.vertexPositions.push_back(blockFace[index] + chunkPosition.y * Options::chunkSize + blockPosition.y);
		index++;
		m_vegetationMesh.vertexPositions.push_back(blockFace[index] + chunkPosition.z * Options::chunkSize + blockPosition.z);
		index++;
	}

	for (int i = 0; i < 2; i++)
	{
		//Texture coords
		m_vegetationMesh.textureCoordinates.insert(m_vegetationMesh.textureCoordinates.end(), textureCoords.begin(), textureCoords.end());
		//Indices
		m_vegetationMesh.indices.insert(m_vegetationMesh.indices.end(),
			{
				m_vegetationIndicesCount,
				m_vegetationIndicesCount + 1,
				m_vegetationIndicesCount + 2,

				m_vegetationIndicesCount + 2,
				m_vegetationIndicesCount + 3,
				m_vegetationIndicesCount
			});
		m_vegetationIndicesCount += 4;
	}
}

//Carrega a mesh para a placa de video
//Cria o Model da mesh
void ChunkMesh::BufferMesh()
{
	m_blocksModel.SetData(m_blocksMesh);

	m_blocksMesh.vertexPositions.clear();
	m_blocksMesh.textureCoordinates.clear();
	m_blocksMesh.indices.clear();
	m_blocksIndicesCount = 0;
	
	m_vegetationModel.SetData(m_vegetationMesh);
	
	m_vegetationMesh.vertexPositions.clear();
	m_vegetationMesh.textureCoordinates.clear();
	m_vegetationMesh.indices.clear();
	m_vegetationIndicesCount = 0;
}

const Model& ChunkMesh::GetVegetationModel() const
{
	return m_vegetationModel;
}
const Model& ChunkMesh::GetBlocksModel() const
{
	return m_blocksModel;
}
