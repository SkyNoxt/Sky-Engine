
#include <cmath>

#include "Vector3.h"

template <typename T>
Vector3<T>::Vector3(const T x, const T y, const T z)
	: x(x)
	, y(y)
	, z(z)
{
}

template <typename T>
Vector3<T>::Vector3(const T values[3])
	: x(values[0])
	, y(values[1])
	, z(values[2])
{
}

template <typename T>
Vector3<T>::Vector3(const T value)
	: x(value)
	, y(value)
	, z(value)
{
}

template <typename T>
template <typename S>
Vector3<T>::Vector3(const Vector3<S>& vector)
	: x(vector.x)
	, y(vector.y)
	, z(vector.z)
{
}

template <typename T>
T Vector3<T>::dot() const
{
	return x * x + y * y + z * z;
}

template <typename T>
T Vector3<T>::length() const
{
	return std::sqrt(dot());
}

template <typename T>
T Vector3<T>::dot(const Vector3<T>& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z;
}

template <typename T>
T Vector3<T>::distance(const Vector3<T>& vector) const
{
	return (*this - vector).length();
}

template <typename T>
Vector3<T> Vector3<T>::normalize() const
{
	T l = 1 / length();

	if(l)
		return { x * l, y * l, z * l };

	return { 0, 0, 0 };
}

template <typename T>
Vector3<T> Vector3<T>::middle(const Vector3<T>& vector) const
{
	return { (x + vector.x) * 0.5, (y + vector.y) * 0.5, (z + vector.z) * 0.5 };
}

template <typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& vector) const
{
	return Vector3<T>{ y * vector.z - vector.y * z,
					   z * vector.x - vector.z * x,
					   x * vector.y - vector.x * y };
}

template <typename T>
Vector3<T> Vector3<T>::minima(const Vector3<T>& a, const Vector3<T>& b)
{
	return { b.x < a.x ? b.x : a.x, b.y < a.y ? b.y : a.y, b.z < a.z ? b.z : a.z };
}

template <typename T>
Vector3<T> Vector3<T>::maxima(const Vector3<T>& a, const Vector3<T>& b)
{
	return { a.x < b.x ? b.x : a.x, a.y < b.y ? b.y : a.y, a.z < b.z ? b.z : a.z };
}

template <typename T>
Vector3<T> Vector3<T>::operator-() const
{
	return { -x, -y, -z };
}

template <typename T>
T& Vector3<T>::operator[](const int index)
{
	return vector[index];
}

template <typename T>
Vector3<T>& Vector3<T>::operator=(const T value)
{
	x = y = z = value;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator+=(const T value)
{
	x += value;
	y += value;
	z += value;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator-=(const T value)
{
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const T value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T>& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	return *this;
}

template <typename T>
bool Vector3<T>::operator==(const Vector3<T>& vector) const
{
	return x == vector.x && y == vector.y && z == vector.z;
}

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T>& vector) const
{
	return x != vector.x || y != vector.y || z != vector.z;
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const T value) const
{
	return { x + value, y + value, z + value };
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const T value) const
{
	return { x - value, y - value, z - value };
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const T value) const
{
	return { x * value, y * value, z * value };
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& vector) const
{
	return { x + vector.x, y + vector.y, z + vector.z };
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& vector) const
{
	return { x - vector.x, y - vector.y, z - vector.z };
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& vector) const
{
	return { x * vector.x, y * vector.y, z * vector.z };
}

// Inline heterogeneous opeartors

template <typename T, typename S>
Vector3<S> operator*(const Vector3<T>& vector, const S value)
{
	return { vector.x * value, vector.y * value, vector.z * value };
}

// Explicit template instantiations

// Classes

template class Vector3<>;
template class Vector3<unsigned char>;

// Constructors

template Vector3<unsigned char>::Vector3(const Vector3<>& vector);

// Heterogeneous opeartors

template Vector3<> operator*(const Vector3<unsigned char>&, const float);
