
#pragma once

#include <new>

#include <Streams/Stream.h>

#include "Mesh.h"

class Model
{

  public:
	unsigned int numMeshes;
	Mesh* meshArray;

	// Constructors
	Model(unsigned int meshCount, Mesh* meshes);
	Model(const Stream& stream);

	// Member functions
	// bool intersect(const Ray& ray, float& distance, unsigned int& index, Vector2<>& barycenter) const;

	void serialize(const Stream& stream) const;

	// Destructor
	~Model();
};
