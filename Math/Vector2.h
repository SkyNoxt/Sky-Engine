
#pragma once

template <typename T = float>
class Vector2
{
  public:
	union
	{
		struct
		{
			T x;
			T y;
		};
		T vector[2];
	};

	// Constructors
	Vector2(const T x, const T y);
	Vector2(const T values[2]);
	Vector2(const T value);
	Vector2() = default;

	template <typename S>
	Vector2(const Vector2<S>& vector);

	// Member functions
	T dot() const;
	T length() const;
	T dot(const Vector2& vector) const;
	T distance(const Vector2& vector) const;

	Vector2 normalize() const;
	Vector2 middle(const Vector2& vector) const;

	static Vector2 minima(const Vector2& a, const Vector2& b);
	static Vector2 maxima(const Vector2& a, const Vector2& b);

	// Unary operators
	Vector2 operator-() const;

	// Subscript operator
	T& operator[](const int index);

	// Binary operators
	Vector2& operator=(const T value);
	Vector2& operator+=(const T value);
	Vector2& operator-=(const T value);
	Vector2& operator*=(const T value);

	Vector2& operator=(const Vector2& vector);
	Vector2& operator+=(const Vector2& vector);
	Vector2& operator-=(const Vector2& vector);
	Vector2& operator*=(const Vector2& vector);

	bool operator==(const Vector2& vector) const;
	bool operator!=(const Vector2& vector) const;

	Vector2 operator+(const T value) const;
	Vector2 operator-(const T value) const;
	Vector2 operator*(const T value) const;

	Vector2 operator+(const Vector2& vector) const;
	Vector2 operator-(const Vector2& vector) const;
	Vector2 operator*(const Vector2& vector) const;

	// Destructor
	~Vector2() = default;

  private:
};

// Heterogeneous opeartors

template <typename T, typename S>
Vector2<S> operator*(const Vector2<T>& vector, const S value);
