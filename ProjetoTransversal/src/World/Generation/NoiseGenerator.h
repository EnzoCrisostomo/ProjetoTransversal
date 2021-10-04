#pragma once
#include <array>
#include "Options/Options.h"
#include "FastNoiseLite.h"
struct VectorXZ;

namespace NoiseGenerator
{
	std::array<int, Options::chunkArea> GenerateNoise(VectorXZ chunkPos, int seed);
};

