
#include <cstdio>
#include <fcntl.h>

#if defined(WINDOWS)
#include <io.h>
#endif

#if !defined(O_BINARY)
#define O_BINARY 0
#endif

#include "FileStream.h"

using Sky::IO::FileStream;

FileStream::FileStream(const char* file)
	: file(fdopen(open(file, O_RDWR | O_CREAT | O_BINARY, 0666), "r+"))
{
}

unsigned int FileStream::read(void* buffer, unsigned int size, unsigned int count) const
{
	return fread(buffer, size, count, file);
}

unsigned int FileStream::write(void* buffer, unsigned int size, unsigned int count) const
{
	return fwrite(buffer, size, count, file);
}

FileStream::~FileStream()
{
	fclose(file);
}
