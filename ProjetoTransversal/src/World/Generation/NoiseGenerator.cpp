#include "NoiseGenerator.h"
#include "Math/VectorXZ.h"

namespace NoiseGenerator
{
	int m_seed;
	int m_octaves = 8;
	double m_lacunarity = 1.8;
	double m_persistance = 0.3;
	double m_scale = 2.0;
	FastNoiseLite m_noise;

	std::array<int, Options::chunkArea> NoiseGenerator::GenerateNoise(VectorXZ chunkPos, int seed)
	{
		std::array<int, Options::chunkArea> noiseMap = std::array<int, Options::chunkArea>();

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
			for (int i = 0; i < m_octaves; i++)
			{
				//a frequencia altera os pontos de amostra do ruido
				double sampleX = blockPosX / m_scale * frequency;
				double sampleZ = blockPosZ / m_scale * frequency;

				double simplexXZ = m_noise.GetNoise(sampleX, sampleZ);
				simplexXZ += 1;
				simplexXZ /= 2;
				//a amplitude altera o quanto essa oitava altera no valor final
				noiseHeigth += simplexXZ * amplitude;

				amplitude *= m_persistance;
				frequency *= m_lacunarity;
			}
			noiseHeigth *= 40;
			noiseHeigth += 40;
			size_t mapIndex = static_cast<size_t>(x) * Options::chunkSize + z;
			noiseMap.at(mapIndex) = static_cast<int>(noiseHeigth);
		}

		return noiseMap;
	}
}

