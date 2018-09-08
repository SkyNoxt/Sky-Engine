
#include "Sampler.h"

Sampler::Sampler(unsigned int smpSize, unsigned int smpWidth, unsigned int smpHeight, unsigned int smpDepth, unsigned int smpLength, unsigned char* data)
	: size(smpSize)
	, width(smpWidth)
	, height(smpHeight)
	, depth(smpDepth)
	, length(smpLength)
	, samples(data)
{
}

Sampler::Sampler(const Stream& stream)
	: size(stream.read<unsigned int>())
	, width(stream.read<unsigned int>())
	, height(stream.read<unsigned int>())
	, depth(stream.read<unsigned int>())
	, length(stream.read<unsigned int>())
	, samples(stream.read<unsigned char>(size * width * height * depth * length))
{
}

void Sampler::serialize(const Stream& stream) const
{
	stream.write<unsigned int>(size);
	stream.write<unsigned int>(width);
	stream.write<unsigned int>(height);
	stream.write<unsigned int>(depth);
	stream.write<unsigned int>(length);
	stream.write<unsigned char>(samples, size * width * height * depth * length);
}

Sampler::~Sampler()
{
	delete[] samples;
}
