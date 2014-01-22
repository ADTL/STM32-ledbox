/**
 * System init of firmware
 */
#include "stm32f10x.h"
#define CIR_FLAGS RCC_CIR_CSSC | RCC_CIR_PLLRDYC | RCC_CIR_HSERDYC | \
RCC_CIR_HSIRDYC | RCC_CIR_LSERDYC | RCC_CIR_LSIRDYC
/* system init function */
void SystemInit(void) {
    /* enable HSI - hight speed interal clock */
    if ((RCC->CR & RCC_CR_HSION) == 0)
        RCC->CR |= RCC_CR_HSION;
    /* disable all interrupts and clear penging bits */
    RCC->CIR = CIR_FLAGS;
    /* reset CGGR2 register */
    RCC->CFGR2 = 0x0;
    /* disable all interrupts and clear penging bits */
    RCC->CIR = CIR_FLAGS;
}
