#pragma once
#include "World/Block/Block.h"
#include "Math/Vectors.h"
#include "Options/Options.h"
#include <array>

struct ChunkData
{
	BlockId blockId;
	int height;
};

namespace WorldGen
{
	std::array<ChunkData, Options::chunkArea> GenerateChunk(const int seed, const VectorXZ& chunkPos);
}