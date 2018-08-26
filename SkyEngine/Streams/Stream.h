
#pragma once

class Stream
{

public:
	//Member functions
	virtual unsigned int write(void* buffer, unsigned int size, unsigned int count) const = 0;
	virtual unsigned int read(void* buffer, unsigned int size, unsigned int count) const = 0;
	virtual void flush() const = 0;

	template <class T>
	T read() const;

	template <class T>
	T* read(unsigned int count) const;

	template <class T>
	void write(T value) const;

	template <class T>
	void write(T* value, unsigned int count) const;

	//Destructor
	virtual ~Stream() = default;
};

template <class T>
T Stream::read() const
{
	T value;
	read(&value, sizeof(T), 1);
	return value;
}

template <class T>
T* Stream::read(unsigned int count) const
{
	T* value = new T[count];
	read(value, sizeof(T), count);
	return value;
}

template <class T>
void Stream::write(T value) const
{
	write(&value, sizeof(T), 1);
}

template <class T>
void Stream::write(T* value, unsigned int count) const
{
	write(value, sizeof(T), count);
}