#include "MDR32Fx.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"

int main() {
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
    PORT_InitTypeDef PortInitStructure;
    PORT_StructInit(&PortInitStructure);
    PortInitStructure.PORT_Pin = PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 |
                                 PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7;
    PortInitStructure.PORT_MODE = PORT_MODE_DIGITAL;
    PortInitStructure.PORT_FUNC = PORT_FUNC_PORT;
    PortInitStructure.PORT_OE = PORT_OE_OUT;
    PORT_Init(MDR_PORTA, &PortInitStructure);

    while (1) {
        PORT_Write(MDR_PORTA, 0x01);
        for (volatile int i = 0; i < 50000; i++);
        PORT_Write(MDR_PORTA, 0x02);
        for (volatile int i = 0; i < 50000; i++);
        PORT_Write(MDR_PORTA, 0x04);
        for (volatile int i = 0; i < 50000; i++);
        PORT_Write(MDR_PORTA, 0x08);
        for (volatile int i = 0; i < 50000; i++);
    }
}