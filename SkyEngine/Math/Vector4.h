
#pragma once

#include <math.h>

template <class T>
class Vector4
{

public:

	union
	{
		struct
		{
			T x;
			T y;
			T z;
			T w;
		};
		T vector[4];
	};

	//Constructors
	Vector4<T>(const T xVal, const T yVal, const T zVal, const T wVal);
	Vector4<T>(const T val[4]);
	Vector4<T>(const T value);
	Vector4<T>();

	//Member functions
	T dot() const;
	T length() const;
	T dot(const Vector4<T>& vector) const;
	T distance(const Vector4<T>& vector) const;

	Vector4<T> invert() const;
	Vector4<T> normalize() const;
	Vector4<T> middle(const Vector4<T>& vector) const;

	//Unary operators
	Vector4<T> operator - ();

	void operator =  (const Vector4<T>& vector);
	void operator += (const Vector4<T>& vector);
	void operator -= (const Vector4<T>& vector);
	void operator *= (const Vector4<T>& vector);

	void operator += (const T value);
	void operator -= (const T value);
	void operator *= (const T value);

	//Subscript operator
	T& operator [] (const int index);

	//Binary operators
	bool operator == (const Vector4<T>& vector) const;
	bool operator != (const Vector4<T>& vector) const;

	Vector4<T> operator + (const Vector4<T>& vector) const;
	Vector4<T> operator - (const Vector4<T>& vector) const;
	Vector4<T> operator * (const Vector4<T>& vector) const;

	Vector4<T> operator + (const T value) const;
	Vector4<T> operator - (const T value) const;
	Vector4<T> operator * (const T value) const;

	//Destructor
	~Vector4();

private:

};
