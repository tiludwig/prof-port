/*
 * cm3_dwt.h
 *
 *  Created on: 24.03.2019
 *      Author: Tim
 */

#ifndef CORE_EXECUTIONTIMER_CM3_DWT_H_
#define CORE_EXECUTIONTIMER_CM3_DWT_H_

#include <stm32f10x.h>
#include <stdint.h>

struct DWT_TypeDef
{
	__IO uint32_t CTRL;
	__IO uint32_t CYCCNT;
	__IO uint32_t CPICNT;
	__IO uint32_t EXCCNT;
	__IO uint32_t SLEEPCNT;
	__IO uint32_t LSUCNT;
	__IO uint32_t FOLDCNT;
};

#define DWT_BASE		((uint32_t)0xE0001000)
#define DWT				((DWT_TypeDef *) DWT_BASE)

#define DWT_CTRL_CYCCNTENA	((uint32_t) 1U << 0)
#define DWT_CTRL_FOLDEVTENA	((uint32_t) 1U << 21)
#define DWT_CTRL_LSUEVTENA  ((uint32_t) 1U << 20)
#define DWT_CTRL_SLEEPEVTENA	((uint32_t) 1U << 19)
#define DWT_CTRL_EXCEVTENA	((uint32_t) 1U << 18)
#define DWT_CTRL_CPIEVTENA	((uint32_t) 1U << 16)

#endif /* CORE_EXECUTIONTIMER_CM3_DWT_H_ */
