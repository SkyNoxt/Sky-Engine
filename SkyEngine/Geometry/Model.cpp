
#include "Model.h"

Model::Model(unsigned int meshCount, Mesh* meshes)
	: numMeshes(meshCount)
	, meshArray(meshes)
{
}

Model::Model(const Stream& stream)
	: numMeshes(stream.read<unsigned int>())
	, meshArray(new Mesh[numMeshes])
{
	for(unsigned int i = 0; i < numMeshes; ++i)
		new(meshArray + i) Mesh(stream);
}

void Model::serialize(const Stream& stream) const
{
	stream.write<unsigned int>(numMeshes);
	for(unsigned int i = 0; i < numMeshes; ++i)
		meshArray[i].serialize(stream);
}

Model::~Model()
{
	delete[] meshArray;
}
