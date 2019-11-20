#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "string.h"

void init()
{
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
}

inline void pwm(int duty_percent)
{
    for(int j=0;j<5;++j){
    //out of one second period
    LATDbits.LATD3 = 0;
    __delay_ms(1000-duty_percent * 10);
    LATDbits.LATD3 = 1;
    __delay_ms(duty_percent * 10);
    }
}
void toggle()
{
    LATDbits.LATD2 = 0;
    __delay_ms(200);
    LATDbits.LATD2 = 1;
    __delay_ms(200);
}
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    uint8_t data = 0;
    init();
    char decoded;
    uint8_t recv;
    for(int i=0;i<=3;++i)
    {
        toggle();
    }
    while (1)
    {
        for(register int i=0;i<=100;i+=10)
        {
            pwm(i);
        }
    }
}
