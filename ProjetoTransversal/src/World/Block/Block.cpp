#include "Block.h"

namespace
{
	constexpr unsigned int TEXTURE_COUNT = 8;
	constexpr float TEXTURE_STEP = 1.0 / TEXTURE_COUNT;
}

Block::Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent,
			 const glm::vec2& topTextureCoords, const glm::vec2& sideTextureCoords, const glm::vec2& bottomTextureCoords)
	: m_name(name), m_blockId(blockId), m_isSolid(isSolid), m_transparency(isTransparent)
{
	Generatetextures(topTextureCoords, sideTextureCoords, bottomTextureCoords);
}

Block::Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent,
			 const unsigned int topTextureIndex, const unsigned int sideTextureIndex, const unsigned int bottomTextureIndex)
	: m_name(name), m_blockId(blockId), m_isSolid(isSolid), m_transparency(isTransparent)
{
	glm::vec2 topTextureCoords = IndexToTextureCoords(topTextureIndex);
	glm::vec2 sideTextureCoords = IndexToTextureCoords(sideTextureIndex);
	glm::vec2 bottomTextureCoords = IndexToTextureCoords(bottomTextureIndex);

	Generatetextures(topTextureCoords, sideTextureCoords, bottomTextureCoords);
}

Block::Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const glm::vec2& textureCoords)
	: m_name(name), m_blockId(blockId), m_isSolid(isSolid), m_transparency(isTransparent)
{
	Generatetextures(textureCoords, textureCoords, textureCoords);
}

Block::Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const unsigned int textureIndex)
	: m_name(name), m_blockId(blockId), m_isSolid(isSolid), m_transparency(isTransparent)
{
	glm::vec2 textureCoords = IndexToTextureCoords(textureIndex);

	Generatetextures(textureCoords, textureCoords, textureCoords);
}

glm::vec2 Block::IndexToTextureCoords(unsigned int i) const
{
	unsigned int x = i % 8;
	unsigned int y = i / 8;
	return glm::vec2(x * TEXTURE_STEP, 1 - ((y + 1) * TEXTURE_STEP));
}

const std::vector<GLfloat>& Block::GetTopTexture() const
{
	return m_topTextureVector;
}

const std::vector<GLfloat>& Block::GetSideTexture() const
{
	return m_sideTextureVector;
}

const std::vector<GLfloat>& Block::GetBottomTexture() const
{
	return m_bottomTextureVector;
}

void Block::Generatetextures(const glm::vec2& topTextureCoords,
	const glm::vec2& sideTextureCoords, const glm::vec2& bottomTextureCoords)
{
	m_topTextureVector		= { topTextureCoords.x					, topTextureCoords.y ,
								topTextureCoords.x					, topTextureCoords.y + TEXTURE_STEP,
								topTextureCoords.x +	TEXTURE_STEP, topTextureCoords.y + TEXTURE_STEP,
								topTextureCoords.x +	TEXTURE_STEP, topTextureCoords.y };

	m_sideTextureVector		= { sideTextureCoords.x +	TEXTURE_STEP, sideTextureCoords.y ,
								sideTextureCoords.x					, sideTextureCoords.y ,
								sideTextureCoords.x					, sideTextureCoords.y + TEXTURE_STEP,
								sideTextureCoords.x +	TEXTURE_STEP, sideTextureCoords.y + TEXTURE_STEP };

	m_bottomTextureVector	= { bottomTextureCoords.x				, bottomTextureCoords.y ,
								bottomTextureCoords.x				, bottomTextureCoords.y + TEXTURE_STEP,
								bottomTextureCoords.x + TEXTURE_STEP, bottomTextureCoords.y + TEXTURE_STEP,
								bottomTextureCoords.x + TEXTURE_STEP, bottomTextureCoords.y };
}
