/*
 * File:   newmain.c
 * Author: radus
 *
 * Created on November 14, 2019, 3:16 PM
 */


#include <xc.h>
#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"


void init_registers()
{
    /**
     initialise all pins like in pin manager (MCC)
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    TRISE = 0x07;
    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISD = 0xFF;

    ANSELD = 0xFF;
    ANSELC = 0x3C;
    ANSELB = 0x3F;
    ANSELE = 0x07;
    ANSELA = 0x2F;

    WPUB = 0x00;
    INTCON2bits.nRBPU = 1;
    
    // Initialise oscillator 
    OSCCON = 0x39;
    OSCCON2 = 0x00;
    OSCTUNE = 0x00;

    TRISCbits.TRISC6 = 0; // TX as output
    TRISCbits.TRISC7 = 1; // RX as input
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;  
    BAUDCON1bits.BRG16 = 0; // Divisor at 8 bit
    TXSTA1bits.BRGH = 0; // No high-speed baudrate
    SPBRG1 = 103; // divisor value for 19200
    return;
}
void send(uint8_t x)
{
    while(TXSTA1bits.TRMT == 0){}
    TXREG1 = x;
}

void main(void) {
    init_registers();
    uint8_t c = 0;
    while(1){
        send(c);
        c++;
        if(c==100)
            c=1;}
    return;
}
