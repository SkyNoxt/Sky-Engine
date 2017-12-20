
#pragma once

#include <Streams/Stream.h>

class Texture
{

public:

	//Member variables
    unsigned int width;
    unsigned int height;
    unsigned int channelDepth;
    unsigned int channelCount;
    unsigned char* pixels;

	//Constructor
	Texture(unsigned int texWidth, unsigned int texHeight, unsigned int chDepth, unsigned int chCount, unsigned char* data);
    Texture(const Stream& stream);

    //Member functions
    void serialize(const Stream& stream) const;

	//Destructor
	~Texture();
};
