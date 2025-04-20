#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_timer.h"

int main() {
    MDR_RST_CLK->HS_CONTROL |= (1<<0);
    while (!(MDR_RST_CLK->CLOCK_STATUS & (1<<2)));
    MDR_RST_CLK->CPU_CLOCK |= (1<<1);
    MDR_RST_CLK->PLL_CONTROL |= (1<<11)|(1<<8);
    MDR_RST_CLK->PLL_CONTROL |= (1<<2);
    while (!(MDR_RST_CLK->CLOCK_STATUS & (1<<1)));
    MDR_RST_CLK->CPU_CLOCK |= (1<<8)|(1<<7)|(1<<4)|(1<<2)|(1<<1);

    MDR_RST_CLK->PER_CLOCK |= (1<<21);
    MDR_RST_CLK->PER_CLOCK |= (1<<15);

    MDR_PORTA->FUNC |= (1<<6)|(1<<7);
    MDR_PORTA->OE |= (1<<3);
    MDR_PORTA->ANALOG |= (1<<3);
    MDR_PORTA->PWR |= (1<<6)|(1<<7);

    MDR_TIMER2->CNTRL = 0x00000000;
    MDR_TIMER2->CNT = 0;
    MDR_TIMER2->PSG = 9;
    MDR_TIMER2->ARR = 999;
    MDR_TIMER2->CCR2 = 200;
    MDR_TIMER2->CH2_CNTRL |= (1<<10)|(1<<11);
    MDR_TIMER2->CH2_CNTRL1 |= (1<<0)|(1<<3);
    MDR_TIMER2->CNTRL = 0x00000001;

    while (1);
}