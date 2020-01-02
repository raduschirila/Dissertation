#include "mcc_generated_files/mcc.h"
#include "string.h"
uint8_t data[14];

inline void fill(int x)
{
    memset(data, 1, sizeof(data));
    for (int i=0;i<x;++i)
    {
        data[i]=2;
    }
}

inline void send_pad()
{
    for(int i=0;i<5;++i)
    {
        EUSART2_Write((uint8_t)0);
    }
    while(!EUSART2_is_tx_done());
}

inline void send_buf()
{
    for(int i=0;i<14;++i)
    {
        EUSART2_Write(data[i]);
    }
    while(!EUSART2_is_tx_done());
}

void main(void)
{
    SYSTEM_Initialize();
    uint8_t index = 0;
    while (1)
    {
        send_pad();
        fill(index);
        send_buf();
        send_pad();
        while(!EUSART2_is_tx_done());
        if(index == 14)
            index = 0;
        else index++;
        
        __delay_ms(1000);
    }
}
