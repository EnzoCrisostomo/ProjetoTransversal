#include "ChunkMesh.h"
#include "Options/Options.h"
#include <iostream>

namespace Face
{
	const std::vector<GLfloat> front
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
	};

	const std::vector<GLfloat> back
	{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
	};

	const std::vector<GLfloat> left
	{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,
	};

	const std::vector<GLfloat> right
	{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,
	};

	const std::vector<GLfloat> top
	{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,
	};

	const std::vector<GLfloat> bottom
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};
}

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

	float value = 0.8;
	if (blockFace == Face::top)
		value = 1;
	else if (blockFace == Face::bottom)
		value = 0.5;
	m_blocksMesh.lightValues.push_back(value);
}

void ChunkMesh::AddWaterBlockFace(std::vector<GLfloat> blockFace,
							 const std::vector<GLfloat>& textureCoords,
							 const glm::ivec3& chunkPosition,
							 const glm::ivec3& blockPosition,
							 const bool isUpper)
{
	if(isUpper)
		for (int i = 1; i < 11; i+=3)
			blockFace[i] = blockFace[i] == 1 ? 0.8f : 0;

	//Vertex Positions
	for (int i = 0, index = 0; i < 4; i++)
	{
		m_waterMesh.vertexPositions.push_back(blockFace[index] + chunkPosition.x * Options::chunkSize + blockPosition.x);
		index++;
		m_waterMesh.vertexPositions.push_back(blockFace[index] + chunkPosition.y * Options::chunkSize + blockPosition.y);
		index++;
		m_waterMesh.vertexPositions.push_back(blockFace[index] + chunkPosition.z * Options::chunkSize + blockPosition.z);
		index++;
	}
	//Texture coords
	m_waterMesh.textureCoordinates.insert(m_waterMesh.textureCoordinates.end(), textureCoords.begin(), textureCoords.end());
	
	//Indices
	m_waterMesh.indices.insert(m_waterMesh.indices.end(),
		{
			m_waterIndicesCount,
			m_waterIndicesCount + 1,
			m_waterIndicesCount + 2,

			m_waterIndicesCount + 2,
			m_waterIndicesCount + 3,
			m_waterIndicesCount
		});
	m_waterIndicesCount += 4;
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
	m_blocksMesh.Free();
	m_blocksIndicesCount = 0;
	
	m_vegetationModel.SetData(m_vegetationMesh);
	m_vegetationMesh.Free();
	m_hasVegetation = m_vegetationIndicesCount > 0;
	m_vegetationIndicesCount = 0;
	
	m_waterModel.SetData(m_waterMesh);
	m_waterMesh.Free();
	m_hasWater = m_waterIndicesCount > 0;
	m_waterIndicesCount = 0;
}

const Model& ChunkMesh::GetVegetationModel() const
{
	return m_vegetationModel;
}
const Model& ChunkMesh::GetBlocksModel() const
{
	return m_blocksModel;
}
const Model& ChunkMesh::GetWaterModel() const
{
	return m_waterModel;
}
