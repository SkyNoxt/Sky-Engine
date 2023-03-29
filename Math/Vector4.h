
#pragma once

template <typename T = float>
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

	// Constructors
	Vector4(const T x, const T y, const T z, const T w);
	Vector4(const T values[4]);
	Vector4(const T value);
	Vector4() = default;

	template <typename S>
	Vector4(const Vector4<S>& vector);

	// Member functions
	T dot() const;
	T length() const;
	T dot(const Vector4& vector) const;
	T distance(const Vector4& vector) const;

	Vector4 normalize() const;
	Vector4 middle(const Vector4& vector) const;

	static Vector4 minima(const Vector4& a, const Vector4& b);
	static Vector4 maxima(const Vector4& a, const Vector4& b);

	// Unary operators
	Vector4 operator-() const;

	// Subscript operator
	T& operator[](const int index);

	// Binary operators
	Vector4& operator=(const T value);
	Vector4& operator+=(const T value);
	Vector4& operator-=(const T value);
	Vector4& operator*=(const T value);

	Vector4& operator=(const Vector4& vector);
	Vector4& operator+=(const Vector4& vector);
	Vector4& operator-=(const Vector4& vector);
	Vector4& operator*=(const Vector4& vector);

	bool operator==(const Vector4& vector) const;
	bool operator!=(const Vector4& vector) const;

	Vector4 operator+(const T value) const;
	Vector4 operator-(const T value) const;
	Vector4 operator*(const T value) const;

	Vector4 operator+(const Vector4& vector) const;
	Vector4 operator-(const Vector4& vector) const;
	Vector4 operator*(const Vector4& vector) const;

	// Destructor
	~Vector4() = default;

  private:
};

// Heterogeneous opeartors

template <typename T, typename S>
Vector4<S> operator*(const Vector4<T>& vector, const S value);
