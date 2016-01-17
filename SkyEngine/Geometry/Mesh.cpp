
#include "Mesh.h"

Mesh::Mesh()
{
	
}

bool Mesh::intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<float>& barycenter) const
{
	bool intersect = false;
	float tempDist, u, v;

	distance = Ray::maxLength;
	for(unsigned int i = 0; i < numVertices; i+=3)
	{
		if(triangleIntersect(ray,
			vertexArray[i].position, vertexArray[i + 1].position, vertexArray[i + 2].position,
			tempDist, u, v) && tempDist < distance)
			{
				distance = tempDist;
				barycenter = { u, v };
				index = i;
				intersect = true;
			}
	}

	return intersect;
}

Mesh::~Mesh()
{
	delete[] vertexArray;
}

bool Mesh::triangleIntersect(const Ray& ray,
		const Vector3<float>& vertex0, const Vector3<float>& vertex1, const Vector3<float>& vertex2,
    	float &distance, float &u, float &v) const
{
    Vector3<float> edge1 = vertex1 - vertex0;
    Vector3<float> edge2 = vertex2 - vertex0;

    Vector3<float> pvec = ray.direction.cross(edge2);

    float det = edge1.dot(pvec);

    if(culling && det == 0) return false;
    else if(fabs(det) == 0) return false;

    float invDet = 1 / det;

    Vector3<float> tvec = ray.origin - vertex0;
    u = tvec.dot(pvec) * invDet;
    if (u < 0 || u > 1) return false;

    Vector3<float> qvec = tvec.cross(edge1);
    v = ray.direction.dot(qvec) * invDet;
    if (v < 0 || u + v > 1) return false;
    
    distance = edge2.dot(qvec) * invDet;
    
    return true;
}
