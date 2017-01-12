
#include "Model.h"

Model::Model(unsigned int meshCount, IndexedMesh* meshes)
{
	numMeshes = meshCount;
	meshArray = meshes;
}

Model::Model(const Stream& stream)
{
	numMeshes = stream.read<unsigned int>();
	meshArray = new IndexedMesh[numMeshes];
	for(unsigned int i = 0; i < numMeshes; ++i)
		meshArray[i] = IndexedMesh(stream);
}

void Model::serialize(const Stream& stream)
{
	stream.write<unsigned int>(numMeshes);
	for(unsigned int i = 0; i < numMeshes; ++i)
		meshArray[i].serialize(stream);
}

Model::~Model()
{
	delete[] meshArray;
}
