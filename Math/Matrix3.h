
#pragma once

#include "Vector3.h"

namespace Sky::Math
{
	template <class T = float>
	class Matrix3
	{
	  public:
		union
		{
			struct
			{
				T xx, xy, xz;
				T yx, yy, yz;
				T zx, zy, zz;
			};
			struct
			{
				Vector3<T> x;
				Vector3<T> y;
				Vector3<T> z;
			};
		};

		static const Matrix3<T> IDENTITY;

		// Constructors
		Matrix3(T xx, T xy, T xz, T yx, T yy, T yz, T zx, T zy, T zz);
		Matrix3(T matrix[9]);
		Matrix3(T value);
		Matrix3();

		Matrix3(const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z);
		Matrix3(const Vector3<T> vector[3]);

		// Member functions
		T determinant() const;

		Matrix3<T> transpose() const;
		Matrix3<T> inverse() const;

		// Subscript operator
		Vector3<T>& operator[](const int index);

		// Binary operators
		bool operator==(const Matrix3<T>& matrix) const;
		bool operator!=(const Matrix3<T>& matrix) const;

		Matrix3<T> operator*(const T value) const;
		Matrix3<T> operator*(const Matrix3<T>& matrix) const;

		Matrix3<T>& operator=(const T value);
		Matrix3<T>& operator*=(const T value);

		Matrix3<T>& operator=(const Matrix3<T>& matrix);
		Matrix3<T>& operator*=(const Matrix3<T>& matrix);

		// Destructor
		~Matrix3() = default;

	  private:
	};
}
