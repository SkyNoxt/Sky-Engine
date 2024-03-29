﻿
#include <cmath>
#include <numbers>

#include "Matrix4.h"

using Sky::Math::Vector2;
using Sky::Math::Vector3;
using Sky::Math::Vector4;

using Sky::Math::Matrix4;

template <typename T>
const Matrix4<T> Matrix4<T>::IDENTITY = { 1, 0, 0, 0,
										  0, 1, 0, 0,
										  0, 0, 1, 0,
										  0, 0, 0, 1 };

template <typename T>
Matrix4<T>::Matrix4(T xx, T xy, T xz, T xw, T yx, T yy, T yz, T yw, T zx, T zy, T zz, T zw, T wx, T wy, T wz, T ww)
	: xx(xx)
	, xy(xy)
	, xz(xz)
	, xw(xw)
	, yx(yx)
	, yy(yy)
	, yz(yz)
	, yw(yw)
	, zx(zx)
	, zy(zy)
	, zz(zz)
	, zw(zw)
	, wx(wx)
	, wy(wy)
	, wz(wz)
	, ww(ww)
{
}

template <typename T>
Matrix4<T>::Matrix4(T matrix[16])
	: xx(matrix[0])
	, xy(matrix[1])
	, xz(matrix[2])
	, xw(matrix[3])
	, yx(matrix[4])
	, yy(matrix[5])
	, yz(matrix[6])
	, yw(matrix[7])
	, zx(matrix[8])
	, zy(matrix[9])
	, zz(matrix[10])
	, zw(matrix[11])
	, wx(matrix[12])
	, wy(matrix[13])
	, wz(matrix[14])
	, ww(matrix[15])
{
}

template <typename T>
Matrix4<T>::Matrix4(T value)
	: xx(value)
	, xy(value)
	, xz(value)
	, xw(value)
	, yx(value)
	, yy(value)
	, yz(value)
	, yw(value)
	, zx(value)
	, zy(value)
	, zz(value)
	, zw(value)
	, wx(value)
	, wy(value)
	, wz(value)
	, ww(value)
{
}

template <typename T>
Matrix4<T>::Matrix4()
{
	*this = IDENTITY;
}

template <typename T>
Matrix4<T>::Matrix4(const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
{
}

template <typename T>
Matrix4<T>::Matrix4(const Vector4<T> vector[4])
	: x(vector[0])
	, y(vector[1])
	, z(vector[2])
	, w(vector[3])
{
}

template <typename T>
Matrix4<T>::Matrix4(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up)
{
	Vector3<T> zVec = (eye - center).normalize();
	Vector3<T> xVec = up.normalize().cross(zVec);
	Vector3<T> yVec = zVec.cross(xVec);

	x = { xVec.x, xVec.y, xVec.z, 0 };
	y = { yVec.x, yVec.y, yVec.z, 0 };
	z = { zVec.x, zVec.y, zVec.z, 0 };
	w = { eye.x, eye.y, eye.z, 1 };
}

template <typename T>
T Matrix4<T>::determinant() const
{
	return xw * yz * zy * wx - xz * yw * zy * wx - xw * yy * zz * wx + xy * yw * zz * wx + xz * yy * zw * wx - xy * yz * zw * wx - xw * yz * zx * wy + xz * yw * zx * wy + xw * yx * zz * wy - xx * yw * zz * wy - xz * yx * zw * wy + xx * yz * zw * wy + xw * yy * zx * wz - xy * yw * zx * wz - xw * yx * zy * wz + xx * yw * zy * wz + xy * yx * zw * wz - xx * yy * zw * wz - xz * yy * zx * ww + xy * yz * zx * ww + xz * yx * zy * ww - xx * yz * zy * ww - xy * yx * zz * ww + xx * yy * zz * ww;
}

template <typename T>
Matrix4<T> Matrix4<T>::transpose() const
{
	return Matrix4<T>{
		xx, yx, zx, wx,
		xy, yy, zy, wy,
		xz, yz, zz, wz,
		xw, yw, zw, ww
	};
}

template <typename T>
Matrix4<T> Matrix4<T>::inverse() const
{
	Matrix4<T> inverse = Matrix4<T>{
		yy * zz * ww - yy * zw * wz - zy * yz * ww + zy * yw * wz + wy * yz * zw - wy * yw * zz,
		-xy * zz * ww + xy * zw * wz + zy * xz * ww - zy * xw * wz - wy * xz * zw + wy * xw * zz,
		xy * yz * ww - xy * yw * wz - yy * xz * ww + yy * xw * wz + wy * xz * yw - wy * xw * yz,
		-xy * yz * zw + xy * yw * zz + yy * xz * zw - yy * xw * zz - zy * xz * yw + zy * xw * yz,

		-yx * zz * ww + yx * zw * wz + zx * yz * ww - zx * yw * wz - wx * yz * zw + wx * yw * zz,
		xx * zz * ww - xx * zw * wz - zx * xz * ww + zx * xw * wz + wx * xz * zw - wx * xw * zz,
		-xx * yz * ww + xx * yw * wz + yx * xz * ww - yx * xw * wz - wx * xz * yw + wx * xw * yz,
		xx * yz * zw - xx * yw * zz - yx * xz * zw + yx * xw * zz + zx * xz * yw - zx * xw * yz,

		yx * zy * ww - yx * zw * wy - zx * yy * ww + zx * yw * wy + wx * yy * zw - wx * yw * zy,
		-xx * zy * ww + xx * zw * wy + zx * xy * ww - zx * xw * wy - wx * xy * zw + wx * xw * zy,
		xx * yy * ww - xx * yw * wy - yx * xy * ww + yx * xw * wy + wx * xy * yw - wx * xw * yy,
		-xx * yy * zw + xx * yw * zy + yx * xy * zw - yx * xw * zy - zx * xy * yw + zx * xw * yy,

		-yx * zy * wz + yx * zz * wy + zx * yy * wz - zx * yz * wy - wx * yy * zz + wx * yz * zy,
		xx * zy * wz - xx * zz * wy - zx * xy * wz + zx * xz * wy + wx * xy * zz - wx * xz * zy,
		-xx * yy * wz + xx * yz * wy + yx * xy * wz - yx * xz * wy - wx * xy * yz + wx * xz * yy,
		xx * yy * zz - xx * yz * zy - yx * xy * zz + yx * xz * zy + zx * xy * yz - zx * xz * yy
	};

	return inverse * (1 / (xx * inverse.xx + xy * inverse.yx + xz * inverse.zx + xw * inverse.wx));
}

template <typename T>
void Matrix4<T>::translate(T x, T y, T z)
{
	wx += xx * x + yx * y + zx * z;
	wy += xy * x + yy * y + zy * z;
	wz += xz * x + yz * y + zz * z;
	ww += xw * x + yw * y + zw * z;
}

template <typename T>
void Matrix4<T>::translate(const Vector3<T>& translation)
{
	translate(translation.x, translation.y, translation.z);
}

template <typename T>
void Matrix4<T>::rotate(T angle, T x, T y, T z)
{
	T s = std::sin(angle * std::numbers::pi / 180),
	  c = std::cos(angle * std::numbers::pi / 180),
	  xx = x * x,
	  yy = y * y,
	  zz = z * z,
	  xy = x * y,
	  yz = y * z,
	  zx = z * x,
	  xs = x * s,
	  ys = y * s,
	  zs = z * s,
	  c1 = 1 - c;

	Matrix4<T> rotationMatrix = Matrix4<T>{ (c1 * xx) + c, (c1 * xy) + zs, (c1 * zx) - ys, 0,
											(c1 * xy) - zs, (c1 * yy) + c, (c1 * yz) + xs, 0,
											(c1 * zx) + ys, (c1 * yz) - xs, (c1 * zz) + c, 0,
											0, 0, 0, 1 };

	*this *= rotationMatrix;
}

template <typename T>
void Matrix4<T>::rotate(const Vector4<T>& rotation)
{
	rotate(rotation.w, rotation.x, rotation.y, rotation.z);
}

template <typename T>
void Matrix4<T>::scale(T x, T y, T z)
{
	xx *= x;
	xy *= x;
	xz *= x;
	xw *= x;

	yx *= y;
	yy *= y;
	yz *= y;
	yw *= y;

	zx *= z;
	zy *= z;
	zz *= z;
	zw *= z;
}

template <typename T>
void Matrix4<T>::scale(const Vector3<T>& scaling)
{
	scale(scaling.x, scaling.y, scaling.z);
}

template <typename T>
Vector4<T>& Matrix4<T>::operator[](const int index)
{
	return *(((Vector4<T>*)this) + index);
}

template <typename T>
bool Matrix4<T>::operator==(const Matrix4<T>& matrix) const
{
	return x == matrix.x && y == matrix.y && z == matrix.z && w == matrix.w;
}

template <typename T>
bool Matrix4<T>::operator!=(const Matrix4<T>& matrix) const
{
	return x != matrix.x || y != matrix.y || z != matrix.z || w != matrix.w;
}

template <typename T>
Matrix4<T> Matrix4<T>::operator*(const T value) const
{
	return Matrix4<T>{ x * value, y * value, z * value, w * value };
}

template <typename T>
Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& matrix) const
{
	return Matrix4<T>{
		xx * matrix.xx + yx * matrix.xy + zx * matrix.xz + wx * matrix.xw,
		xy * matrix.xx + yy * matrix.xy + zy * matrix.xz + wy * matrix.xw,
		xz * matrix.xx + yz * matrix.xy + zz * matrix.xz + wz * matrix.xw,
		xw * matrix.xx + yw * matrix.xy + zw * matrix.xz + ww * matrix.xw,

		xx * matrix.yx + yx * matrix.yy + zx * matrix.yz + wx * matrix.yw,
		xy * matrix.yx + yy * matrix.yy + zy * matrix.yz + wy * matrix.yw,
		xz * matrix.yx + yz * matrix.yy + zz * matrix.yz + wz * matrix.yw,
		xw * matrix.yx + yw * matrix.yy + zw * matrix.yz + ww * matrix.yw,

		xx * matrix.zx + yx * matrix.zy + zx * matrix.zz + wx * matrix.zw,
		xy * matrix.zx + yy * matrix.zy + zy * matrix.zz + wy * matrix.zw,
		xz * matrix.zx + yz * matrix.zy + zz * matrix.zz + wz * matrix.zw,
		xw * matrix.zx + yw * matrix.zy + zw * matrix.zz + ww * matrix.zw,

		xx * matrix.wx + yx * matrix.wy + zx * matrix.wz + wx * matrix.ww,
		xy * matrix.wx + yy * matrix.wy + zy * matrix.wz + wy * matrix.ww,
		xz * matrix.wx + yz * matrix.wy + zz * matrix.wz + wz * matrix.ww,
		xw * matrix.wx + yw * matrix.wy + zw * matrix.wz + ww * matrix.ww
	};
}

template <typename T>
Matrix4<T>& Matrix4<T>::operator=(const T value)
{
	x = value;
	y = value;
	z = value;
	w = value;
	return *this;
}

template <typename T>
Matrix4<T>& Matrix4<T>::operator*=(const T value)
{
	return *this = *this * value;
}

template <typename T>
Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& matrix)
{
	x = matrix.x;
	y = matrix.y;
	z = matrix.z;
	w = matrix.w;
	return *this;
}

template <typename T>
Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& matrix)
{
	return *this = *this * matrix;
}

template <typename T>
Vector2<T> Matrix4<T>::operator*(const Vector2<T>& vector) const
{
	return Vector2<T>{
		xx * vector.x + yx * vector.y,
		xy * vector.x + yy * vector.y
	};
}

template <typename T>
Vector3<T> Matrix4<T>::operator*(const Vector3<T>& vector) const
{
	return Vector3<T>{
		xx * vector.x + yx * vector.y + zx * vector.z,
		xy * vector.x + yy * vector.y + zy * vector.z,
		xz * vector.x + yz * vector.y + zz * vector.z
	};
}

template <typename T>
Vector4<T> Matrix4<T>::operator*(const Vector4<T>& vector) const
{
	return Vector4<T>{
		xx * vector.x + yx * vector.y + zx * vector.z + wx * vector.w,
		xy * vector.x + yy * vector.y + zy * vector.z + wy * vector.w,
		xz * vector.x + yz * vector.y + zz * vector.z + wz * vector.w,
		xw * vector.x + yw * vector.y + zw * vector.z + ww * vector.w
	};
}

template class Sky::Math::Matrix4<>;
