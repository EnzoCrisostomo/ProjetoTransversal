#pragma once
#include "Math/Vectors.h"
#include <vector>
#include <cinttypes>

typedef float GLfloat;

enum class BlockId : uint8_t
{
	Air = 0,
	GrassBlock,
	Dirt,
	Stone,
	Sand,
	SnowGrass,
	Snow,
	StoneBrick,
	Water,
	Lava,
	DarkWood,
	LightWood,
	PineWood,
	Leaf,
	LightLeaf,
	PineLeaf,
	Cactus,
	Mushroom,
	MushroomStalk,
	DarkPlanks,
	LightPlanks,
	PinePlanks,
	Bricks,
	Glass,
	BookShelf,
	Grass,
	Poppy,
	Lily,
	Dandelion,
	BlueOrchid,

	blockCount
};

enum class Transparency
{
	Opaque,
	Half,
	Full,
};

class Block
{
public:
	Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const bool isVegetation,
		const glm::vec2& topTextureCoords, const glm::vec2& sideTextureCoords, const glm::vec2& bottomTextureCoords);
	Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const bool isVegetation,
		const unsigned int topTextureIndex, const unsigned int sideTextureIndex, const unsigned int bottomTextureIndex);

	Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const bool isVegetation, 
		const glm::vec2& textureCoords);
	Block(const char* name, const BlockId& blockId, const bool isSolid, Transparency isTransparent, const bool isVegetation, 
		const unsigned int textureIndex);

	const bool operator == (const Block& other) const
	{
		return this->m_blockId == other.m_blockId;
	}
	const bool IsSolid() const { return m_isSolid; };
	const bool IsVegetation() const { return m_isVegetation; };

	Transparency IsTranslucent() const { return m_transparency; };

	const char* GetName() const { return m_name; };
	const BlockId& GetId() const { return m_blockId; };

	const std::vector<GLfloat>& GetTopTexture() const;
	const std::vector<GLfloat>& GetSideTexture() const;
	const std::vector<GLfloat>& GetBottomTexture() const;
private:
	glm::vec2 IndexToTextureCoords(unsigned int i) const;
	void Generatetextures(const glm::vec2& topTextureCoords,
		const glm::vec2& sideTextureCoords, const glm::vec2& bottomTextureCoords);

	std::vector<GLfloat> m_topTextureVector;
	std::vector<GLfloat> m_sideTextureVector;
	std::vector<GLfloat> m_bottomTextureVector;

	const char* m_name;
	const BlockId m_blockId;
	const bool m_isSolid;
	const bool m_isVegetation;
	Transparency m_transparency;
};