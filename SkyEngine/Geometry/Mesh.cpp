
#include <cmath>

#include "Mesh.h"
#include "Vertex.h"

Mesh::Mesh(unsigned int vertexSize, unsigned int vertexCount, unsigned int indexCount, unsigned char* vertices, unsigned int* indices)
	: size(vertexSize)
	, numVertices(vertexCount)
	, numIndices(indexCount)
	, vertexArray(vertices)
	, indexArray(indices)
{
}

Mesh::Mesh(unsigned int vertexSize, unsigned int vertexCount, unsigned char* vertices)
	: size(vertexSize)
	, numVertices(vertexCount)
	, numIndices(0)
	, vertexArray(vertices)
	, indexArray(nullptr)
{
}

Mesh::Mesh(const Stream& stream)
	: size(stream.read<unsigned int>())
	, numVertices(stream.read<unsigned int>())
	, numIndices(stream.read<unsigned int>())
	, vertexArray(stream.read<unsigned char>(size * numVertices))
	, indexArray(numVertices ? stream.read<unsigned int>(numIndices) : nullptr)
{
}

Mesh::Mesh()
	: size(0)
	, numVertices(0)
	, numIndices(0)
	, vertexArray(nullptr)
	, indexArray(nullptr)
{
}

unsigned int Mesh::numElements() const
{
	if(indexArray)
		return numIndices;
	return numVertices;
}

template <class T>
bool Mesh::intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const
{
	bool intersect = false;
	float tempDist, u, v;

	distance = Ray::MAX_LENGTH;
	for(unsigned int i = 0; i < numVertices; i += 3)
		{
			if(triangleIntersect(ray, vertex<T>(i).position, vertex<T>(i + 1).position, vertex<T>(i + 2).position, tempDist, u, v)
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

template <class T>
const T& Mesh::vertex(unsigned int index) const
{
	if(indexArray)
		return ((T*)vertexArray)[indexArray[index]];
	return ((T*)vertexArray)[index];
}

template <class T>
T& Mesh::vertex(unsigned int index)
{
	if(indexArray)
		return ((T*)vertexArray)[indexArray[index]];
	return ((T*)vertexArray)[index];
}

void Mesh::serialize(const Stream& stream) const
{
	stream.write<unsigned int>(size);
	stream.write<unsigned int>(numVertices);
	stream.write<unsigned int>(numIndices);
	stream.write<unsigned char>(vertexArray, size * numVertices);
	stream.write<unsigned int>(indexArray, numIndices);
}

Mesh::~Mesh()
{
	delete[] vertexArray;
	delete[] indexArray;
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
	if(std::abs(det) == 0)
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

template bool Mesh::intersect<Vertex>(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const;

template const Vertex& Mesh::vertex<Vertex>(unsigned int index) const;
template Vertex& Mesh::vertex<Vertex>(unsigned int index);
