
#pragma once

#include "Vector3.h"

template <class T = float>
class Matrix3
{

public:
	union
	{
		struct
		{
			T xx;
			T xy;
			T xz;
			T yx;
			T yy;
			T yz;
			T zx;
			T zy;
			T zz;
		};
		struct
		{
			Vector3<T> x;
			Vector3<T> y;
			Vector3<T> z;
		};
	};

	static const Matrix3<T> IDENTITY;

	//Constructors
	Matrix3<T>(T xxVal, T xyVal, T xzVal, T yxVal, T yyVal, T yzVal, T zxVal, T zyVal, T zzVal);
	Matrix3<T>(T matrix[9]);
	Matrix3<T>(T value);
	Matrix3<T>();

	Matrix3<T>(const Vector3<T>& xVec, const Vector3<T>& yVec, const Vector3<T>& zVec);
	Matrix3<T>(const Vector3<T> vec[3]);

	//Member functions
	T determinant() const;

	Matrix3<T> transpose() const;
	Matrix3<T> inverse() const;

	//Unary operators
	void operator=(const Matrix3<T>& matrix);
	void operator*=(const Matrix3<T>& matrix);

	void operator*=(const T value);

	//Subsript operator
	Vector3<T>& operator[](int index);

	//Binary operators
	bool operator==(const Matrix3<T>& matrix) const;
	bool operator!=(const Matrix3<T>& matrix) const;

	Matrix3<T> operator*(const Matrix3<T>& matrix) const;

	Matrix3<T> operator*(const T value) const;

	//Destructor
	~Matrix3();

private:
};

//Inline heterogeneous opeartors

template <class T>
void operator*=(Vector3<T>& vector, const Matrix3<T>& matrix)
{
	vector = vector * matrix;
}

template <class T>
Vector3<T> operator*(const Vector3<T>& vector, const Matrix3<T>& matrix)
{
	return Vector3<T>{
		vector.x * matrix.xx + vector.y * matrix.yx + vector.z * matrix.zx,
		vector.x * matrix.xy + vector.y * matrix.yy + vector.z * matrix.zy,
		vector.x * matrix.xz + vector.y * matrix.yz + vector.z * matrix.zz
	};
}
