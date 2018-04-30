
#pragma once

#include <Math/Vector4.h>

#include <Streams/Stream.h>

template <class T = Vector4<unsigned char>>
class Sampler
{

public:
	//Member variables
	unsigned int width;
	unsigned int height;
	unsigned int depth;
	unsigned int length;
	T* samples;

	//Constructor
	Sampler(unsigned int smpWidth, unsigned int smpHeight, unsigned int smpDepth, unsigned int smpLength, T* data);
	Sampler(const Stream& stream);

	//Member functions
	const T& sample(unsigned int x = 1, unsigned int y = 1) const;
	T& sample(unsigned int x = 1, unsigned int y = 1);

	void serialize(const Stream& stream) const;

	//Destructor
	~Sampler();
};
