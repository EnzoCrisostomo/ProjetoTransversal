#pragma once
#include <array>
#include "Options/Options.h"
#include "FastNoiseLite.h"
struct VectorXZ;

namespace NoiseGenerator
{
	void Configure(int seed, int octaves, double lacunarity, double persistance, double scale);
	std::array<double, Options::chunkArea> GenerateNoise(VectorXZ chunkPos);
};