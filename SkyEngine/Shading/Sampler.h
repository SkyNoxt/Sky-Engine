
#pragma once

#include <Streams/Stream.h>

class Sampler
{

public:
	//Member variables
	unsigned int size;
	unsigned int width;
	unsigned int height;
	unsigned int depth;
	unsigned int length;
	unsigned char* samples;

	//Constructor
	Sampler(unsigned int smpSize, unsigned int smpWidth, unsigned int smpHeight, unsigned int smpDepth, unsigned int smpLength, unsigned char* data);
	Sampler(const Stream& stream);

	//Member functions

	template <class T>
	const T& sample(unsigned int x = 1, unsigned int y = 1) const;

	template <class T>
	T& sample(unsigned int x = 1, unsigned int y = 1);

	void serialize(const Stream& stream) const;

	//Destructor
	~Sampler();
};

template <class T>
const T& Sampler::sample(unsigned int x, unsigned int y) const
{
	return ((T*)samples)[y * width + x];
}

template <class T>
T& Sampler::sample(unsigned int x, unsigned int y)
{
	return ((T*)samples)[y * width + x];
}
