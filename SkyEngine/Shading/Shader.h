
#pragma once

#include <Math/Vector3.h>
#include <Math/Vector4.h>

class Shader
{

public:
	//Constructor
	Shader();

	//Member functions
	Vector3<float> shade();
	Vector4<float> shadeAlpha();

	//Destructor
	~Shader();
};
