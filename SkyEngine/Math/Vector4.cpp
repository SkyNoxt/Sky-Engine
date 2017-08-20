
#include <cmath>

#include "Vector4.h"

template <class T>
Vector4<T>::Vector4(const T xVal, const T yVal, const T zVal, const T wVal)
	: x(xVal)
	, y(yVal)
	, z(zVal)
	, w(wVal)
{
}

template <class T>
Vector4<T>::Vector4(const T val[4])
	: x(val[0])
	, y(val[1])
	, z(val[2])
	, w(val[3])
{
}

template <class T>
Vector4<T>::Vector4(const T value)
	: x(value)
	, y(value)
	, z(value)
	, w(value)
{
}

template <class T>
Vector4<T>::Vector4()
	: x(0)
	, y(0)
	, z(0)
	, w(0)
{
}

template <class T>
T Vector4<T>::dot() const
{
	return x * x + y * y + z * z + w * w;
}

template <class T>
T Vector4<T>::length() const
{
	return sqrt(dot());
}

template <class T>
T Vector4<T>::dot(const Vector4<T>& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}

template <class T>
T Vector4<T>::distance(const Vector4<T>& vector) const
{
	return (*this - vector).length();
}

template <class T>
Vector4<T> Vector4<T>::invert() const
{
	return Vector4<T>{ -x, -y, -z, -w };
}

template <class T>
Vector4<T> Vector4<T>::normalize() const
{
	T l = 1 / length();

	if(l)
		return Vector4<T>{ x * l, y * l, z * l, w * l };

	return Vector4<T>{ 0, 0, 0, 0 };
}

template <class T>
Vector4<T> Vector4<T>::middle(const Vector4<T>& vector) const
{
	return Vector4<T>{ (x + vector.x) * 0.5f, (y + vector.y) * 0.5f, (z + vector.z) * 0.5f, (w + vector.w) * 0.5f };
}

template <class T>
Vector4<T> Vector4<T>::minima(const Vector4<T>& aVec, const Vector4<T>& bVec)
{
	return Vector4<T>{ aVec.x < bVec.x ? aVec.x : bVec.x, aVec.y < bVec.y ? aVec.y : bVec.y, aVec.z < bVec.z ? aVec.z : bVec.z, aVec.w < bVec.w ? aVec.w : bVec.w };
}

template <class T>
Vector4<T> Vector4<T>::maxima(const Vector4<T>& aVec, const Vector4<T>& bVec)
{
	return Vector4<T>{ aVec.x > bVec.x ? aVec.x : bVec.x, aVec.y > bVec.y ? aVec.y : bVec.y, aVec.z > bVec.z ? aVec.z : bVec.z, aVec.w > bVec.w ? aVec.w : bVec.w };
}

template <class T>
Vector4<T> Vector4<T>::operator-() const
{
	return Vector4<T>{ -x, -y, -z, -w };
}

template <class T>
Vector4<T>& Vector4<T>::operator=(const Vector4<T>& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;
	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator+=(const T value)
{
	x += value;
	y += value;
	z += value;
	w += value;
	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator-=(const T value)
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;
	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator*=(const T value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
	return *this;
}

template <class T>
T& Vector4<T>::operator[](const int index)
{
	return vector[index];
}

template <class T>
bool Vector4<T>::operator==(const Vector4<T>& vector) const
{
	return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
}

template <class T>
bool Vector4<T>::operator!=(const Vector4<T>& vector) const
{
	return x != vector.x || y != vector.y || z != vector.z || w != vector.w;
}

template <class T>
Vector4<T> Vector4<T>::operator+(const Vector4<T>& vector) const
{
	return Vector4<T>{ x + vector.x, y + vector.y, z + vector.z, w + vector.w };
}

template <class T>
Vector4<T> Vector4<T>::operator-(const Vector4<T>& vector) const
{
	return Vector4<T>{ x - vector.x, y - vector.y, z - vector.z, w - vector.w };
}

template <class T>
Vector4<T> Vector4<T>::operator*(const Vector4<T>& vector) const
{
	return Vector4<T>{ x * vector.x, y * vector.y, z * vector.z, w * vector.w };
}

template <class T>
Vector4<T> Vector4<T>::operator+(const T value) const
{
	return Vector4<T>{ x + value, y + value, z + value, w + value };
}

template <class T>
Vector4<T> Vector4<T>::operator-(const T value) const
{
	return Vector4<T>{ x - value, y - value, z - value, w - value };
}

template <class T>
Vector4<T> Vector4<T>::operator*(const T value) const
{
	return Vector4<T>{ x * value, y * value, z * value, w * value };
}

template class Vector4<>;
