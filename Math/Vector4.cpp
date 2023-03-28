
#include <cmath>

#include "Vector4.h"

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
template <typename S>
Vector4<T>::Vector4(const Vector4<S>& vector)
	: x(vector.x)
	, y(vector.y)
	, z(vector.z)
	, w(vector.w)
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
T Vector4<T>::dot(const Vector4<T>& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}

template <typename T>
T Vector4<T>::distance(const Vector4<T>& vector) const
{
	return (*this - vector).length();
}

template <typename T>
Vector4<T> Vector4<T>::invert() const
{
	return Vector4<T>{ -x, -y, -z, -w };
}

template <typename T>
Vector4<T> Vector4<T>::normalize() const
{
	T l = 1 / length();

	if(l)
		return Vector4<T>{ x * l, y * l, z * l, w * l };

	return Vector4<T>{ 0, 0, 0, 0 };
}

template <typename T>
Vector4<T> Vector4<T>::middle(const Vector4<T>& vector) const
{
	return Vector4<T>{ (x + vector.x) * 0.5f, (y + vector.y) * 0.5f, (z + vector.z) * 0.5f, (w + vector.w) * 0.5f };
}

template <typename T>
Vector4<T> Vector4<T>::minima(const Vector4<T>& a, const Vector4<T>& b)
{
	return Vector4<T>{ b.x < a.x ? b.x : a.x, b.y < a.y ? b.y : a.y, b.z < a.z ? b.z : a.z, b.w < a.w ? b.w : a.w };
}

template <typename T>
Vector4<T> Vector4<T>::maxima(const Vector4<T>& a, const Vector4<T>& b)
{
	return Vector4<T>{ a.x < b.x ? b.x : a.x, a.y < b.y ? b.y : a.y, a.z < b.z ? b.z : a.z, a.w < b.w ? b.w : a.w };
}

template <typename T>
Vector4<T> Vector4<T>::operator-() const
{
	return Vector4<T>{ -x, -y, -z, -w };
}

template <typename T>
T& Vector4<T>::operator[](const int index)
{
	return vector[index];
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
Vector4<T>& Vector4<T>::operator=(const Vector4<T>& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
	return *this;
}

template <typename T>
Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;
	return *this;
}

template <typename T>
bool Vector4<T>::operator==(const Vector4<T>& vector) const
{
	return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
}

template <typename T>
bool Vector4<T>::operator!=(const Vector4<T>& vector) const
{
	return x != vector.x || y != vector.y || z != vector.z || w != vector.w;
}

template <typename T>
Vector4<T> Vector4<T>::operator+(const T value) const
{
	return Vector4<T>{ x + value, y + value, z + value, w + value };
}

template <typename T>
Vector4<T> Vector4<T>::operator-(const T value) const
{
	return Vector4<T>{ x - value, y - value, z - value, w - value };
}

template <typename T>
Vector4<T> Vector4<T>::operator*(const T value) const
{
	return Vector4<T>{ x * value, y * value, z * value, w * value };
}

template <typename T>
Vector4<T> Vector4<T>::operator+(const Vector4<T>& vector) const
{
	return Vector4<T>{ x + vector.x, y + vector.y, z + vector.z, w + vector.w };
}

template <typename T>
Vector4<T> Vector4<T>::operator-(const Vector4<T>& vector) const
{
	return Vector4<T>{ x - vector.x, y - vector.y, z - vector.z, w - vector.w };
}

template <typename T>
Vector4<T> Vector4<T>::operator*(const Vector4<T>& vector) const
{
	return Vector4<T>{ x * vector.x, y * vector.y, z * vector.z, w * vector.w };
}

// Inline heterogeneous opeartors

template <typename T, typename S>
Vector4<T> operator*(const S value, const Vector4<T>& vector)
{
	return vector * value;
}

template <typename T, typename S>
Vector4<S> operator*(const Vector4<T>& vector, const S value)
{
	return Vector4<S>{ vector.x * value, vector.y * value, vector.z * value, vector.w * value };
}

// Explicit template instanciations

// Classes

template class Vector4<>;
template class Vector4<unsigned char>;

// Constructors

template Vector4<unsigned char>::Vector4(const Vector4<>& vector);

// Heterogeneous opeartors

template Vector4<> operator*(float, const Vector4<>&);
template Vector4<> operator*(const Vector4<unsigned char>&, const float);
