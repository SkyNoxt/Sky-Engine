
#include "Matrix3.h"

using Sky::Math::Vector2;
using Sky::Math::Vector3;

using Sky::Math::Matrix3;

template <class T>
const Matrix3<T> Matrix3<T>::IDENTITY = { 1, 0, 0,
										  0, 1, 0,
										  0, 0, 1 };

template <class T>
Matrix3<T>::Matrix3(T xx, T xy, T xz, T yx, T yy, T yz, T zx, T zy, T zz)
	: xx(xx)
	, xy(xy)
	, xz(xz)
	, yx(yx)
	, yy(yy)
	, yz(yz)
	, zx(zx)
	, zy(zy)
	, zz(zz)
{
}

template <class T>
Matrix3<T>::Matrix3(T matrix[9])
	: xx(matrix[0])
	, xy(matrix[1])
	, xz(matrix[2])
	, yx(matrix[3])
	, yy(matrix[4])
	, yz(matrix[5])
	, zx(matrix[6])
	, zy(matrix[7])
	, zz(matrix[8])
{
}

template <class T>
Matrix3<T>::Matrix3(T value)
	: xx(value)
	, xy(value)
	, xz(value)
	, yx(value)
	, yy(value)
	, yz(value)
	, zx(value)
	, zy(value)
	, zz(value)
{
}

template <class T>
Matrix3<T>::Matrix3()
{
	*this = IDENTITY;
}

template <class T>
Matrix3<T>::Matrix3(const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z)
	: x(x)
	, y(y)
	, z(z)
{
}

template <class T>
Matrix3<T>::Matrix3(const Vector3<T> vector[3])
	: x(vector[0])
	, y(vector[1])
	, z(vector[2])
{
}

template <class T>
T Matrix3<T>::determinant() const
{
	return xx * (yy * zz - zy * yz) - xy * (yx * zz - yz * zx) + xz * (yx * zy - yy * zx);
}

template <class T>
Matrix3<T> Matrix3<T>::transpose() const
{
	return Matrix3<T>{
		xx, yx, zx,
		xy, yy, zy,
		xz, yz, zz
	};
}

template <class T>
Matrix3<T> Matrix3<T>::inverse() const
{
	T invdet = 1 / determinant();

	return Matrix3<T>{
		(yy * zz - zy * yz) * invdet,
		(xz * zy - xy * zz) * invdet,
		(xy * yz - xz * yy) * invdet,
		(yz * zx - yx * zz) * invdet,
		(xx * zz - xz * zx) * invdet,
		(yx * xz - xx * yz) * invdet,
		(yx * zy - zx * yy) * invdet,
		(zx * xy - xx * zy) * invdet,
		(xx * yy - yx * xy) * invdet
	};
}

template <class T>
Vector3<T>& Matrix3<T>::operator[](const int index)
{
	return *(((Vector3<T>*)this) + index);
}

template <class T>
bool Matrix3<T>::operator==(const Matrix3<T>& matrix) const
{
	return x == matrix.x && y == matrix.y && z == matrix.z;
}

template <class T>
bool Matrix3<T>::operator!=(const Matrix3<T>& matrix) const
{
	return x != matrix.x || y != matrix.y || z != matrix.z;
}

template <class T>
Matrix3<T> Matrix3<T>::operator*(const T value) const
{
	return Matrix3<T>{ x * value, y * value, z * value };
}

template <class T>
Matrix3<T> Matrix3<T>::operator*(const Matrix3<T>& matrix) const
{
	return Matrix3<T>{
		xx * matrix.xx + xy * matrix.yx + xz * matrix.zx,
		xx * matrix.xy + xy * matrix.yy + xz * matrix.zy,
		xx * matrix.xz + xy * matrix.yz + xz * matrix.zz,

		yx * matrix.xx + yy * matrix.yx + yz * matrix.zx,
		yx * matrix.xy + yy * matrix.yy + yz * matrix.zy,
		yx * matrix.xz + yy * matrix.yz + yz * matrix.zz,

		zx * matrix.xx + zy * matrix.yx + zz * matrix.zx,
		zx * matrix.xy + zy * matrix.yy + zz * matrix.zy,
		zx * matrix.xz + zy * matrix.yz + zz * matrix.zz
	};
}

template <class T>
Matrix3<T>& Matrix3<T>::operator=(const T value)
{
	x = value;
	y = value;
	z = value;
	return *this;
}

template <class T>
Matrix3<T>& Matrix3<T>::operator*=(const T value)
{
	return *this = *this * value;
}

template <class T>
Matrix3<T>& Matrix3<T>::operator=(const Matrix3<T>& matrix)
{
	x = matrix.x;
	y = matrix.y;
	z = matrix.z;
	return *this;
}

template <class T>
Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& matrix)
{
	return *this = *this * matrix;
}

template <class T>
Vector2<T> Matrix3<T>::operator*(const Vector2<T>& vector) const
{
	return Vector2<T>{
		xx * vector.x + yx * vector.y,
		xy * vector.x + yy * vector.y
	};
}

template <class T>
Vector3<T> Matrix3<T>::operator*(const Vector3<T>& vector) const
{
	return Vector3<T>{
		xx * vector.x + yx * vector.y + zx * vector.z,
		xy * vector.x + yy * vector.y + zy * vector.z,
		xz * vector.x + yz * vector.y + zz * vector.z
	};
}

template class Matrix3<>;
