#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "string.h"

void init()
{
    TRISDbits.RD2 = 0;
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
        //polling receive
        recv = EUSART2_Read();
        decoded = (char)recv;
        char msg[20] = "Hello, Human.";
        if(decoded == 'i' || decoded == '0')
        {
            toggle();
            EUSART2_Write((uint8_t)40);
            for (register int i=0;i<strlen(msg);++i)
            {
                EUSART1_Write(msg[i]);
            }
            toggle();
            __delay_ms(10);
        }
        
        
    }
}
/**
 End of File
*/