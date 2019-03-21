/*
 * Target.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef TARGET_H_
#define TARGET_H_

#include <stdint.h>
#include "Commandable.h"

class Target : public Commandable<128>
{
public:
	virtual void initialize() = 0;

	virtual void startProcessCycle() = 0;
	virtual void waitForCycleToEnd() = 0;
};


#endif /* TARGET_H_ */
