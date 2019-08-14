#include "state_propagator.h"

#include <math.h>

#include <FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t xProfSem = NULL;

odometry_t predictorOdometryInput;

volatile int state[4];
volatile int accelerations[2];
static int update_mat[4][4] = { { 1, 0, 100, 0 }, { 0, 1, 0, 100 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

void doStateUpdate()
{
	if (state[0] >= 1000)
	{
		state[0] = 0;
	}
	if (state[1] >= 1000)
	{
		state[1] = 0;
	}
	// calculate measurement vector
	int measurements[4];
	int accel_x = 0;
	int accel_y = 0;

	if (predictorOdometryInput.type == UNIT_MM)
	{
		accel_x = predictorOdometryInput.acceleration[0];
		accel_y = predictorOdometryInput.acceleration[1];
	}
	/*else
	{
		// get floating point numbers
		//volatile float facc_r = *reinterpret_cast<volatile float*>(&predictorOdometryInput.acceleration[0]);
		//volatile float facc_w = *reinterpret_cast<volatile float*>(&predictorOdometryInput.acceleration[1]);
		// convert to mm
		accel_x = predictorOdometryInput.acceleration[0] * cos(predictorOdometryInput.acceleration[1]);
		accel_y = predictorOdometryInput.acceleration[0] * sin(predictorOdometryInput.acceleration[1]);
	}*/

	measurements[0] = 5000 * accel_x;
	measurements[1] = 5000 * accel_y;
	measurements[2] = 100 * accel_x;
	measurements[3] = 100 * accel_y;

	// update the state variable
	for (int row = 0; row < 4; row++)
	{
		int tempstate = 0;
		for (int col = 0; col < 4; col++)
		{
			tempstate += update_mat[row][col] * state[col];

		}
		state[row] = tempstate + measurements[row];
	}
}

void localizationTask(void* pv)
{
	// Initialize IPC
	if (xProfSem == NULL)
	{
		xProfSem = xSemaphoreCreateBinary();
	}

	state[0] = 0;
	state[1] = 0;
	state[2] = 1;
	state[3] = 2;

	while (1)
	{
		// Wait until next processing cycle
		if (xSemaphoreTake(xProfSem, portMAX_DELAY) != pdTRUE)
			continue;

		doStateUpdate();
	}
}
