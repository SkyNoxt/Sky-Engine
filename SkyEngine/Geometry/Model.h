
#pragma once

#include <new>

#include <Streams/Stream.h>

#include "IndexedMesh.h"

class Model
{

public:
	unsigned int numMeshes;
	IndexedMesh* meshArray;

	//Constructors
	Model(unsigned int meshCount, IndexedMesh* meshes);
	Model(const Stream& stream);

	//Member functions
	//bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const;

	void serialize(const Stream& stream) const;

	//Destructor
	~Model();
};
