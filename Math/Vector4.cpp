
#include <cmath>

#include "Vector4.h"

using Sky::Math::Vector4;

template <typename T>
Vector4<T>::Vector4(const T x, const T y, const T z, const T w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
{
}

template <typename T>
Vector4<T>::Vector4(const T values[4])
	: x(values[0])
	, y(values[1])
	, z(values[2])
	, w(values[3])
{
}

template <typename T>
Vector4<T>::Vector4(const T value)
	: x(value)
	, y(value)
	, z(value)
	, w(value)
{
}

template <typename T>
T Vector4<T>::dot() const
{
	return x * x + y * y + z * z + w * w;
}

template <typename T>
T Vector4<T>::length() const
{
	return std::sqrt(dot());
}

template <typename T>
T Vector4<T>::dot(const Vector4& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}

template <typename T>
T Vector4<T>::distance(const Vector4& vector) const
{
	return (*this - vector).length();
}

template <typename T>
Vector4<T> Vector4<T>::normalize() const
{
	T l = 1 / length();

	if(l)
		return { T(x * l), T(y * l), T(z * l), T(w * l) };

	return { 0, 0, 0, 0 };
}

template <typename T>
Vector4<T> Vector4<T>::middle(const Vector4& vector) const
{
	return { T((x + vector.x) * 0.5), T((y + vector.y) * 0.5), T((z + vector.z) * 0.5), T((w + vector.w) * 0.5) };
}

template <typename T>
Vector4<T> Vector4<T>::minima(const Vector4& a, const Vector4& b)
{
	return { b.x < a.x ? b.x : a.x, b.y < a.y ? b.y : a.y, b.z < a.z ? b.z : a.z, b.w < a.w ? b.w : a.w };
}

template <typename T>
Vector4<T> Vector4<T>::maxima(const Vector4& a, const Vector4& b)
{
	return { a.x < b.x ? b.x : a.x, a.y < b.y ? b.y : a.y, a.z < b.z ? b.z : a.z, a.w < b.w ? b.w : a.w };
}

template <typename T>
Vector4<T> Vector4<T>::operator-() const
{
	return { T(-x), T(-y), T(-z), T(-w) };
}

template <typename T>
T& Vector4<T>::operator[](const int index)
{
	return vector[index];
}

template <typename T>
bool Vector4<T>::operator==(const Vector4& vector) const
{
	return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
}

template <typename T>
bool Vector4<T>::operator!=(const Vector4& vector) const
{
	return x != vector.x || y != vector.y || z != vector.z || w != vector.w;
}

template <typename T>
Vector4<T> Vector4<T>::operator+(const T value) const
{
	return { T(x + value), T(y + value), T(z + value), T(w + value) };
}

template <typename T>
Vector4<T> Vector4<T>::operator-(const T value) const
{
	return { T(x - value), T(y - value), T(z - value), T(w - value) };
}

template <typename T>
Vector4<T> Vector4<T>::operator*(const T value) const
{
	return { T(x * value), T(y * value), T(z * value), T(w * value) };
}

template <typename T>
Vector4<T> Vector4<T>::operator/(const T value) const
{
	return { T(x / value), T(y / value), T(z / value), T(w / value) };
}

template <typename T>
Vector4<T> Vector4<T>::operator+(const Vector4& vector) const
{
	return { T(x + vector.x), T(y + vector.y), T(z + vector.z), T(w + vector.w) };
}

template <typename T>
Vector4<T> Vector4<T>::operator-(const Vector4& vector) const
{
	return { T(x - vector.x), T(y - vector.y), T(z - vector.z), T(w - vector.w) };
}

template <typename T>
Vector4<T> Vector4<T>::operator*(const Vector4& vector) const
{
	return { T(x * vector.x), T(y * vector.y), T(z * vector.z), T(w * vector.w) };
}

template <typename T>
Vector4<T> Vector4<T>::operator/(const Vector4& vector) const
{
	return { T(x / vector.x), T(y / vector.y), T(z / vector.z), T(w / vector.w) };
}

template <typename T>
Vector4<T>& Vector4<T>::operator=(const T value)
{
	x = y = z = w = value;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator+=(const T value)
{
	x += value;
	y += value;
	z += value;
	w += value;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator-=(const T value)
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator*=(const T value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator/=(const T value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator=(const Vector4& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator+=(const Vector4& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator-=(const Vector4& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator*=(const Vector4& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator/=(const Vector4& vector)
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	w /= vector.w;
	return *this;
}

template class Vector4<>;
template class Vector4<unsigned char>;
