
#pragma once

template <typename T = float>
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

	// Constructors
	Vector3(const T x, const T y, const T z);
	Vector3(const T values[3]);
	Vector3(const T value);
	Vector3() = default;

	template <typename S>
	Vector3(const Vector3<S>& vector);

	// Member functions
	T dot() const;
	T length() const;
	T dot(const Vector3& vector) const;
	T distance(const Vector3& vector) const;

	Vector3 normalize() const;
	Vector3 middle(const Vector3& vector) const;

	Vector3 cross(const Vector3& vector) const;

	static Vector3 minima(const Vector3& a, const Vector3& b);
	static Vector3 maxima(const Vector3& a, const Vector3& b);

	// Unary operators
	Vector3 operator-() const;

	// Subscript operator
	T& operator[](const int index);

	// Binary operators
	Vector3& operator=(const T value);
	Vector3& operator+=(const T value);
	Vector3& operator-=(const T value);
	Vector3& operator*=(const T value);

	Vector3& operator=(const Vector3& vector);
	Vector3& operator+=(const Vector3& vector);
	Vector3& operator-=(const Vector3& vector);
	Vector3& operator*=(const Vector3& vector);

	bool operator==(const Vector3& vector) const;
	bool operator!=(const Vector3& vector) const;

	Vector3 operator+(const T value) const;
	Vector3 operator-(const T value) const;
	Vector3 operator*(const T value) const;

	Vector3 operator+(const Vector3& vector) const;
	Vector3 operator-(const Vector3& vector) const;
	Vector3 operator*(const Vector3& vector) const;

	// Destructor
	~Vector3() = default;

  private:
};

// Heterogeneous opeartors

template <typename T, typename S>
Vector3<S> operator*(const Vector3<T>& vector, const S value);
