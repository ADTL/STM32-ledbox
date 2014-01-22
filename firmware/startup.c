/**
 * Startup code of firmware
 */
#include "stm32f10x.h"
#include "core_cm3.h"
#include "main.h"
void SystemInit(void);
void main(void);
/* provided by linker script */
extern unsigned long _estack;
extern unsigned long __text_end;
extern unsigned long __data_start;
extern unsigned long __data_end;
extern unsigned long __bss_start;
extern unsigned long __bss_end;
/* reset handler */
void Reset_Handler(void) {
    /* presetup bss and data sections */
    unsigned long *src;
    unsigned long *dest;
    
    src = &__text_end;
    dest = &__data_start;
    if (src != dest)
        while(dest < &__data_end)
            *(dest++) = *(src++);
 
    dest = &__bss_start;
    while(dest < &__bss_end)
        *(dest++) = 0;
    
    SystemInit();
    main();
}

/* table of Cortex vectors */
void *vector_table[] __attribute__ ((section(".vectors"))) = {
    &_estack,
    Reset_Handler,      /*!#0 cortex-m3 reset interrupt begin code of this */
    0,                  /*!#1 cortex-m3 non maskable interrupt */
    0,                  /*!#2 cortex-m3 hardware fault interrupt */
    0,                  /*!#3 cortex-m3 memory management interrupt */
    0,                  /*!#4 cortex-m3 bus fault interrupt */
    0,                  /*!#5 cortex-m3 usage fault interrupt */
    0,                  /*!#6 reserved */
    0,                  /*!#7 reserved */
    0,                  /*!#8 reserved */
    0,                  /*!#9 reserved */
    0,                  /*!#10 cortex-m3 system service interrupt */
    0,                  /*!#11 cortex-m3 debug monitor interrupt */
    0,                  /*!#12 reserved */
    0,                  /*!#13 cortex-m3 penable request for system service interrupt */
    0,                  /*!#14 cortex-m3 system tick timer interrupt */
    0,                  /*!%0 window watchdog interrupt */
    0,                  /*!%1 PVD through EXTI line detection interrupt */
    0,                  /*!%2 tamper adn timestamp through EXTI interrupt */
    0,                  /*!%3 RTC wakeup through EXTI interrupt */
    0,                  /*!%4 flash global interrupt */
    0,                  /*!%5 RCC global interrupt */
    0,/*EXTI_L0_Handler,    /*!%6 EXTI line0 interrupt */
    0,                  /*!%7 EXTI line1 interrupt */
    0,                  /*!%8 EXTI line2 interrupt */
    0,                  /*!%9 EXTI line3 interrupt */
    0,                  /*!%10 EXTI line4 interrupt */
    0,                  /*!%11 DMA1 channel 1 global interrupt */
    0,                  /*!%12 DMA1 channel 2 global interrupt */
    0,                  /*!%13 DMA1 channel 3 global interrupt */
    0,                  /*!%14 DMA1 channel 4 global interrupt */
    0,                  /*!%15 DMA1 channel 5 global interrupt */
    0,                  /*!%16 DMA1 channel 6 global interrupt */
    0,                  /*!%17 DMA1 channel 7 global interrupt */
    0,                  /*!%18 ADC1 global interrupt */
    0,                  /*!%19 reserved */
    0,                  /*!%20 reserved */
    0,                  /*!%21 reserved */
    0,                  /*!%22 reserved */
    0,                  /*!%23 EXTI line[9:5] interrupts */
    0,                  /*!%24 TIM1 break and TIM15 global interrupt */
    0,                  /*!%25 TIM1 update and TIM16 global interrupt */
    0,                  /*!%26 TIM1 trigger and commutation and TIM17 global interrupt */
    0,                  /*!%27 TIM1 capture compare interrupt */
    0,                  /*!%28 TIM2 global interrupt */
    0,                  /*!%29 TIM3 global interrupt */
    0,                  /*!%30 TIM4 global interrupt */
    0,                  /*!%31 I2C1 event interrupt */
    0,                  /*!%32 I2C1 error interrupt */
    0,                  /*!%33 I2C2 event interrupt */
    0,                  /*!%34 I2C2 error interrupt */
    0,                  /*!%35 SPI1 global interrupt */
    0,                  /*!%36 SPI2 global interrupt */
    0,                  /*!%37 USART1 global interrupt */
    0,                  /*!%38 USART2 global interrupt */
    0,                  /*!%39 USART3 global interrupt */
    0,                  /*!%40 EXTI line[15:10] interrupts */
    0,                  /*!%41 RTC alarm through EXTI line interrupt */
    0,                  /*!%42 HDMI-CEC interrupt */
    0,                  /*!%43 reserved */
    0,                  /*!%44 reserved */
    0,                  /*!%45 reserved */
    0,                  /*!%46 reserved */
    0,                  /*!%47 reserved */
    0,                  /*!%48 reserved */
    0,                  /*!%49 reserved */
    0,                  /*!%50 reserved */
    0,                  /*!%51 reserved */
    0,                  /*!%52 reserved */
    0,                  /*!%53 reserved */
    0,                  /*!%54 TIM6 and DAC underrun interrupt */
    0,                  /*!%55 TIM7 interrupt */
};
