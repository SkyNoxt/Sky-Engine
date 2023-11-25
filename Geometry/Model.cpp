
#include <new>

#include "Model.h"

using Sky::Geometry::Model;

Model::Model(unsigned int meshCount, Mesh* meshes)
	: meshCount(meshCount)
	, meshes(meshes)
{
}

Model::Model(const Stream& stream)
	: meshCount(stream.read<unsigned int>())
	, meshes(new Mesh[meshCount])
{
	for(unsigned int i = 0; i < meshCount; ++i)
		new(meshes + i) Mesh(stream);
}

void Model::serialize(const Stream& stream) const
{
	stream.write<unsigned int>(meshCount);
	for(unsigned int i = 0; i < meshCount; ++i)
		meshes[i].serialize(stream);
}

Model::~Model()
{
	delete[] meshes;
}
