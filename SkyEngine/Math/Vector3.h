
#pragma once

#include <math.h>

template <class T = float>
class Vector3
{

public:
	union
	{
		struct
		{
			T x;
			T y;
			T z;
		};
		T vector[3];
	};

	//Constructors
	Vector3<T>(const T xVal, const T yVal, const T zVal);
	Vector3<T>(const T val[3]);
	Vector3<T>(const T value);
	Vector3<T>();

	//Member functions
	T dot() const;
	T length() const;
	T dot(const Vector3<T>& vector) const;
	T distance(const Vector3<T>& vector) const;

	Vector3<T> invert() const;
	Vector3<T> normalize() const;
	Vector3<T> middle(const Vector3<T>& vector) const;
	Vector3<T> cross(const Vector3<T>& vector) const;

	Vector3<T> reflect(const Vector3<T>& normal) const;
	Vector3<T> refract(const Vector3<T>& normal, float index) const;

	static Vector3<T> minima(const Vector3<T>& aVec, const Vector3<T>& bVec);
	static Vector3<T> maxima(const Vector3<T>& aVec, const Vector3<T>& bVec);

	//Unary operators
	Vector3<T> operator-() const;

	void operator=(const Vector3<T>& vector);
	void operator+=(const Vector3<T>& vector);
	void operator-=(const Vector3<T>& vector);
	void operator*=(const Vector3<T>& vector);

	void operator+=(const T value);
	void operator-=(const T value);
	void operator*=(const T value);

	//Subscript operator
	T& operator[](const int index);

	//Binary operators
	bool operator==(const Vector3<T>& vector) const;
	bool operator!=(const Vector3<T>& vector) const;

	Vector3<T> operator+(const Vector3<T>& vector) const;
	Vector3<T> operator-(const Vector3<T>& vector) const;
	Vector3<T> operator*(const Vector3<T>& vector) const;

	Vector3<T> operator+(const T value) const;
	Vector3<T> operator-(const T value) const;
	Vector3<T> operator*(const T value) const;

	//Destructor
	~Vector3();

private:
};

//Inline heterogeneous opeartors

template <class T>
Vector3<T> operator*(const T& value, const Vector3<T>& vector)
{
	return vector * value;
}
