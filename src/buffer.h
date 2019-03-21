/*
 * buffer.h
 *
 *  Created on: 21.03.2019
 *      Author: Tim
 */

#ifndef BUFFER_H_
#define BUFFER_H_

template<class T>
class buffer_t
{
protected:
	T* p_data;
	uint32_t size;
	uint32_t index;
	uint32_t overflowCount;

public:
	buffer_t()
			: buffer_t(nullptr, 0)
	{

	}

	buffer_t(T* buffer, uint32_t bufferSize)
	{
		assignBuffer(buffer, bufferSize);
		index = 0;
		overflowCount = 0;
	}

	void assignBuffer(T* buffer, uint32_t bufferSize)
	{
		p_data = buffer;
		size = bufferSize;
	}

	void assignBuffer(buffer_t* buffer)
	{
		p_data = buffer->p_data;
		size = buffer->size;
	}

	bool isFull()
	{
		return (index >= size);
	}

	void push_back(const T& data)
	{
		if (p_data == nullptr)
			return;

		if (isFull())
		{
			overflowCount++;
			return;
		}

		p_data[index++] = data;
	}

	T& operator[](uint32_t idx)
	{
		return p_data[idx];
	}

	uint32_t getCapacity()
	{
		return size;
	}

	uint32_t getCount()
	{
		return index;
	}

	void clear()
	{
		index = 0;
		overflowCount = 0;
	}
};

#endif /* BUFFER_H_ */
