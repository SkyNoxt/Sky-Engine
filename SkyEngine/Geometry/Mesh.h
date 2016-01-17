
#pragma once

#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Matrix4.h>

#include <Ray.h>

#include "Vertex.h"

class Mesh
{

public:

	bool culling = false;
	unsigned int numVertices;
	Vertex* vertexArray;

	//Constructor
	Mesh();

	//Member function
	virtual bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<float>& barycenter) const;

	//Destructor
	~Mesh();

protected:

	//Protected member function
	bool triangleIntersect(const Ray& ray,
		const Vector3<float>& vertex0, const Vector3<float>& vertex1, const Vector3<float>& vertex2,
    	float &distance, float &u, float &v) const;
		
};
