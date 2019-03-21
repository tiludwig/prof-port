/*
 * IComProtocol.hpp
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef COMLINK_COMPROTOCOL_ICOMPROTOCOL_HPP_
#define COMLINK_COMPROTOCOL_ICOMPROTOCOL_HPP_


class IComProtocol
{
public:
	virtual bool isPacketComplete() = 0;
	virtual void processByte(char data) = 0;
	virtual void resetReceiver() = 0;
};


#endif /* COMLINK_COMPROTOCOL_ICOMPROTOCOL_HPP_ */
