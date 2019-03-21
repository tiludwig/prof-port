/*
 * IComLink.hpp
 *
 *  Created on: 19.03.2019
 *      Author: Tim
 */

#ifndef COMLINK_ICOMLINK_HPP_
#define COMLINK_ICOMLINK_HPP_

#include <stdint.h>

class IComLink
{
public:
	virtual bool initialize() = 0;

	virtual void write(uint8_t* data, uint32_t count) = 0;
	virtual uint8_t read() = 0;
};
#endif /* COMLINK_ICOMLINK_HPP_ */
