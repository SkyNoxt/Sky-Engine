
#include "Sampler.h"

template <class T>
Sampler<T>::Sampler(unsigned int smpWidth, unsigned int smpHeight, unsigned int smpDepth, unsigned int smpLength, T* data)
	: width(smpWidth)
	, height(smpHeight)
	, depth(smpDepth)
	, length(smpLength)
	, samples(data)
{
}

template <class T>
Sampler<T>::Sampler(const Stream& stream)
	: width(stream.read<unsigned int>())
	, height(stream.read<unsigned int>())
	, depth(stream.read<unsigned int>())
	, length(stream.read<unsigned int>())
	, samples(stream.read<T>(width * height * depth * length))
{
}

template <class T>
const T& Sampler<T>::sample(unsigned int x, unsigned int y) const
{
	return samples[y * width + x];
}

template <class T>
T& Sampler<T>::sample(unsigned int x, unsigned int y)
{
	return samples[y * width + x];
}

template <class T>
void Sampler<T>::serialize(const Stream& stream) const
{
	stream.write<unsigned int>(width);
	stream.write<unsigned int>(height);
	stream.write<unsigned int>(depth);
	stream.write<unsigned int>(length);
	stream.write<T>(samples, width * height * depth * length);
}

template <class T>
Sampler<T>::~Sampler()
{
	delete[] samples;
}

template class Sampler<>;
