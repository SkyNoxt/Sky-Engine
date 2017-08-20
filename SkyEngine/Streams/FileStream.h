
#pragma once

#include "Stream.h"

class FileStream : public Stream
{

public:
	//Constructor
	FileStream(const char* filePath);

	//Member functions
	unsigned int write(void* buffer, unsigned int size, unsigned int count) const override;
	unsigned int read(void* buffer, unsigned int size, unsigned int count) const override;
	void flush() const override;

	//Destructor
	~FileStream() override;

private:
	FILE* file;
};
