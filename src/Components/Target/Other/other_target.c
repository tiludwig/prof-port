/*
 * other_target.c
 *
 *  Created on: 14.04.2019
 *      Author: Tim
 */

#include <FreeRTOS.h>
#include <semphr.h>
#include <math.h>

#define MAXROWS 4
#define MAXCOLS 4


#include "mat_mul.h"
#include "mat_transpose.h"
#include "simple_swap.h"

volatile int32_t lengthInfo[2];

SemaphoreHandle_t xTargetSemaphore = NULL;

volatile int32_t array2[MAXROWS][MAXCOLS] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 10, 11, 12, 13 }, { 14, 15, 16, 17 }, };
volatile int32_t array1[MAXROWS][MAXCOLS] = { { -1, 2, -3, 4 }, { -5, 6, -7, 8 }, { -10, -11, 12, 13 }, { 1400, -4598,
		-257844165, 17 }, };

volatile int32_t unsorted_array[32];


int arrayAverage(volatile int* array, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += array[i];
	}

	return sum / size;
}

void bubblesort(volatile int32_t* array, int size)
{
	int n = size;
	do
	{
		int newn = 1;
		for (int i=0; i<n-1; ++i)
		{
			int currentElement = array[i];
			int nextElement = array[i+1];

			if (currentElement > nextElement)
			{
				array[i] = nextElement;
				array[i+1] = currentElement;
				newn = i+1;
			}
		}
		n = newn;
	}while (n > 1);
}

volatile int averageSensorValue;

float getLength(float a, float b)
{
	return a*sin(b) + b*cos(a);
}


int sum(int a, int b)
{
	return a + b;
}

volatile float length;
void run_task()
{
	//array1[0][0] = sum(array2[1][0], array2[0][1]);
	//length = getLength(lengthInfo[0], lengthInfo[1]);

	//swap(&array2[1][0], &array2[0][1]);
	int32_t array3[4][4];
	//bubblesort(unsorted_array, 32);
	productMatrix(array1, array2, array3, 4, 4);
	//transposeMatrix(array2, array3);
	//matrixAdd(array1, array2, array3, m, n);
	//averageSensorValue = arrayAverage(sensorValues, 256);
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
