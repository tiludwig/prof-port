#include <FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t xProfSem = NULL;

volatile int state[4];
static int update_mat[4][4] = { { 1, 0, 100, 0 }, { 0, 1, 0, 100 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

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

		// update the state variable
		for (int row = 0; row < 4; row++)
		{
			int tempstate = 0;
			for (int col = 0; col < 4; col++)
			{
				tempstate += update_mat[row][col] * state[col];
			}
			state[row] = tempstate;
		}
	}
}
