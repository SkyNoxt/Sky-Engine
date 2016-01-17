
#include "IndexedMesh.h"

IndexedMesh::IndexedMesh()
{
	
}

bool IndexedMesh::intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<float>& barycenter) const
{
	bool intersect = false;
	for(unsigned int i = 0; i < numIndices; i+=3)
	{
		distance = Ray::maxLength;
		float tempDist, u, v;
		if(triangleIntersect(ray,
			vertexArray[indexArray[i]].position, vertexArray[indexArray[i + 1]].position,
			vertexArray[indexArray[i + 2]].position, tempDist, u, v) && tempDist < distance)
			{
				distance = tempDist;
				barycenter = { u, v };
				index = i;
				intersect = true;
			}
	}

	return intersect;
}

IndexedMesh::~IndexedMesh()
{
	delete[] indexArray;
}
