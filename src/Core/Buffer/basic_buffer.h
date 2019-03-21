/*
 * basic_buffer.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef BASIC_BUFFER_H_
#define BASIC_BUFFER_H_

#include <stdint.h>

template<class T, uint32_t N>
class basic_buffer
{
private:
	T data[N];
	uint32_t size;
	uint32_t index;
	uint32_t overflowCount;
public:
	basic_buffer()
	{
		size = N;
		index = 0;
		overflowCount = 0;
	}

	void clear()
	{
		index = 0;
		overflowCount = 0;
	}

	void push_back(const T& data)
	{
		if (isFull())
		{
			overflowCount++;
			return;
		}

		this->data[index++] = data;
	}

	bool isFull()
	{
		return (index >= size);
	}

	T& operator[](uint32_t idx)
	{
		return data[idx];
	}

	T* getMemAddress()
	{
		return data;
	}

	uint32_t getSize()
	{
		return size;
	}
};

#endif /* BASIC_BUFFER_H_ */
