#include "VectorXZ.h"
#include <iostream>

VectorXZ::VectorXZ(int x, int z)
{
    this->x = x;
    this->z = z;
}

void VectorXZ::Print() const
{
    std::cout << "vecXZ: x[" << x << "], z[" << z << "]\n";
}

bool VectorXZ::operator==(const VectorXZ& other) const
{
	return (this->x == other.x && this->z == other.z);
}

bool VectorXZ::operator!=(const VectorXZ& other) const
{
    return (this->x != other.x || this->z != other.z);
}

void VectorXZ::operator+=(const VectorXZ& other)
{
    this->x += other.x;
    this->z += other.z;
}

void VectorXZ::operator-=(const VectorXZ& other)
{
    this->x -= other.x;
    this->z -= other.z;
}

VectorXZ VectorXZ::operator+(const VectorXZ& other) const
{
    return VectorXZ(this->x + other.x, this->z + other.z);
}

VectorXZ VectorXZ::operator-(const VectorXZ& other) const
{
    return VectorXZ(this->x - other.x, this->z - other.z);
}
