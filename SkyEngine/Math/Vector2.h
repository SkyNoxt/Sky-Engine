
#pragma once

#include <math.h>

template <class T>
class Vector2
{

public:
	union
	{
		struct
		{
			T x;
			T y;
		};
		T vector[2];
	};

	//Constructors
	Vector2<T>(const T xVal, const T yVal);
	Vector2<T>(const T val[2]);
	Vector2<T>(const T value);
	Vector2<T>();

	//Member functions
	T dot() const;
	T length() const;
	T dot(const Vector2<T>& vector) const;
	T distance(const Vector2<T>& vector) const;

	Vector2<T> invert() const;
	Vector2<T> normalize() const;
	Vector2<T> middle(const Vector2<T>& vector) const;

	static Vector2<T> minima(const Vector2<T>& aVec, const Vector2<T>& bVec);
	static Vector2<T> maxima(const Vector2<T>& aVec, const Vector2<T>& bVec);

	//Unary operators
	Vector2<T> operator-() const;

	void operator=(const Vector2<T>& vector);
	void operator+=(const Vector2<T>& vector);
	void operator-=(const Vector2<T>& vector);
	void operator*=(const Vector2<T>& vector);

	void operator+=(const T value);
	void operator-=(const T value);
	void operator*=(const T value);

	//Subscript operator
	T& operator[](const int index);

	//Binary operators
	bool operator==(const Vector2<T>& vector) const;
	bool operator!=(const Vector2<T>& vector) const;

	Vector2<T> operator+(const Vector2<T>& vector) const;
	Vector2<T> operator-(const Vector2<T>& vector) const;
	Vector2<T> operator*(const Vector2<T>& vector) const;

	Vector2<T> operator+(const T value) const;
	Vector2<T> operator-(const T value) const;
	Vector2<T> operator*(const T value) const;

	//Destructor
	~Vector2();

private:
};

//Inline heterogeneous opeartors

template <class T>
Vector2<T> operator*(const T& value, const Vector2<T>& vector)
{
	return vector * value;
}
