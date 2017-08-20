
#pragma once

#include "Mesh.h"

class IndexedMesh : public Mesh
{

public:
	unsigned int numIndices;
	unsigned int* indexArray;

	//Constructors
	IndexedMesh(unsigned int vertexCount, Vertex* vertices, unsigned int indexCount, unsigned int* indices);
	IndexedMesh(const Stream& stream);
	IndexedMesh();

	//Member functions
	bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const override;
	unsigned int numElements() const override;

	const Vertex& getVertex(int index) const override;

	void serialize(const Stream& stream) const override;

	//Destructor
	~IndexedMesh() override;
};
