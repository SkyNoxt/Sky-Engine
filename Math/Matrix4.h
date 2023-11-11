
#pragma once

#include "Vector3.h"
#include "Vector4.h"

namespace Sky::Math
{
	template <class T = float>
	class Matrix4
	{
	  public:
		union
		{
			struct
			{
				T xx, xy, xz, xw;
				T yx, yy, yz, yw;
				T zx, zy, zz, zw;
				T wx, wy, wz, ww;
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

		// Constructors
		Matrix4(T xx, T xy, T xz, T xw, T yx, T yy, T yz, T yw, T zx, T zy, T zz, T zw, T wx, T wy, T wz, T ww);
		Matrix4(T matrix[16]);
		Matrix4(T value);
		Matrix4();

		Matrix4(const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w);
		Matrix4(const Vector4<T> vector[4]);

		Matrix4(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up = { 0, 1, 0 });

		// Member functions
		T determinant() const;

		Matrix4<T> transpose() const;
		Matrix4<T> inverse() const;

		void translate(T x, T y, T z);
		void translate(const Vector3<T>& translation);

		void rotate(T angle, T x, T y, T z);
		void rotate(const Vector4<T>& rotation);

		void scale(T x, T y, T z);
		void scale(const Vector3<T>& scaling);

		// Subscript operator
		Vector4<T>& operator[](const int index);

		// Binary operators
		bool operator==(const Matrix4<T>& matrix) const;
		bool operator!=(const Matrix4<T>& matrix) const;

		Matrix4<T> operator*(const T value) const;
		Matrix4<T> operator*(const Matrix4<T>& matrix) const;

		Matrix4<T>& operator=(const T value);
		Matrix4<T>& operator*=(const T value);

		Matrix4<T>& operator=(const Matrix4<T>& matrix);
		Matrix4<T>& operator*=(const Matrix4<T>& matrix);

		// Heterogeneous opeartors
		Vector3<T> operator*(const Vector3<T>& vector) const;
		Vector4<T> operator*(const Vector4<T>& vector) const;

		// Destructor
		~Matrix4() = default;

	  private:
	};
}
