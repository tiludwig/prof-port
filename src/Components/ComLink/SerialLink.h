/*
 * SerialLink.h
 *
 *  Created on: 19.03.2019
 *      Author: Tim
 */

#ifndef COMLINK_SERIALLINK_H_
#define COMLINK_SERIALLINK_H_

#include <Components/ComLink/IComLink.hpp>
#include <stdint.h>

class SerialLink: public IComLink
{
public:
	virtual ~SerialLink();

	virtual bool initialize();

	virtual void write(const uint8_t* data, uint32_t count);
	virtual uint8_t read();
};

#endif /* COMLINK_SERIALLINK_H_ */
