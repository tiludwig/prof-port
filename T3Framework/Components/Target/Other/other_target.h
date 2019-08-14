/*
 * other_target.h
 *
 *  Created on: 14.04.2019
 *      Author: Tim
 */

#ifndef COMPONENTS_TARGET_OTHER_TARGET_H_
#define COMPONENTS_TARGET_OTHER_TARGET_H_

#include <stdint.h>

extern volatile int32_t sensorValues[256];
extern volatile int32_t array2[4][4];
extern volatile int32_t lengthInfo[2];

extern "C" void targetTask(void* pv);

#endif /* COMPONENTS_TARGET_OTHER_TARGET_H_ */
