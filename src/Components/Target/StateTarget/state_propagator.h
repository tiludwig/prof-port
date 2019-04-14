/*
 * state_propagator.h
 *
 *  Created on: 27.03.2019
 *      Author: Tim
 */

#ifndef COMPONENTS_TARGET_STATETARGET_STATE_PROPAGATOR_H_
#define COMPONENTS_TARGET_STATETARGET_STATE_PROPAGATOR_H_

extern volatile int state[4];
extern volatile int accelerations[2];


enum OdometryType_t
{
	UNIT_MM = 0,
	UNIT_POLAR,
};

struct odometry_t
{
	volatile OdometryType_t type;
	volatile int acceleration[2];
};

extern odometry_t predictorOdometryInput;

void localizationTask(void* pv);


#endif /* COMPONENTS_TARGET_STATETARGET_STATE_PROPAGATOR_H_ */
