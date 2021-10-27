#include "WorldGen.h"
#include "FastNoiseLite.h"
#include "NoiseGenerator.h"
#include <vector>

struct Biome
{
	Biome(const char* name, double altitude, double humidity, double temperature, BlockId block)
	{
		this->name = name;
		this->altitude = altitude;
		this->humidity = humidity;
		this->temperature = temperature;
		this->block = block;
	}

	bool operator == (const Biome& other)
	{
		return (this->altitude		== other.altitude &&
				this->humidity		== other.humidity &&
				this->temperature	== other.temperature);
	}

	const char* name;
	double altitude;
	double humidity;
	double temperature;
	BlockId block;
};

namespace WorldGen
{
	int octaves;
	double lacunarity;
	double persistance;
	double scale;
	int localSeed;
	FastNoiseLite heightNoise;

	BlockId GetBlockId(int x, int z);
	BlockId GetBiomeValue(int x, int z);

	std::array<ChunkData, Options::chunkArea> GenerateChunk(const int seed, const VectorXZ& chunkPos)
	{
		auto ChunkMap = std::array<ChunkData, Options::chunkArea>();
		localSeed = seed;
		heightNoise.SetSeed(localSeed);
		heightNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
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

				double simplexXZ = heightNoise.GetNoise(sampleX, sampleZ);
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
		return GetBiomeValue(x, z);
	}

	BlockId GetBiomeValue(int x, int z)
	{
		NoiseGenerator::Configure(localSeed >> 2, 4, 1.4, 0.2, 4);
		double altitude =		100 * NoiseGenerator::GenerateNoiseBlock(x, z);
		NoiseGenerator::Configure(localSeed << 4, 4, 1.4, 0.2, 4);
		double humidity =		100 * NoiseGenerator::GenerateNoiseBlock(x, z);
		NoiseGenerator::Configure(localSeed + 353344, 4, 1.4, 0.2, 4);
		double temperature =	100 * NoiseGenerator::GenerateNoiseBlock(x, z);

		BlockId block = BlockId::Air;
		double lowestDiff = INFINITY;

		std::vector<Biome> biomes;

		//altitude, humidity, temperature
		//biomes.emplace_back("ocean",			 -10,  50, temperature, BlockId::Water);
		biomes.emplace_back("beach",			 -10,  49, temperature, BlockId::Sand);
		biomes.emplace_back("plains",			   0,  48, temperature, BlockId::Grass);
		//biomes.emplace_back("desert",			 0, -50, temperature, BlockId::Lava);
		biomes.emplace_back("tundra",			 0,  10, -20, BlockId::SnowGrass);
		//biomes.emplace_back("hills",			 1,  0,  0, BlockId::Mushroom);
		//biomes.emplace_back("mountains",		 2,  0,  0, BlockId::Stone);
		//biomes.emplace_back("desertDunes",		 1, -2,  2, BlockId::Cactus);
		//biomes.emplace_back("forest",			 0,  1,  1, BlockId::DarkWood);
		//biomes.emplace_back("forestHills",		 1,  1,  1, BlockId::LightWood);
		//biomes.emplace_back("forestMountains",	 2,  1,  1, BlockId::PineWood);
		//biomes.emplace_back("taiga",			-1, -1, -2, BlockId::Leaf);
		//biomes.emplace_back("taigaForest",		-1,  0, -2, BlockId::LightLeaf);
		//biomes.emplace_back("tundraHills",		 1,  1, -2, BlockId::Glass);
		//biomes.emplace_back("tundraForestHills", 1,  0, -2, BlockId::Lava);

		for (auto& bioma : biomes)
		{
			double deltaA = pow(abs(bioma.altitude		- altitude), 8);
			double deltaH =	pow(abs(bioma.humidity		- humidity), 8);
			double deltaT = pow(abs(bioma.temperature	- temperature), 8);
			double totalDiff = deltaA + deltaH + deltaT;

			if (totalDiff < lowestDiff)
			{
				lowestDiff = totalDiff;
				block = bioma.block;
			}
		}
		return block;
	}
}