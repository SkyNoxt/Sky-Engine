
#include <cmath>

#include "Mesh.h"

Mesh::Mesh(unsigned int vertexCount, Vertex* vertices)
	: numVertices(vertexCount)
	, vertexArray(vertices)
{
}

Mesh::Mesh(const Stream& stream)
	: numVertices(stream.read<unsigned int>())
	, vertexArray(stream.read<Vertex>(numVertices))
{
}

Mesh::Mesh()
	: numVertices(0)
	, vertexArray(nullptr)
{
}

bool Mesh::intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const
{
	bool intersect = false;
	float tempDist, u, v;

	distance = Ray::MAX_LENGTH;
	for(unsigned int i = 0; i < numVertices; i += 3)
		{
			if(triangleIntersect(ray,
				   vertexArray[i].position, vertexArray[i + 1].position, vertexArray[i + 2].position,
				   tempDist, u, v)
				&& tempDist > 0 && tempDist < distance)
				{
					distance = tempDist;
					barycenter = { u, v };
					index = i;
					intersect = true;
				}
		}

	return intersect;
}

unsigned int Mesh::numElements() const
{
	return numVertices;
}

const Vertex& Mesh::getVertex(int index) const
{
	return vertexArray[index];
}

void Mesh::serialize(const Stream& stream) const
{
	stream.write<unsigned int>(numVertices);
	stream.write<Vertex>(vertexArray, numVertices);
}

Mesh::~Mesh()
{
	delete[] vertexArray;
}

bool Mesh::triangleIntersect(const Ray& ray,
	const Vector3<>& vertex0, const Vector3<>& vertex1, const Vector3<>& vertex2,
	float& distance, float& u, float& v) const
{
	Vector3<> edge1 = vertex1 - vertex0;
	Vector3<> edge2 = vertex2 - vertex0;

	Vector3<> pvec = ray.direction.cross(edge2);

	float det = edge1.dot(pvec);

	if(culling && det <= 0)
		return false;
	if(fabs(det) == 0)
		return false;

	float invDet = 1 / det;

	Vector3<> tvec = ray.origin - vertex0;
	u = tvec.dot(pvec) * invDet;
	if(u < 0 || u > 1)
		return false;

	Vector3<> qvec = tvec.cross(edge1);
	v = ray.direction.dot(qvec) * invDet;
	if(v < 0 || u + v > 1)
		return false;

	distance = edge2.dot(qvec) * invDet;

	return true;
}
