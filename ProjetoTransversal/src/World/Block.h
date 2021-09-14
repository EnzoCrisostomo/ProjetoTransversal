#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <vector>

typedef float GLfloat;

enum class BlockId
{
	Air,
	Grass,
	Dirt,
	Stone,
	DarkWood,
	LightWood,
	Leaf,
	Sand,
	SandStone,
	StoneBrick,
	DarkPlanks,
	LightPlanks,
	Lava,

	blockCount
};

class Block
{
public:
	Block(const BlockId& blockId, const bool isSolid, const bool isTranslucent, const glm::vec2& topTextureCoords,
		  const glm::vec2& sideTextureCoords, const glm::vec2& bottomTextureCoords);

	Block(const BlockId& blockId, const bool isSolid, const bool isTranslucent, const glm::vec2& allTextureCoords);

	const bool operator = (const Block& other) const
	{
		return this->m_blockId == other.m_blockId;
	}
	const bool IsSolid() const { return m_isSolid; };

	const bool IsTranslucent() const { return m_isTranslucent; };

	const std::vector<GLfloat>& GetTopTexture() const;
	const std::vector<GLfloat>& GetSideTexture() const;
	const std::vector<GLfloat>& GetBottomTexture() const;
private:
	void Generatetextures(const glm::vec2& topTextureCoords,
		const glm::vec2& sideTextureCoords, const glm::vec2& bottomTextureCoords);

	std::vector<GLfloat> m_topTextureVector;
	std::vector<GLfloat> m_sideTextureVector;
	std::vector<GLfloat> m_bottomTextureVector;

	const BlockId m_blockId;
	const bool m_isSolid;
	const bool m_isTranslucent;
};

