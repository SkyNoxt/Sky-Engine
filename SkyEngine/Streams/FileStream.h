
#pragma once

#include <fcntl.h>
#include <stdio.h>

#include "Stream.h"

class FileStream : public Stream
{

public:
	//Constructor
	FileStream(const char* filePath);

	//Member functions
	unsigned int write(void* buffer, unsigned int size, unsigned int count) const;
	unsigned int read(void* buffer, unsigned int size, unsigned int count) const;
	void flush() const;

	//Destructor
	~FileStream();

private:
	FILE* file;
};
