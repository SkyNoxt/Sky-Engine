
#pragma once

#include <Math/Vector2.h>
#include <Math/Vector3.h>

#include <Ray.h>

#include <Streams/Stream.h>

#include "Vertex.h"

class Mesh
{
public:
	bool culling = false;
	unsigned int numVertices;
	unsigned int numIndices;
	Vertex* vertexArray;
	unsigned int* indexArray;

	//Constructors
	Mesh(unsigned int vertexCount, unsigned int indexCount, Vertex* vertices, unsigned int* indices);
	Mesh(unsigned int vertexCount, Vertex* vertices);
	Mesh(const Stream& stream);
	Mesh();

	//Member functions
	bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const;
	unsigned int numElements() const;

	const Vertex& get(int index) const;

	void serialize(const Stream& stream) const;

	//Destructor
	~Mesh();

private:
	bool triangleIntersect(const Ray& ray,
		const Vector3<>& vertex0, const Vector3<>& vertex1, const Vector3<>& vertex2,
		float& distance, float& u, float& v) const;
};
