#include "mcc_generated_files/mcc.h"
#include "math.h"

void main(void)
{
    SYSTEM_Initialize();

    uint8_t data=0;
    
    while (1)
    {
        EUSART2_Write((uint8_t)(200 * cos(data/10.)));
        
        if(data < 255)
            data++;
        else
            data = 1;
        while(!EUSART2_is_tx_done());
    }
}
