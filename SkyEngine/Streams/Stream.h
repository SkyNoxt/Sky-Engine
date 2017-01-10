
#pragma once

class Stream
{

public:
	//Member functions
	virtual unsigned int write(void* buffer, unsigned int size, unsigned int count) const = 0;
	virtual unsigned int read(void* buffer, unsigned int size, unsigned int count) const = 0;
	virtual void flush() const = 0;

	template <typename T>
	T read() const;

	template <typename T>
	T* read(unsigned int count) const;

	template <typename T>
	void write(T value) const;

	template <typename T>
	void write(T* value, unsigned int count) const;

	//Destructor
	virtual ~Stream() = 0;
};

//Template method implementations

template <typename T>
T Stream::read() const
{
	T value;
	read(&value, sizeof(T), 1);
	return value;
}

template <typename T>
T* Stream::read(unsigned int count) const
{
	T* value = new T[count];
	read(value, sizeof(T), count);
	return value;
}

template <typename T>
void Stream::write(T value) const
{
	write(&value, sizeof(T), 1);
}

template <typename T>
void Stream::write(T* value, unsigned int count) const
{
	write(value, sizeof(T), count);
}