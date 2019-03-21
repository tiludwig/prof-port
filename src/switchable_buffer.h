/*
 * switchable_buffer.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef SWITCHABLE_BUFFER_H_
#define SWITCHABLE_BUFFER_H_

template<class T>
class switchable_buffer
{
private:
	T* internal_buffer;
	uint32_t size;
	uint32_t index;
	uint32_t overflowCounter;
public:
	switchable_buffer()
	{
		assignBuffer(nullptr, 0);
		index = 0;
	}

	switchable_buffer(T* buffer, uint32_t size)
	{
		assignBuffer(buffer, size);
		index = 0;
	}

	void clear()
	{
		overflowCounter = 0;
		index = 0;
	}

	void assignBuffer(T* buffer, uint32_t size)
	{
		internal_buffer = buffer;
		this->size = size;
	}

	T* getBufferAddress()
	{
		return internal_buffer;
	}

	T& operator[](uint32_t index)
	{
		return internal_buffer[index];
	}

	bool isFull()
	{
		return (index >= size);
	}

	void push_back(const T& data)
	{
		if(internal_buffer == nullptr)
			return;

		if(isFull())
		{
			overflowCounter++;
			return;
		}

		internal_buffer[index++] = data;
	}

	uint32_t getCapacity()
	{
		return size;
	}

	uint32_t getCount()
	{
		return index;
	}
};

#endif /* SWITCHABLE_BUFFER_H_ */
