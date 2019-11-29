#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "string.h"

void init()
{
    TRISDbits.RD2 = 0;
}

void toggle(int delay)
{
    LATDbits.LATD2 = 0;
    for(int i=0;i<delay/10;++i)
        __delay_ms(10);
    LATDbits.LATD2 = 1;
    for(int i=0;i<delay/10;++i)
        __delay_ms(10);
}
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    uint8_t data = 0;
    init();
    char decoded;
    uint8_t delay = 100;
    for(int i=0;i<=3;++i)
    {
        toggle();
    }
    while (1)
    {
        data = EUSART2_Read();
        if(data == (uint8_t) 'w')//up in speed
            toggle(delay-1);
        else if (data == (uint8_t) 's')
            toggle(delay+1);
        else toggle(delay);
    }
}
