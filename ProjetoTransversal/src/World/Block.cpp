#include "Block.h"

Block::Block(const BlockId& blockId, const bool isSolid, const bool isTranslucent, const glm::vec2& topTextureCoords,
	         const glm::vec2& sideTextureCoords, const glm::vec2& bottomTextureCoords)

	: m_blockId(blockId), m_isSolid(isSolid), m_isTranslucent(isTranslucent)
{
	Generatetextures(topTextureCoords, sideTextureCoords, bottomTextureCoords);
}

Block::Block(const BlockId& blockId, const bool isSolid, const bool isTranslucent, const glm::vec2& allTextureCoords)
	: m_blockId(blockId), m_isSolid(isSolid), m_isTranslucent(isTranslucent)
{
	Generatetextures(allTextureCoords, allTextureCoords, allTextureCoords);
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
	m_topTextureVector = { topTextureCoords.x        , topTextureCoords.y        ,
						   topTextureCoords.x        , topTextureCoords.y + 0.25f,
					       topTextureCoords.x + 0.25f, topTextureCoords.y + 0.25f,
						   topTextureCoords.x + 0.25f, topTextureCoords.y };

	m_sideTextureVector = { sideTextureCoords.x + 0.25f, sideTextureCoords.y		,
							sideTextureCoords.x        , sideTextureCoords.y        ,
							sideTextureCoords.x        , sideTextureCoords.y + 0.25f,
							sideTextureCoords.x + 0.25f, sideTextureCoords.y + 0.25f };

	m_bottomTextureVector = { bottomTextureCoords.x        , bottomTextureCoords.y        ,
							  bottomTextureCoords.x        , bottomTextureCoords.y + 0.25f,
							  bottomTextureCoords.x + 0.25f, bottomTextureCoords.y + 0.25f,
							  bottomTextureCoords.x + 0.25f, bottomTextureCoords.y };
}
