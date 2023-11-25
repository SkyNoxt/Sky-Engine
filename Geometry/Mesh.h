
#pragma once

#include <Math/Vector2.h>
#include <Math/Vector3.h>

#include <Ray.h>

#include <IO/Stream.h>

using Sky::Math::Vector2;
using Sky::Math::Vector3;

using Sky::IO::Stream;

struct Vertex
{
	Vector3<> position;
	Vector3<> normal;
	Vector2<> texCoord;
};

class Mesh
{
  public:
	bool culling = false;

	unsigned int size;
	unsigned int numVertices;
	unsigned int numIndices;

	unsigned char* vertexArray;
	unsigned int* indexArray;

	// Constructors
	Mesh(unsigned int vertexSize, unsigned int vertexCount, unsigned int indexCount, unsigned char* vertices, unsigned int* indices);
	Mesh(unsigned int vertexSize, unsigned int vertexCount, unsigned char* vertices);
	Mesh(const Stream& stream);
	Mesh();

	// Member functions
	unsigned int numElements() const;

	template <typename T>
	bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const;

	template <typename T>
	const T& vertex(unsigned int index) const;

	template <typename T>
	T& vertex(unsigned int index);

	void serialize(const Stream& stream) const;

	// Destructor
	~Mesh();

  private:
	bool triangleIntersect(const Ray& ray,
						   const Vector3<>& vertex0, const Vector3<>& vertex1, const Vector3<>& vertex2,
						   float& distance, float& u, float& v) const;
};
