
#include "IndexedMesh.h"

IndexedMesh::IndexedMesh()
{
}

bool IndexedMesh::intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<float>& barycenter) const
{
	bool intersect = false;
	float tempDist, u, v;

	distance = Ray::maxLength;
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

const Vertex& IndexedMesh::getVertex(const int index) const
{
	return vertexArray[indexArray[index]];
}

void IndexedMesh::write(const Stream& stream)
{
	Mesh::write(stream);
	stream.write<unsigned int>(numIndices);
	stream.write<unsigned int>(indexArray, numIndices);
}

void IndexedMesh::read(const Stream& stream)
{
	Mesh::read(stream);
	numIndices = stream.read<unsigned int>();
	indexArray = stream.read<unsigned int>(numIndices);
}

IndexedMesh::~IndexedMesh()
{
	delete[] indexArray;
}
