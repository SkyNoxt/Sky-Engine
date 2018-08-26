
#include "Sampler.h"

Sampler::Sampler(unsigned int smpWidth, unsigned int smpHeight, unsigned int smpDepth, unsigned int smpLength, unsigned int smpSize, unsigned char* data)
	: width(smpWidth)
	, height(smpHeight)
	, depth(smpDepth)
	, length(smpLength)
	, sampleSize(smpSize)
	, samples(data)
{
}

Sampler::Sampler(const Stream& stream)
	: width(stream.read<unsigned int>())
	, height(stream.read<unsigned int>())
	, depth(stream.read<unsigned int>())
	, length(stream.read<unsigned int>())
	, sampleSize(stream.read<unsigned int>())
	, samples(stream.read<unsigned char>(width * height * depth * length * sampleSize))
{
}

void Sampler::serialize(const Stream& stream) const
{
	stream.write<unsigned int>(width);
	stream.write<unsigned int>(height);
	stream.write<unsigned int>(depth);
	stream.write<unsigned int>(length);
	stream.write<unsigned int>(sampleSize);
	stream.write<unsigned char>(samples, width * height * depth * length * sampleSize);
}

Sampler::~Sampler()
{
	delete[] samples;
}
