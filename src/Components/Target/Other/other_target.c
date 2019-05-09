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


volatile int32_t array2[MAXROWS][MAXCOLS] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 10, 11, 12, 13 }, { 14, 15, 16, 17 }, };
volatile int32_t array1[MAXROWS][MAXCOLS] = { { -1, 2, -3, 4 }, { -5, 6, -7, 8 }, { -10, -11, 12, 13 }, { 1400, -4598,
		-257844165, 17 }, };

volatile int sensorValues[256];

volatile int32_t lengthInfo[2];

SemaphoreHandle_t xTargetSemaphore = NULL;
void productMatrix(volatile int array1[][MAXCOLS], volatile int array2[][MAXCOLS], int array3[][MAXCOLS], int m, int n)
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

void transposeMatrix(volatile int32_t input[][MAXCOLS], int32_t result[][4])
{
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			result[i][j] = input[i][j];
		}
	}
}

void matrixAdd(int matrixA[][MAXCOLS], int matrixB[][MAXCOLS], int result[][MAXCOLS], int m, int n)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = matrixA[i][j] + matrixB[i][j];
		}
	}
}

int arrayAverage(volatile int* array, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += array[i];
	}

	return sum / size;
}

void bubblesort(volatile int* array, int size)
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
				//array.swap(i, i+1)
				array[i] = nextElement;
				array[i+1] = currentElement;
				newn = i+1;
			} // ende if
		} // ende for
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

void swap(volatile int32_t* a, volatile int32_t* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


volatile float length;
void run_task()
{
	//length = getLength(lengthInfo[0], lengthInfo[1]);

	//swap(&array2[1][0], &array2[0][1]);
	int32_t array3[4][4];

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
