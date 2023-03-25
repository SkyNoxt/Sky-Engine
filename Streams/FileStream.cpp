
#include <cstdio>
#include <fcntl.h>

#if !defined(O_BINARY)
#define O_BINARY 0
#endif

#if defined(WINDOWS)
#include <io.h>
#endif

#include "FileStream.h"

FileStream::FileStream(const char* filePath)
	: file(fdopen(open(filePath, O_RDWR | O_CREAT | O_BINARY, 0666), "r+"))
{
}

unsigned int FileStream::write(void* buffer, unsigned int size, unsigned int count) const
{
	return fwrite(buffer, size, count, file);
}

unsigned int FileStream::read(void* buffer, unsigned int size, unsigned int count) const
{
	return fread(buffer, size, count, file);
}

void FileStream::flush() const
{
	fflush(file);
}

FileStream::~FileStream()
{
	fclose(file);
}
