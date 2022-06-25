#include "Block.h"

namespace
{
	static constexpr unsigned int TEXTURE_COUNT = 8;
	static constexpr float TEXTURE_STEP = 1.0 / TEXTURE_COUNT;
}

Block::Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const bool isVegetation,
			 const uint8_t topTextureIndex, const uint8_t sideTextureIndex, const uint8_t bottomTextureIndex)
	: m_name(name), m_blockId(blockId), m_isSolid(isSolid), m_transparency(isTransparent), m_isVegetation(isVegetation)
{
	m_topTextureIndex = topTextureIndex;
	m_sideTextureIndex = sideTextureIndex;
	m_bottomTextureIndex = bottomTextureIndex;

}

Block::Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const bool isVegetation, const uint8_t textureIndex)
	: m_name(name), m_blockId(blockId), m_isSolid(isSolid), m_transparency(isTransparent), m_isVegetation(isVegetation)
{
	m_topTextureIndex = textureIndex;
	m_sideTextureIndex = textureIndex;
	m_bottomTextureIndex = textureIndex;
}

const uint8_t& Block::GetTopTexture() const
{
	return m_topTextureIndex;
}

const uint8_t& Block::GetSideTexture() const
{
	return m_sideTextureIndex;
}

const uint8_t& Block::GetBottomTexture() const
{
	return m_bottomTextureIndex;
}
