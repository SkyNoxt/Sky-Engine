
#pragma once

#include <Math/Matrix4.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>

#include <Ray.h>

#include <Streams/Stream.h>

#include "Vertex.h"

class Mesh
{

	template <class T>
	friend class BVH;

public:
	bool culling = false;
	unsigned int numVertices;
	Vertex* vertexArray;

	//Constructors
	Mesh(unsigned int vertexCount, Vertex* vertices);
	Mesh(const Stream& stream);
	Mesh();

	//Member functions
	virtual bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<float>& barycenter) const;
	virtual unsigned int numElements() const;

	virtual const Vertex& getVertex(const int index) const;

	virtual void serialize(const Stream& stream);

	//Destructor
	virtual ~Mesh();

protected:
	//Protected member function
	bool triangleIntersect(const Ray& ray,
		const Vector3<float>& vertex0, const Vector3<float>& vertex1, const Vector3<float>& vertex2,
		float& distance, float& u, float& v) const;
};
