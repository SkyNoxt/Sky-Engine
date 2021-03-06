﻿
#pragma once

#include "Vector3.h"
#include "Vector4.h"

template <class T = float>
class Matrix4
{

  public:
	union
	{
		struct
		{
			T xx;
			T xy;
			T xz;
			T xw;
			T yx;
			T yy;
			T yz;
			T yw;
			T zx;
			T zy;
			T zz;
			T zw;
			T wx;
			T wy;
			T wz;
			T ww;
		};
		struct
		{
			Vector4<T> x;
			Vector4<T> y;
			Vector4<T> z;
			Vector4<T> w;
		};
	};

	static const Matrix4<T> IDENTITY;

	//Constructors
	Matrix4<T>(T xxVal, T xyVal, T xzVal, T xwVal, T yxVal, T yyVal, T yzVal, T ywVal, T zxVal, T zyVal, T zzVal, T zwVal, T wxVal, T wyVal, T wzVal, T wwVal);
	Matrix4<T>(T matrix[16]);
	Matrix4<T>(T value);
	Matrix4<T>();

	Matrix4<T>(const Vector4<T>& xVec, const Vector4<T>& yVec, const Vector4<T>& zVec, const Vector4<T>& wVec);
	Matrix4<T>(const Vector4<T> vec[4]);

	Matrix4<T>(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up = { 0, 1, 0 });

	//Member functions
	T determinant() const;

	Matrix4<T> transpose() const;
	Matrix4<T> inverse() const;

	void translate(T x, T y, T z);
	void translate(const Vector3<T>& translation);

	void rotate(T angle, T x, T y, T z);
	void rotate(const Vector4<T>& rotation);

	void scale(T x, T y, T z);
	void scale(const Vector3<T>& scaling);

	//Unary operators
	Matrix4<T>& operator=(const Matrix4<T>& matrix);
	Matrix4<T>& operator*=(const Matrix4<T>& matrix);

	Matrix4<T>& operator*=(const T value);

	//Subsript operator
	Vector4<T>& operator[](const int index);

	//Binary operators
	bool operator==(const Matrix4<T>& matrix) const;
	bool operator!=(const Matrix4<T>& matrix) const;

	Matrix4<T> operator*(const Matrix4<T>& matrix) const;

	Matrix4<T> operator*(const T value) const;

	//Destructor
	~Matrix4() = default;

  private:
};

//Inline heterogeneous opeartors

template <class T>
Vector3<T>& operator*=(Vector3<T>& vector, const Matrix4<T>& matrix)
{
	return vector = vector * matrix;
}

template <class T>
Vector3<T> operator*(const Vector3<T>& vector, const Matrix4<T>& matrix)
{
	/*T w = 1 / (vector.x * matrix.xw + vector.y * matrix.yw + vector.z * matrix.zw + matrix.ww);

	return Vector3<T>(
		vector.x * matrix.xx + vector.y * matrix.yx + vector.z * matrix.zx + matrix.wx * w,
		vector.x * matrix.xy + vector.y * matrix.yy + vector.z * matrix.zy + matrix.wy * w,
		vector.x * matrix.xz + vector.y * matrix.yz + vector.z * matrix.zz + matrix.wz * w
	);*/

	return Vector3<T>{
		vector.x * matrix.xx + vector.y * matrix.yx + vector.z * matrix.zx,
		vector.x * matrix.xy + vector.y * matrix.yy + vector.z * matrix.zy,
		vector.x * matrix.xz + vector.y * matrix.yz + vector.z * matrix.zz
	};
}

template <class T>
Vector4<T>& operator*=(Vector4<T>& vector, const Matrix4<T>& matrix)
{
	return vector = vector * matrix;
}

template <class T>
Vector4<T> operator*(const Vector4<T>& vector, const Matrix4<T>& matrix)
{
	return Vector4<T>{
		vector.x * matrix.xx + vector.y * matrix.yx + vector.z * matrix.zx + vector.w * matrix.wx,
		vector.x * matrix.xy + vector.y * matrix.yy + vector.z * matrix.zy + vector.w * matrix.wy,
		vector.x * matrix.xz + vector.y * matrix.yz + vector.z * matrix.zz + vector.w * matrix.wz,
		vector.x * matrix.xw + vector.y * matrix.yw + vector.z * matrix.zw + vector.w * matrix.ww
	};
}
