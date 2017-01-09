
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

void IndexedMesh::write(FILE* file)
{
	Mesh::write(file);
	fwrite(&numIndices, sizeof(numIndices), 1, file);
	fwrite(indexArray, sizeof(unsigned int), numIndices, file);
}

void IndexedMesh::read(FILE* file)
{
	Mesh::read(file);
	fread(&numIndices, sizeof(numIndices), 1, file);
	indexArray = new unsigned int[numIndices];
	fread(indexArray, sizeof(unsigned int), numIndices, file);
}

IndexedMesh::~IndexedMesh()
{
	delete[] indexArray;
}
