/**
 * Main code of firmware
 */
#include "stm32f10x.h"
#include "main.h"
#include "fsrand.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
/* Global vars */
uint32_t tred, tgreen, tblue; // target colors
float red, green, blue;    // now colors
float delta_red, delta_green, delta_blue; // delta colors
unsigned int time;
/* Setup peripheral */
void setup_periph(void) {
    /* setup i/o port */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
    /** disable jtag pins but swd is enable */
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
    /** setup leds pins */
    GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
    GPIOA->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1;
    GPIOA->CRL |= GPIO_CRL_MODE6_0 | GPIO_CRL_MODE7_0;
    GPIOB->CRL &= ~(GPIO_CRL_CNF0);
    GPIOB->CRL |= GPIO_CRL_CNF0_1;
    GPIOB->CRL |= GPIO_CRL_MODE0_0;
    /* setup TIM3 base timer */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->PSC = 1 - 1;
    TIM3->ARR = 511;
    /* setup TIM3 compare block */
    /** setup CC1..2 as output */
    TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
    /** setup CC1..2 to PWM mode 1 */
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 |
        TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
    /** setup CC3 as output */
    TIM3->CCMR2 &= ~(TIM_CCMR2_CC3S);
    /** setup CC3 to PWM mode 1 */
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
    /** setup value to compare registers 1..3 */
    TIM3->CCR1 = 0;
    TIM3->CCR2 = 0;
    TIM3->CCR3 = 0;
    /** setup channels 1..3 to corresponding output pin */
    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;
    /* enable TIM3 */
    TIM3->CR1 |= TIM_CR1_CEN;
}
/* settings colors */
void set_blue(unsigned char color)
{
    TIM3->CCR1 = color * 227 / 1000;
}
void set_green(unsigned char color)
{
    TIM3->CCR2 = color * 2;
}
void set_red(unsigned char color)
{
    TIM3->CCR3 = color * 141 / 1000;
}
/* generate target color */
void generate_target_color(void)
{
    tred = frand();
    tgreen = frand();
    tblue = frand();
    tred &= 0xff;
    tgreen &= 0xff;
    tblue &= 0xff;
}
/* delay function */
void delay_ms(int delay)
{
    volatile int counter = delay * 4000;
    while(counter--);
}
/* Main function */
void main(void) {
    uint32_t temp1, temp2, temp3, temp4;
    /* setup peripheral */
    setup_periph();
    fsrand(1);
    /* set test white color */
    set_red(0);
    set_green(0);
    set_blue(0);
    /* infinity loop */
    while (1) {
        do {
            generate_target_color();
            temp1 = abs(tred - tgreen);
            temp2 = abs(tred - tblue);
            temp3 = abs(tgreen - tblue);
        } while ((temp1 < 150) && (temp2 < 150) && (temp3 < 150));
        
        if (frand() < 13100) {
            do {
                temp4 = frand() & 0x000f;
            } while ((temp4 == 0) || (temp4 > 3));
            
            if (temp4 == 1) {
                do {
                    temp4 = frand() & 0x0fff;
                } while ((temp4 == 0) || (temp4 > 3276));
                
                tred = ceil((float)temp4 / 32768 * tred);
            }
            
            if (temp4 == 2) {
                do {
                    temp4 = frand() & 0x0fff;
                } while ((temp4 == 0) || (temp4 > 3276));
                
                tgreen = ceil((float)temp4 / 32768 * tgreen);
            }
            
            if (temp4 == 3) {
                do {
                    temp4 = frand() & 0x0fff;
                } while ((temp4 == 0) || (temp4 > 3276));
                
                tblue = ceil((float)temp4 / 32768 * tblue);
            }
        }
        
        delta_red = (float)(tred - red) / 255;
        delta_green = (float)(tgreen - green) / 255;
        delta_blue = (float)(tblue - blue) / 255;
        
        do {
            temp4 = frand() & 0x00ff;
        } while ((temp4 < 50) || (temp4 > 100));
        
        time = ceil(((float) temp4 / 255) * 20);
        
        do {
            if (tred != ceil(red))
                red += delta_red;
            if (tgreen != ceil(green))
                green += delta_green;
            if (tblue != ceil(blue))
                blue += delta_blue;
            set_blue(ceil(blue));
            set_green(ceil(green));
            set_red(ceil(red));            
            delay_ms(time);
        } while ((tred != ceil(red)) || (tgreen != ceil(green)) || (tblue != ceil(blue)));
        
        delay_ms(time * 50);
    }
}
