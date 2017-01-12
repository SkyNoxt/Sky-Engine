
#pragma once

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
	//virtual bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<float>& barycenter) const;

	void serialize(const Stream& stream);

	//Destructor
	~Model();
};
