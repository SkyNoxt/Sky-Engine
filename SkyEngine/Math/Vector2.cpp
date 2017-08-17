
#include "Vector2.h"

template <class T>
Vector2<T>::Vector2(const T xVal, const T yVal)
	: x(xVal)
	, y(yVal)
{
}

template <class T>
Vector2<T>::Vector2(const T val[2])
	: x(val[0])
	, y(val[1])
{
}

template <class T>
Vector2<T>::Vector2(const T value)
	: x(value)
	, y(value)
{
}

template <class T>
Vector2<T>::Vector2()
	: x(0)
	, y(0)
{
}

template <class T>
T Vector2<T>::dot() const
{
	return x * x + y * y;
}

template <class T>
T Vector2<T>::length() const
{
	return sqrt(dot());
}

template <class T>
T Vector2<T>::dot(const Vector2<T>& vector) const
{
	return x * vector.x + y * vector.y;
}

template <class T>
T Vector2<T>::distance(const Vector2<T>& vector) const
{
	return (*this - vector).length();
}

template <class T>
Vector2<T> Vector2<T>::invert() const
{
	return Vector2<T>{ -x, -y };
}

template <class T>
Vector2<T> Vector2<T>::normalize() const
{
	T l = 1 / length();

	if(l)
		return Vector2<T>{ x * l, y * l };

	return Vector2<T>{ 0, 0 };
}

template <class T>
Vector2<T> Vector2<T>::middle(const Vector2<T>& vector) const
{
	return Vector2<T>{ (x + vector.x) * 0.5f, (y + vector.y) * 0.5f };
}

template <class T>
Vector2<T> Vector2<T>::minima(const Vector2<T>& aVec, const Vector2<T>& bVec)
{
	return Vector2<T>{ aVec.x < bVec.x ? aVec.x : bVec.x, aVec.y < bVec.y ? aVec.y : bVec.y };
}

template <class T>
Vector2<T> Vector2<T>::maxima(const Vector2<T>& aVec, const Vector2<T>& bVec)
{
	return Vector2<T>{ aVec.x > bVec.x ? aVec.x : bVec.x, aVec.y > bVec.y ? aVec.y : bVec.y };
}

template <class T>
Vector2<T> Vector2<T>::operator-() const
{
	return Vector2<T>{ -x, -y };
}

template <class T>
void Vector2<T>::operator=(const Vector2<T>& vector)
{
	x = vector.x;
	y = vector.y;
}

template <class T>
void Vector2<T>::operator+=(const Vector2<T>& vector)
{
	x += vector.x;
	y += vector.y;
}

template <class T>
void Vector2<T>::operator-=(const Vector2<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
}

template <class T>
void Vector2<T>::operator*=(const Vector2<T>& vector)
{
	x *= vector.x;
	y *= vector.y;
}

template <class T>
void Vector2<T>::operator+=(const T value)
{
	x += value;
	y += value;
}

template <class T>
void Vector2<T>::operator-=(const T value)
{
	x -= value;
	y -= value;
}

template <class T>
void Vector2<T>::operator*=(const T value)
{
	x *= value;
	y *= value;
}

template <class T>
T& Vector2<T>::operator[](int index)
{
	return vector[index];
}

template <class T>
bool Vector2<T>::operator==(const Vector2<T>& vector) const
{
	return x == vector.x && y == vector.y;
}

template <class T>
bool Vector2<T>::operator!=(const Vector2<T>& vector) const
{
	return x != vector.x || y != vector.y;
}

template <class T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& vector) const
{
	return Vector2<T>{ x + vector.x, y + vector.y };
}

template <class T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& vector) const
{
	return Vector2<T>{ x - vector.x, y - vector.y };
}

template <class T>
Vector2<T> Vector2<T>::operator*(const Vector2<T>& vector) const
{
	return Vector2<T>{ x * vector.x, y * vector.y };
}

template <class T>
Vector2<T> Vector2<T>::operator+(const T value) const
{
	return Vector2<T>{ x + value, y + value };
}

template <class T>
Vector2<T> Vector2<T>::operator-(const T value) const
{
	return Vector2<T>{ x - value, y - value };
}

template <class T>
Vector2<T> Vector2<T>::operator*(const T value) const
{
	return Vector2<T>{ x * value, y * value };
}

template <class T>
Vector2<T>::~Vector2()
{
}

template class Vector2<>;
