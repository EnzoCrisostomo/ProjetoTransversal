#pragma once
#include<functional>

struct VectorXZ
{
	int x, z;

	VectorXZ() = default;
	VectorXZ(int x, int z);

	void Print() const;

	bool operator==(const VectorXZ& other) const;
	bool operator!=(const VectorXZ& other) const;
	void operator+=(const VectorXZ& other);
	void operator-=(const VectorXZ& other);
	VectorXZ operator+(const VectorXZ& other) const;
	VectorXZ operator-(const VectorXZ& other) const;
};

//criar especializacao de template em std::hash
//para minha struct VectorXZ
namespace std
{
	template<>
	struct hash<VectorXZ>
	{
		size_t operator()(const VectorXZ& vec) const
		{
			return hash<int>()(vec.x) ^ (hash<int>()(vec.z) << 1);
		}
	};
}
