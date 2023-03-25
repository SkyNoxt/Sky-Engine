
#pragma once

#include <Math/Vector3.h>
#include <Math/Vector4.h>

class Shader
{

  public:
	// Constructor
	Shader() = default;

	// Member functions
	Vector3<> shade();
	Vector4<> shadeAlpha();

	// Destructor
	~Shader() = default;
};
