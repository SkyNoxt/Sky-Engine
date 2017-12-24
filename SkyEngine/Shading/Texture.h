
#pragma once

#include <Math/Vector4.h>

#include <Streams/Stream.h>

template <class T = Vector4<unsigned char>>
class Texture
{

public:
	//Member variables
	unsigned int width;
	unsigned int height;
	T* pixels;

	//Constructor
	Texture(unsigned int texWidth, unsigned int texHeight, T* data);
	Texture(const Stream& stream);

	//Member functions
	const T& texel(unsigned int x, unsigned int y) const;
	T& texel(unsigned int x, unsigned int y);

	void serialize(const Stream& stream) const;

	//Destructor
	~Texture();
};
