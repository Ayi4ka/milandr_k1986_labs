#include "MDR32Fx.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"

int main() {
    MDR_RST_CLK->PER_CLOCK |= (1<<21) | (1<<17) | (1<<24);
    MDR_PORTA->OE |= 0xFF;
    MDR_PORTA->FUNC &= ~0xFFFF;
    MDR_PORTA->ANALOG |= 0xFF;
    MDR_PORTA->PWR |= 0xFFFF;

    MDR_ADC->ADC1_CFG |= (1<<4);
    MDR_ADC->ADC1_CFG |= (1<<12)|(1<<13);
    MDR_ADC->ADC1_CFG |= (1<<0);
    MDR_ADC->ADC1_CFG |= (1<<1);

    uint32_t status;
    uint16_t result;

    while (1) {
        do {
            status = MDR_ADC->ADC1_STATUS & (1<<2);
        } while (!status);

        result = MDR_ADC->ADC1_RESULT & 0x0FFF;
        MDR_PORTA->RXTX = result >> 4;
        MDR_ADC->ADC1_CFG |= (1<<1);
    }
}