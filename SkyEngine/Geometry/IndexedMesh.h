﻿
#pragma once

#include "Mesh.h"

class IndexedMesh : public Mesh
{

public:
	unsigned int numIndices;
	unsigned int* indexArray;

	//Constructor
	IndexedMesh(const Stream& stream);

	//Member function
	bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<float>& barycenter) const;
	unsigned int numElements() const;

	const Vertex& getVertex(const int index) const;

	void serialize(const Stream& stream);

	//Destructor
	~IndexedMesh();
};
