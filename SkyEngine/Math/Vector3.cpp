
#include <cmath>

#include "Vector3.h"

template <class T>
Vector3<T>::Vector3(const T xVal, const T yVal, const T zVal)
	: x(xVal)
	, y(yVal)
	, z(zVal)
{
}

template <class T>
Vector3<T>::Vector3(const T val[3])
	: x(val[0])
	, y(val[1])
	, z(val[2])
{
}

template <class T>
Vector3<T>::Vector3(const T value)
	: x(value)
	, y(value)
	, z(value)
{
}

template <class T>
Vector3<T>::Vector3()
	: x(0)
	, y(0)
	, z(0)
{
}

template <class T>
T Vector3<T>::dot() const
{
	return x * x + y * y + z * z;
}

template <class T>
T Vector3<T>::length() const
{
	return sqrt(dot());
}

template <class T>
T Vector3<T>::dot(const Vector3<T>& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z;
}

template <class T>
T Vector3<T>::distance(const Vector3<T>& vector) const
{
	return (*this - vector).length();
}

template <class T>
Vector3<T> Vector3<T>::invert() const
{
	return Vector3<T>{ -x, -y, -z };
}

template <class T>
Vector3<T> Vector3<T>::normalize() const
{
	T l = 1 / length();

	if(l)
		return Vector3<T>{ x * l, y * l, z * l };

	return Vector3<T>{ 0, 0, 0 };
}

template <class T>
Vector3<T> Vector3<T>::middle(const Vector3<T>& vector) const
{
	return Vector3<T>{ (x + vector.x) * 0.5f, (y + vector.y) * 0.5f, (z + vector.z) * 0.5f };
}

template <class T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& vector) const
{
	return Vector3<T>{ y * vector.z - vector.y * z,
		z * vector.x - vector.z * x,
		x * vector.y - vector.x * y };
}

template <class T>
Vector3<T> Vector3<T>::minima(const Vector3<T>& aVec, const Vector3<T>& bVec)
{
	return Vector3<T>{ bVec.x < aVec.x ? bVec.x : aVec.x, bVec.y < aVec.y ? bVec.y : aVec.y, bVec.z < aVec.z ? bVec.z : aVec.z };
}

template <class T>
Vector3<T> Vector3<T>::maxima(const Vector3<T>& aVec, const Vector3<T>& bVec)
{
	return Vector3<T>{ aVec.x < bVec.x ? bVec.x : aVec.x, aVec.y < bVec.y ? bVec.y : aVec.y, aVec.z < bVec.z ? bVec.z : aVec.z };
}

template <class T>
Vector3<T> Vector3<T>::operator-() const
{
	return Vector3<T>{ -x, -y, -z };
}

template <class T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T>& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator+=(const T value)
{
	x += value;
	y += value;
	z += value;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator-=(const T value)
{
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator*=(const T value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

template <class T>
T& Vector3<T>::operator[](const int index)
{
	return vector[index];
}

template <class T>
bool Vector3<T>::operator==(const Vector3<T>& vector) const
{
	return x == vector.x && y == vector.y && z == vector.z;
}

template <class T>
bool Vector3<T>::operator!=(const Vector3<T>& vector) const
{
	return x != vector.x || y != vector.y || z != vector.z;
}

template <class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& vector) const
{
	return Vector3<T>{ x + vector.x, y + vector.y, z + vector.z };
}

template <class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& vector) const
{
	return Vector3<T>{ x - vector.x, y - vector.y, z - vector.z };
}

template <class T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& vector) const
{
	return Vector3<T>{ x * vector.x, y * vector.y, z * vector.z };
}

template <class T>
Vector3<T> Vector3<T>::operator+(const T value) const
{
	return Vector3<T>{ x + value, y + value, z + value };
}

template <class T>
Vector3<T> Vector3<T>::operator-(const T value) const
{
	return Vector3<T>{ x - value, y - value, z - value };
}

template <class T>
Vector3<T> Vector3<T>::operator*(const T value) const
{
	return Vector3<T>{ x * value, y * value, z * value };
}

template class Vector3<>;
template class Vector3<unsigned char>;
