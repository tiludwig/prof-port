/*
 * buffer.h
 *
 *  Created on: 21.03.2019
 *      Author: Tim
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>

/*
 * Name:	buffer_t
 *
 * Purpose: Implements a wrapper to a c-array.
 *
 * Notes:	The index is not checked against the buffer's boundaries.
 */
template<class T>
class buffer_t
{
protected:
	T* p_data;
	uint32_t size;
	uint32_t index;
	uint32_t overflowCount;

public:
	/*
	 * Name:	buffer_t
	 *
	 * Purpose: Constructs a new instance of the buffer_t wrapper.
	 * 			The internal buffer is initialized to be invalid.
	 */
	buffer_t()
			: buffer_t(nullptr, 0)
	{

	}

	/*
	 * Name:	buffer_t
	 *
	 * Purpose: Constructs a new instance of the buffer_t wrapper.
	 * 			The internal buffer is initialized with the provided memory
	 * 			location.
	 */
	buffer_t(T* buffer, uint32_t bufferSize)
	{
		assignBuffer(buffer, bufferSize);
		index = 0;
		overflowCount = 0;
	}

	/*
	 * Name:	assignBuffer
	 *
	 * Purpose: Assigns this buffer a memory location to operate on.
	 */
	void assignBuffer(T* buffer, uint32_t bufferSize)
	{
		p_data = buffer;
		size = bufferSize;
	}

	/*
	 * Name:	assignBuffer
	 *
	 * Purpose: Assigns this buffer a memory location to operate on.
	 */
	void assignBuffer(buffer_t* buffer)
	{
		p_data = buffer->p_data;
		size = buffer->size;
	}

	/*
	 * Name:	isFull
	 *
	 * Purpose: Checks if the buffer is full.
	 *
	 * Returns:	True, if the buffer is full. False otherwise.
	 */
	bool isFull()
	{
		return (index >= size);
	}

	/*
	 * Name:	push_back
	 *
	 * Purpose: Adds data to the buffer. If the buffer is full the overflow
	 * 			counter will be increased - the data is NOT added to the
	 * 			buffer. If there was no memory location assigned to the buffer
	 * 			this operation will return immediately.
	 *
	 * Notes:	The assignment operator of the data is used.
	 */
	void push_back(T& data)
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

	/*
	 * Name:	push_back
	 *
	 * Purpose: Adds data to the buffer. If the buffer is full the overflow
	 * 			counter will be increased - the data is NOT added to the
	 * 			buffer. If there was no memory location assigned to the buffer
	 * 			this operation will return immediately.
	 *
	 * Notes:	The assignment operator of the data is used.
	 */
	void push_back(T&& data)
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

	/*
	 * Name:	operator[]
	 *
	 * Purpose: Allows indexed access to the buffer's data.
	 *
	 * Notes:	The index is not checked against the buffer's boundaries.
	 */
	T& operator[](uint32_t idx)
	{
		return p_data[idx];
	}

	/*
	 * Name:	getCapacity
	 *
	 * Purpose: Gets the capacity of the buffer.
	 */
	uint32_t getCapacity()
	{
		return size;
	}

	/*
	 * Name:	getCount
	 *
	 * Purpose: Gets the amount of data in the buffer.
	 */
	uint32_t getCount()
	{
		return index;
	}

	/*
	 * Name:	clear
	 *
	 * Purpose: Resets the buffer's write index and overflow count to zero.
	 */
	void clear()
	{
		index = 0;
		overflowCount = 0;
	}
};

#endif /* BUFFER_H_ */
