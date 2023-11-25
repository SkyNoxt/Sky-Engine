
#pragma once

#include "Stream.h"

namespace Sky::IO
{
	class FileStream : public Stream
	{

	  public:
		// Constructor
		FileStream(const char* file);

		// Member functions
		unsigned int read(void* buffer, unsigned int size, unsigned int count) const override;
		unsigned int write(void* buffer, unsigned int size, unsigned int count) const override;

		// Destructor
		~FileStream() override;

	  private:
		FILE* file;
	};
}
