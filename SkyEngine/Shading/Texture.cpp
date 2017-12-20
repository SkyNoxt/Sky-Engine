
#include "Texture.h"

Texture::Texture(unsigned int texWidth, unsigned int texHeight, unsigned int chDepth, unsigned int chCount, unsigned char* data)
	: width(texWidth)
    , height(texHeight)
    , channelDepth(chDepth)
    , channelCount(chCount)
    , pixels(data)
{
}

Texture::Texture(const Stream& stream)
	: width(stream.read<unsigned int>())
    , height(stream.read<unsigned int>())
    , channelDepth(stream.read<unsigned int>())
    , channelCount(stream.read<unsigned int>())
    , pixels(stream.read<unsigned char>(width * height * channelDepth * channelCount / 8))
{
}

void Texture::serialize(const Stream& stream) const
{
    stream.write<unsigned int>(width);
    stream.write<unsigned int>(height);
    stream.write<unsigned int>(channelDepth);
    stream.write<unsigned int>(channelCount);
    stream.write<unsigned char>(pixels, width * height * channelDepth * channelCount / 8);
}

Texture::~Texture()
{
	delete[] pixels;
}
