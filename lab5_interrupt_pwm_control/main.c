#include "MDR32Fx.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"

void Timer3_IRQHandler(void) {
    TIMER_ClearITPendingBit(MDR_TIMER3, TIMER_STATUS_CNT_ARR);
    static int compare = 6500;
    if (compare > 0) {
        compare -= 10;
        TIMER_SetChnCompare(MDR_TIMER2, TIMER_CHANNEL2, compare);
    }
}

int main() {
    RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER2, ENABLE);
    RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER3, ENABLE);

    TIMER_BRGInit(MDR_TIMER2, TIMER_HCLKdiv1);
    TIMER_BRGInit(MDR_TIMER3, TIMER_HCLKdiv1);

    TIMER_CntInitTypeDef Timer2Init;
    TIMER_CntStructInit(&Timer2Init);
    Timer2Init.TIMER_Prescaler = 19;
    Timer2Init.TIMER_Period = 6500;
    TIMER_CntInit(MDR_TIMER2, &Timer2Init);

    TIMER_CntInitTypeDef Timer3Init;
    TIMER_CntStructInit(&Timer3Init);
    Timer3Init.TIMER_Prescaler = 3999;
    Timer3Init.TIMER_Period = 1000;
    TIMER_CntInit(MDR_TIMER3, &Timer3Init);

    TIMER_ITConfig(MDR_TIMER3, TIMER_STATUS_CNT_ARR, ENABLE);
    NVIC_EnableIRQ(Timer3_IRQn);

    TIMER_Cmd(MDR_TIMER2, ENABLE);
    TIMER_Cmd(MDR_TIMER3, ENABLE);

    while (1);
}