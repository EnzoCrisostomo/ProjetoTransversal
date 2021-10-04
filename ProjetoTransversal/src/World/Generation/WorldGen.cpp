#include "WorldGen.h"
#include "FastNoiseLite.h"

namespace WorldGen
{
	int octaves;
	double lacunarity;
	double persistance;
	double scale;
	FastNoiseLite noise;

	BlockId GetBlockId(int x, int z);
	double GetBiomeValue(int x, int z);

	std::array<ChunkData, Options::chunkArea> GenerateChunk(const int seed, const VectorXZ& chunkPos)
	{
		auto ChunkMap = std::array<ChunkData, Options::chunkArea>();
		noise.SetSeed(seed);
		noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		octaves = 8;
		lacunarity = 1.8;
		persistance = 0.3;
		scale = 2.0;

		//loops para iterar sobre todas as posicoes
		for (int z = 0; z < Options::chunkSize; z++)
		for (int x = 0; x < Options::chunkSize; x++)
		{
			long long blockPosX = static_cast<long long>(chunkPos.x) * Options::chunkSize + x;
			long long blockPosZ = static_cast<long long>(chunkPos.z) * Options::chunkSize + z;
			double amplitude = 1;
			double frequency = 1;
			double noiseHeigth = 0;
			//roda na mesma posicao [x, z] n = octaves vezes para maior variedade
			for (int i = 0; i < octaves; i++)
			{
				//a frequencia altera os pontos de amostra do ruido
				double sampleX = blockPosX / scale * frequency;
				double sampleZ = blockPosZ / scale * frequency;

				double simplexXZ = noise.GetNoise(sampleX, sampleZ);
				simplexXZ += 1;
				simplexXZ /= 2;
				//a amplitude altera o quanto essa oitava altera no valor final
				noiseHeigth += simplexXZ * amplitude;

				amplitude *= persistance;
				frequency *= lacunarity;
			}
			noiseHeigth *= 40;
			noiseHeigth += 40;
			size_t mapIndex = static_cast<size_t>(x) * Options::chunkSize + z;
			BlockId block = GetBlockId(blockPosX, blockPosZ);
			ChunkMap.at(mapIndex) = ChunkData{ block, static_cast<int>(noiseHeigth) };
		}
		return ChunkMap;
	}

	BlockId GetBlockId(int x, int z)
	{
		return BlockId::Grass;
		//double biome = GetBiomeValue(x, z);
		//if (biome > 0.7)
		//	return BlockId::Stone;
		//if (biome > 0.5)
		//	return BlockId::Sand;
		//if (biome > 0.3)
		//	return BlockId::Grass;
		//
		////Menor que 0.3
		//return BlockId::SnowGrass;
	}

	double GetBiomeValue(int x, int z)
	{
		double value = noise.GetNoise(x / 20.0, z / 20.0);
		return (value + 1) / 2;
	}
}