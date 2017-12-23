
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
    unsigned int channelDepth;
    unsigned int channelCount;
    T* pixels;

	//Constructor
	Texture(unsigned int texWidth, unsigned int texHeight, unsigned int chDepth, unsigned int chCount, T* data);
    Texture(const Stream& stream);

    //Member functions
    const T& texel(unsigned int x, unsigned int y) const;
    T& texel(unsigned int x, unsigned int y);

    void serialize(const Stream& stream) const;

	//Destructor
	~Texture();
};
