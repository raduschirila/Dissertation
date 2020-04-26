#include <pic18f45k22.h>
#include "mcc_generated_files/mcc.h"
#include "string.h"
#include <xc.h>
uint8_t data[14];
uint8_t read[10];

inline uint8_t map(int x, int in_min, int in_max, uint8_t out_min, uint8_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

inline void setup(void)
{
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISDbits.RD4 = 0;
    TRISDbits.RD5 = 0;
    TRISC = 0x00;
    TRISAbits.RA6 = 0;    
    TRISDbits.RD5 = 0;
}
inline void error(int code)
{
    for(int i = 0; i< code; ++i)
    {
        LATDbits.LATD5 = !LATDbits.LATD5;
        __delay_ms(100);
    }
    LATDbits.LATD5 = 1;
}
inline void start_status()
{
    LATDbits.LATD5 = 1;
}
inline void fill(int x)
{
    memset(data, 1, sizeof(data));
    for (int i=0;i<x;++i)
    {
        data[i]=2;
    }
}

inline void send_data()
{
    for(int i=0;i<14;++i)
    {
        EUSART2_Write(data[i]);
    }
    while(!EUSART2_is_tx_done());
}
inline void actuate()
{
    //memset(data,2,sizeof(data));
    for(int i = 0; i<14; ++i)
    {
        if(data[i] == 2)
        {
            switch(i)
            {
                case 0:
                    LATAbits.LATA6 = 1;
                    break;
                case 1:
                    LATCbits.LATC0 = 1;
                    break;
                case 2:
                    LATCbits.LATC1 = 1;
                    break;
                case 3:
                    LATCbits.LATC2 = 1;
                    break;
                case 4:
                    LATCbits.LATC3 = 1;
                    break;
                case 5:
                    LATDbits.LATD0 = 1;
                    break;
                case 6:
                    LATDbits.LATD1 = 1;
                    break;
                case 7:
                    LATDbits.LATD2 = 1;
                    break;
                case 8:
                    LATDbits.LATD3 = 1;
                    break;
                case 9:
                    LATCbits.LATC4 = 1;
                    break;
                case 10:
                    LATCbits.LATC5 = 1;
                    break;
                case 11:
                    LATCbits.LATC6 = 1;
                    break;
                case 12:
                    LATCbits.LATC7 = 1;
                    break;
                case 13:
                    LATDbits.LATD4 =1;
                default:
                    break;
            }
        }
        else if(data[i]== 1)
        {
            switch(i)
            {
                case 0:
                    LATAbits.LATA6 = 0;
                    break;
                case 1:
                    LATCbits.LATC0 = 0;
                    break;
                case 2:
                    LATCbits.LATC1 = 0;
                    break;
                case 3:
                    LATCbits.LATC2 = 0;
                    break;
                case 4:
                    LATCbits.LATC3 = 0;
                    break;
                case 5:
                    LATDbits.LATD0 = 0;
                    break;
                case 6:
                    LATDbits.LATD1 = 0;
                    break;
                case 7:
                    LATDbits.LATD2 = 0;
                    break;
                case 8:
                    LATDbits.LATD3 = 0;
                    break;
                case 9:
                    LATCbits.LATC4 = 0;
                    break;
                case 10:
                    LATCbits.LATC5 = 0;
                    break;
                case 11:
                    LATCbits.LATC6 = 0;
                    break;
                case 12:
                    LATCbits.LATC7 = 0;
                    break;
                case 13:
                    LATDbits.LATD4 = 0;
                default:
                    break;
            }
        }
    }
}

inline void send_pad()
{
    for (int i =0;i<5;++i)
    {
        EUSART2_Write(0);
    }
}

inline void timedReading_ISR(void)
{
    EUSART2_Write((uint8_t)(ADC_GetConversion(channel_AN0)>>8));
    __delay_ms(1);
    EUSART2_Write((uint8_t)(ADC_GetConversion(channel_AN1)>>8));
    __delay_ms(1);
    EUSART2_Write((uint8_t)(ADC_GetConversion(channel_AN2)>>8));
    __delay_ms(1);
    EUSART2_Write((uint8_t)(ADC_GetConversion(channel_AN3)>>8));
    __delay_ms(1);
    EUSART2_Write((uint8_t)(ADC_GetConversion(channel_AN4)>>8));
    __delay_ms(1);   
}

void receive_information(void)
{
    bool padding = false; 
    bool stop = false;
    uint8_t recv = 0;
    int index = 0;
    memset(data, 1, sizeof(data));
    while(recv == 0){
    recv = EUSART2_Read();
    }
    data[0]=recv;
    for(int i = 1;i<=13;++i)
    {
        recv = EUSART2_Read();
        data[i]=recv;
    }
    actuate();
}


void main(void)
{
    SYSTEM_Initialize();
    ADC_Initialize();
    setup();
    error(25);//setup in progress for arduino to sync buffer
    start_status();
    send_pad();
    uint8_t x = 0; 
    TMR2_SetInterruptHandler (timedReading_ISR);// register the  interrupt handler
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    while (1)
    {
        //every something ms send bend information 
        //always receive from the arduino touch information
        receive_information();
    }
}
