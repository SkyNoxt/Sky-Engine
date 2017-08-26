
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
