
#include "IndexedMesh.h"

IndexedMesh::IndexedMesh(unsigned int vertexCount, Vertex* vertices, unsigned int indexCount, unsigned int* indices)
	: Mesh(vertexCount, vertices)
	, numIndices(indexCount)
	, indexArray(indices)
{
}

IndexedMesh::IndexedMesh(const Stream& stream)
	: Mesh(stream)
	, numIndices(stream.read<unsigned int>())
	, indexArray(stream.read<unsigned int>(numIndices))
{
}

IndexedMesh::IndexedMesh()
	: numIndices(0)
	, indexArray(nullptr)
{
}

bool IndexedMesh::intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const
{
	bool intersect = false;
	float tempDist, u, v;

	distance = Ray::MAX_LENGTH;
	for(unsigned int i = 0; i < numIndices; i += 3)
		{
			if(triangleIntersect(ray,
				   vertexArray[indexArray[i]].position, vertexArray[indexArray[i + 1]].position,
				   vertexArray[indexArray[i + 2]].position, tempDist, u, v)
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

unsigned int IndexedMesh::numElements() const
{
	return numIndices;
}

const Vertex& IndexedMesh::getVertex(int index) const
{
	return vertexArray[indexArray[index]];
}

void IndexedMesh::serialize(const Stream& stream) const
{
	Mesh::serialize(stream);
	stream.write<unsigned int>(numIndices);
	stream.write<unsigned int>(indexArray, numIndices);
}

IndexedMesh::~IndexedMesh()
{
	delete[] indexArray;
}
