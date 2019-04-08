/*
 * TTTProfConfig.h
 *
 *  Created on: 28.03.2019
 *      Author: Tim
 */

#ifndef TTTPROFCONFIG_H_
#define TTTPROFCONFIG_H_

/* Defines the maximum packet payload size */
#define tttConfig_MAX_RECV_PACKET_SIZE		128

#define tttConfigMAX_TASK_NAME_LEN			16
/* The task to profile */
#define tttConfig_PROF_TASK_FUNCTION		localizationTask
#define tttConfig_PROF_TASK_NAME			"target"
#define tttConfig_PROF_TASK_STACKSIZE		128

/* Serial driver */
#define tttConfig_SERIAL_TIMEOUT			portMAX_DELAY

/* Communication id's */

#define tttConfig_COM_ID_APP				10
#define tttConfig_COM_ID_TARGET				20
#define tttConfig_COM_ID_PROFILER			30

#endif /* TTTPROFCONFIG_H_ */
