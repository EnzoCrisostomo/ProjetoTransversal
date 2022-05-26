#include "ChunkMeshBuilder.h"
#include "Chunk.h"
#include "Options/Options.h"

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

struct AdjacentBlocks
{
    glm::ivec3 up;
    glm::ivec3 down;
    glm::ivec3 left;
    glm::ivec3 right;
    glm::ivec3 front;
    glm::ivec3 back;

    void update(int x, int y, int z)
    {
        up =    { x,     y + 1,  z };
        down =  { x,     y - 1,  z };
        left =  { x - 1, y,      z };
        right = { x + 1, y,      z };
        front = { x,     y,      z + 1 };
        back =  { x,     y,      z - 1 };
    }
};

void ChunkMeshBuilder::BuildMesh(Chunk& chunk)
{
    m_chunk = &chunk;
    m_chunkMesh = &(m_chunk->GetMesh());
    AdjacentBlocks adjacentBlocks;

    for(int y = 0; y < Options::chunkSize; y++)
    for(int x = 0; x < Options::chunkSize; x++)
    for(int z = 0; z < Options::chunkSize; z++)
    {
        BlockId blockId = m_chunk->GetBlock(x, y, z);

        if (blockId == BlockId::Air)
            continue;

        adjacentBlocks.update(x, y, z);
        const glm::ivec3 blockPosition = { x, y, z };

        TryToAddBlock(blockId, blockPosition, adjacentBlocks);
    }
}

void ChunkMeshBuilder::TryToAddBlock(const BlockId& blockId, const glm::ivec3& blockPosition, const AdjacentBlocks& adjacentBlocks)
{
    const Block& block = BlockDatabase::Get().GetBlockInfo(blockId);

    if (block.IsVegetation())
    {
        m_chunkMesh->AddVegetationBlock(block.GetSideTexture(), m_chunk->GetLocation(), blockPosition);
    }
    else
    {
        TryToAddFace(blockId, Face::top, block.GetTopTexture(), blockPosition, adjacentBlocks.up);
        TryToAddFace(blockId, Face::bottom, block.GetBottomTexture(), blockPosition, adjacentBlocks.down);

        TryToAddFace(blockId, Face::left, block.GetSideTexture(), blockPosition, adjacentBlocks.left);
        TryToAddFace(blockId, Face::right, block.GetSideTexture(), blockPosition, adjacentBlocks.right);

        TryToAddFace(blockId, Face::front, block.GetSideTexture(), blockPosition, adjacentBlocks.front);
        TryToAddFace(blockId, Face::back, block.GetSideTexture(), blockPosition, adjacentBlocks.back);
    }
}

void ChunkMeshBuilder::TryToAddFace(const BlockId& blockId, const std::vector<GLfloat>& blockFace, const std::vector<GLfloat>& textureCoords,
                                    const glm::ivec3& blockPosition, const glm::ivec3& blockFacing)
{
    if (ShouldMakeFace(blockId, blockFacing))
    {
        if(blockId == BlockId::Water)
            m_chunkMesh->AddWaterBlockFace(blockFace, textureCoords, m_chunk->GetLocation(), blockPosition);
        else
            m_chunkMesh->AddBlockFace(blockFace, textureCoords, m_chunk->GetLocation(), blockPosition);
    }
}

bool ChunkMeshBuilder::ShouldMakeFace(const BlockId& blockId, const glm::ivec3& blockFacing)
{
    const BlockId& blockFacingId = m_chunk->GetBlock(blockFacing.x, blockFacing.y, blockFacing.z);
    const Block& block = BlockDatabase::Get().GetBlockInfo(blockFacingId);
    
    if (block.IsTranslucent() != Transparency::Opaque)
    {
        if (blockId == blockFacingId && block.IsTranslucent() == Transparency::Full)
            return false;
        else
            return true;
    }
    else
        return false;
}