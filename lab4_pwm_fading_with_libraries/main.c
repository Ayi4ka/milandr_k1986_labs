#include "MDR32Fx.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"

int main() {
    RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER2, ENABLE);
    TIMER_BRGInit(MDR_TIMER2, TIMER_HCLKdiv1);

    TIMER_CntInitTypeDef TimerInit;
    TIMER_CntStructInit(&TimerInit);
    TimerInit.TIMER_Prescaler = 19;
    TimerInit.TIMER_Period = 6500;
    TimerInit.TIMER_CounterDirection = TIMER_CntDir_Up;
    TIMER_CntInit(MDR_TIMER2, &TimerInit);

    TIMER_ChnInitTypeDef ChannelInit;
    ChannelInit.TIMER_CH_Number = TIMER_CHANNEL2;
    ChannelInit.TIMER_CH_Mode = TIMER_CH_MODE_PWM;
    ChannelInit.TIMER_CH_REF_Format = TIMER_CH_REF_Format6;
    TIMER_ChnInit(MDR_TIMER2, &ChannelInit);

    TIMER_ChnOutInitTypeDef OutputInit;
    OutputInit.TIMER_CH_DirOut_Source = TIMER_CH_OutSrc_REF;
    OutputInit.TIMER_CH_DirOut_Mode = TIMER_CH_OutMode_Output;
    OutputInit.TIMER_CH_DirOut_Polarity = TIMER_CHOPolarity_NonInverted;
    OutputInit.TIMER_CH_Number = TIMER_CHANNEL2;
    TIMER_ChnOutInit(MDR_TIMER2, &OutputInit);

    TIMER_Cmd(MDR_TIMER2, ENABLE);

    int i;
    while (1) {
        for (i = 6500; i > 0; i--) {
            TIMER_SetChnCompare(MDR_TIMER2, TIMER_CHANNEL2, i);
            for (volatile int j = 0; j < 5000; j++);
        }
    }
}