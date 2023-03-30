
#include <cmath>

#include "Vector2.h"

template <typename T>
Vector2<T>::Vector2(const T x, const T y)
	: x(x)
	, y(y)
{
}

template <typename T>
Vector2<T>::Vector2(const T values[2])
	: x(values[0])
	, y(values[1])
{
}

template <typename T>
Vector2<T>::Vector2(const T value)
	: x(value)
	, y(value)
{
}

template <typename T>
template <typename S>
Vector2<T>::Vector2(const Vector2<S>& vector)
	: x(vector.x)
	, y(vector.y)
{
}

template <typename T>
T Vector2<T>::dot() const
{
	return x * x + y * y;
}

template <typename T>
T Vector2<T>::length() const
{
	return std::sqrt(dot());
}

template <typename T>
T Vector2<T>::dot(const Vector2& vector) const
{
	return x * vector.x + y * vector.y;
}

template <typename T>
T Vector2<T>::distance(const Vector2& vector) const
{
	return (*this - vector).length();
}

template <typename T>
Vector2<T> Vector2<T>::normalize() const
{
	T l = 1 / length();

	if(l)
		return { T(x * l), T(y * l) };

	return { 0, 0 };
}

template <typename T>
Vector2<T> Vector2<T>::middle(const Vector2& vector) const
{
	return { T((x + vector.x) * 0.5), T((y + vector.y) * 0.5) };
}

template <typename T>
Vector2<T> Vector2<T>::minima(const Vector2& a, const Vector2& b)
{
	return { b.x < a.x ? b.x : a.x, b.y < a.y ? b.y : a.y };
}

template <typename T>
Vector2<T> Vector2<T>::maxima(const Vector2& a, const Vector2& b)
{
	return { a.x < b.x ? b.x : a.x, a.y < b.y ? b.y : a.y };
}

template <typename T>
Vector2<T> Vector2<T>::operator-() const
{
	return { T(-x), T(-y) };
}

template <typename T>
T& Vector2<T>::operator[](const int index)
{
	return vector[index];
}

template <typename T>
Vector2<T>& Vector2<T>::operator=(const T value)
{
	x = y = value;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const T value)
{
	x += value;
	y += value;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const T value)
{
	x -= value;
	y -= value;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const T value)
{
	x *= value;
	y *= value;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator=(const Vector2& vector)
{
	x = vector.x;
	y = vector.y;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& vector)
{
	x += vector.x;
	y += vector.y;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const Vector2& vector)
{
	x *= vector.x;
	y *= vector.y;
	return *this;
}

template <typename T>
bool Vector2<T>::operator==(const Vector2& vector) const
{
	return x == vector.x && y == vector.y;
}

template <typename T>
bool Vector2<T>::operator!=(const Vector2& vector) const
{
	return x != vector.x || y != vector.y;
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const T value) const
{
	return { T(x + value), T(y + value) };
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const T value) const
{
	return { T(x - value), T(y - value) };
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const T value) const
{
	return { T(x * value), T(y * value) };
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2& vector) const
{
	return { T(x + vector.x), T(y + vector.y) };
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2& vector) const
{
	return { T(x - vector.x), T(y - vector.y) };
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const Vector2& vector) const
{
	return { T(x * vector.x), T(y * vector.y) };
}

// Inline heterogeneous opeartors

template <typename T, typename S>
Vector2<S> operator*(const Vector2<T>& vector, const S value)
{
	return { vector.x * value, vector.y * value };
}

// Explicit template instantiations

// Classes

template class Vector2<>;
template class Vector2<unsigned char>;

// Constructors

template Vector2<unsigned char>::Vector2(const Vector2<>& vector);

// Heterogeneous opeartors

template Vector2<> operator*(const Vector2<unsigned char>&, const float);
