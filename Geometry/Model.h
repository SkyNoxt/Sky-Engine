
#pragma once

#include <IO/Stream.h>

#include "Mesh.h"

namespace Sky::Geometry
{
	class Model
	{

	  public:
		unsigned int meshCount;
		Mesh* meshes;

		// Constructors
		Model(unsigned int meshCount, Mesh* meshes);
		Model(const Stream& stream);

		void serialize(const Stream& stream) const;

		// Destructor
		~Model();
	};
}
