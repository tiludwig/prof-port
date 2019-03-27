/*
 ******************************************************************************
 File:     main.cpp
 Info:     Generated by Atollic TrueSTUDIO(R) 9.0.0   2019-03-19

 The MIT License (MIT)
 Copyright (c) 2018 STMicroelectronics


 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 ******************************************************************************
 */

/* Includes */
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <Components/Target/StateTarget/state_propagator.h>
#include <application.h>
#include <Utility/ui-task/ui-task.h>
#include <Utility/idle-task/idle-task.h>

TaskHandle_t xProfTask = NULL;


int main()
{
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);

	xTaskCreate(uiTask, "ui", 128, NULL, 1, NULL);
	xTaskCreate(appTask, "perf-app", 512, NULL, 2, NULL);
	xTaskCreate(localizationTask, "target", 128, NULL, 3, &xProfTask);
	xTaskCreate(idleTask, "idle", 128, NULL, 0, NULL);
	xPortStartScheduler();

	while (1)
	{

	}
	return 0;
}
