
#include "Texture.h"

template <class T>
Texture<T>::Texture(unsigned int texWidth, unsigned int texHeight, T* data)
	: width(texWidth)
	, height(texHeight)
	, pixels(data)
{
}

template <class T>
Texture<T>::Texture(const Stream& stream)
	: width(stream.read<unsigned int>())
	, height(stream.read<unsigned int>())
	, pixels(stream.read<T>(width * height))
{
}

template <class T>
const T& Texture<T>::texel(unsigned int x, unsigned int y) const
{
	return pixels[y * width + x];
}

template <class T>
T& Texture<T>::texel(unsigned int x, unsigned int y)
{
	return pixels[y * width + x];
}

template <class T>
void Texture<T>::serialize(const Stream& stream) const
{
	stream.write<unsigned int>(width);
	stream.write<unsigned int>(height);
	stream.write<T>(pixels, width * height);
}

template <class T>
Texture<T>::~Texture()
{
	delete[] pixels;
}

template class Texture<>;
