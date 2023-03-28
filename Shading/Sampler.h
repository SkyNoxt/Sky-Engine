
#pragma once

#include <Streams/Stream.h>

class Sampler
{

  public:
	unsigned int size;
	unsigned int width;
	unsigned int height;
	unsigned int depth;
	unsigned int length;

	unsigned char* samples;

	// Constructor
	Sampler(unsigned int smpSize, unsigned int smpWidth, unsigned int smpHeight, unsigned int smpDepth, unsigned int smpLength, unsigned char* data);
	Sampler(const Stream& stream);

	// Member functions

	template <class T>
	T& sample(unsigned int x);
	template <class T>
	T& sample(unsigned int x, unsigned int y);

	template <class T>
	T sample(float x);
	template <class T>
	T sample(float x, float y);

	void serialize(const Stream& stream) const;

	// Destructor
	~Sampler();
};

template <class T>
T& Sampler::sample(unsigned int x)
{
	return ((T*)samples)[x];
}

template <class T>
T& Sampler::sample(unsigned int x, unsigned int y)
{
	return ((T*)samples)[y * width + x];
}

template <class T>
T Sampler::sample(float x)
{
	unsigned int ix = (unsigned int)x;
	float dx = x - ix;

	T f0 = ((T*)samples)[ix];
	T f1 = ((T*)samples)[ix + 1];

	return f0 * (1.f - dx) + f1 * dx;
}

template <class T>
T Sampler::sample(float x, float y)
{
	unsigned int ix = (unsigned int)x;
	unsigned int iy = (unsigned int)y;
	float dx = x - ix;
	float dy = y - iy;

	T f00 = ((T*)samples)[iy * width + ix];
	T f01 = ((T*)samples)[iy * width + (ix + 1)];
	T f10 = ((T*)samples)[(iy + 1) * width + ix];
	T f11 = ((T*)samples)[(iy + 1) * width + (ix + 1)];

	return (f00 * (1.f - dx) + f01 * dx) * (1.f - dy) + (f10 * (1.f - dx) + f11 * dx) * dy;
}
