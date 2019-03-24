/*
 * basic_buffer.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef BASIC_BUFFER_H_
#define BASIC_BUFFER_H_

#include <stdint.h>

/*
 * Name:		basic_buffer
 *
 * Purpose: 	Implements a simple buffer with configurable size and overflow
 * 				counters. It also prevents writes to a full buffer.
 *
 * Notes:		The implementation can not prevent a user from accessing a buffer
 * 				element that is out of bounds. This is because exceptions are
 * 				disabled on the cortex-m3 for runtime performance.
 * 				Calling code can check it's index by comparing it against the
 * 				buffer's size.
 */
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

	/*
	 * Name:	push_back
	 *
	 * Purpose: Adds data to the buffer. If the buffer is full the overflow
	 * 			counter will be increased - the data is NOT added to the
	 * 			buffer.
	 *
	 * Notes:	The assignment operator of the data is used.
	 */
	void push_back(const T& data)
	{
		if (isFull())
		{
			overflowCount++;
			return;
		}

		this->data[index++] = data;
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
	 * Name:	operator[]
	 *
	 * Purpose: Allows indexed access to the buffer's data.
	 *
	 * Notes:	The index is not checked against the buffer's boundaries.
	 */
	T& operator[](uint32_t idx)
	{
		return data[idx];
	}

	/*
	 * Name:	getMemAddress
	 *
	 * Purpose: Returns the memory address of the first element in the buffer's
	 * 			data array.
	 */
	T* getMemAddress()
	{
		return data;
	}

	/*
	 * Name:	getSize
	 *
	 * Purpose: Gets the size of the buffer
	 */
	uint32_t getSize()
	{
		return size;
	}
};

#endif /* BASIC_BUFFER_H_ */
