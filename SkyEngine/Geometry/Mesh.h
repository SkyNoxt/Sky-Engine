
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
	Vertex* vertexArray;

	//Constructors
	Mesh(unsigned int vertexCount, Vertex* vertices);
	Mesh(const Stream& stream);
	Mesh();

	//Member functions
	virtual bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const;
	virtual unsigned int numElements() const;

	virtual const Vertex& getVertex(int index) const;

	virtual void serialize(const Stream& stream) const;

	//Destructor
	virtual ~Mesh();

protected:
	//Protected member function
	bool triangleIntersect(const Ray& ray,
		const Vector3<>& vertex0, const Vector3<>& vertex1, const Vector3<>& vertex2,
		float& distance, float& u, float& v) const;
};
