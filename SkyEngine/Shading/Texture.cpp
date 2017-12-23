
#include "Texture.h"

template <class T>
Texture<T>::Texture(unsigned int texWidth, unsigned int texHeight, unsigned int chDepth, unsigned int chCount, T* data)
	: width(texWidth)
    , height(texHeight)
    , channelDepth(chDepth)
    , channelCount(chCount)
    , pixels(data)
{
}

template <class T>
Texture<T>::Texture(const Stream& stream)
	: width(stream.read<unsigned int>())
    , height(stream.read<unsigned int>())
    , channelDepth(stream.read<unsigned int>())
    , channelCount(stream.read<unsigned int>())
    , pixels(stream.read<T>(width * height))
{
}

template <class T>
void Texture<T>::serialize(const Stream& stream) const
{
    stream.write<unsigned int>(width);
    stream.write<unsigned int>(height);
    stream.write<unsigned int>(channelDepth);
    stream.write<unsigned int>(channelCount);
    stream.write<T>(pixels, width * height);
}

template <class T>
Texture<T>::~Texture()
{
	delete[] pixels;
}

template class Texture<>;
