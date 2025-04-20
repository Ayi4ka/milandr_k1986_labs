#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_timer.h"

int main() {
    MDR_RST_CLK->HS_CONTROL = (1<<0);
    while (!(MDR_RST_CLK->CLOCK_STATUS & (1<<2)));
    MDR_RST_CLK->CPU_CLOCK |= (1<<1);
    MDR_RST_CLK->PLL_CONTROL |= (1<<11)|(1<<8);
    MDR_RST_CLK->PLL_CONTROL |= (1<<2);
    while (!(MDR_RST_CLK->CLOCK_STATUS & (1<<1)));
    MDR_RST_CLK->CPU_CLOCK |= (1<<8)|(1<<7)|(1<<4)|(1<<2)|(1<<1);

    MDR_RST_CLK->PER_CLOCK |= (1<<14);
    MDR_TIMER1->CNTRL = 0x00000000;
    MDR_TIMER1->CNT = 0x00000000;
    MDR_TIMER1->PSG = 0x00009C3F;
    MDR_TIMER1->ARR = 0x00000064;
    MDR_TIMER1->CNTRL = 0x00000001;

    MDR_RST_CLK->PER_CLOCK |= (1<<21);
    MDR_PORTA->OE |= 0xFF;
    MDR_PORTA->FUNC &= ~0xFFFF;
    MDR_PORTA->ANALOG |= 0xFF;
    MDR_PORTA->PWR |= 0xFFFF;

    int check = 0, now = 0;
    int OutputValue = 0xFF;
    MDR_PORTA->RXTX = OutputValue;

    while (1) {
        now = MDR_TIMER1->CNT;
        if (now == 100 && now != check) {
            OutputValue -= 2;
            MDR_PORTA->RXTX = OutputValue;
        }
        check = now;
    }
}