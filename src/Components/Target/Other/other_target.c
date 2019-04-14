/*
 * other_target.c
 *
 *  Created on: 14.04.2019
 *      Author: Tim
 */

#include <FreeRTOS.h>
#include <semphr.h>

#define MAXROWS 10
#define MAXCOLS 10

void productMatrix(int array1[][MAXCOLS], int array2[][MAXCOLS], int array3[][MAXCOLS], int m, int n);

volatile int array1[MAXROWS][MAXCOLS] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 10, 11, 12, 13 }, { 14, 15, 16, 17 }, };
volatile int array2[MAXROWS][MAXCOLS] = { { -1, 2, -3, 4 }, { -5, 6, -7, 8 }, { -10, -11, 12, 13 },
		{ 1400, -4598, -257844165, 17 }, };

SemaphoreHandle_t xTargetSemaphore = NULL;
void productMatrix(int array1[][MAXCOLS], int array2[][MAXCOLS], int array3[][MAXCOLS], int m, int n)
{

	int i, j, k;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			array3[i][j] = 0;
			for (k = 0; k < n; k++)
			{
				array3[i][j] = array3[i][j] + array1[i][k] * array2[k][j];
			}
		}
	}
}

void run_task()
{

	int m = 4;
	int n = 4;

	volatile int array3[MAXROWS][MAXCOLS];
	productMatrix(array1, array2, array3, m, n);
}

void targetTask(void* pv)
{
// Initialize IPC
	if (xTargetSemaphore == NULL)
	{
		xTargetSemaphore = xSemaphoreCreateBinary();
	}

	while (1)
	{
		// Wait until next processing cycle
		if (xSemaphoreTake(xTargetSemaphore, portMAX_DELAY) != pdTRUE)
			continue;

		run_task();
	}
}
