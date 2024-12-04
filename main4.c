#include "MKL25Z4.h"
#include "ej4.h"

int main(){
    int btn = 0;
    const uint8_t ledv = 8, ledr = 9;
    SIM -> SCGC5 |= SIM_SCGC5_PORTD_MASK;
    PORTD -> PCR[12] |= (1 << 8);
    PORT -> PCR[12] = PORT_PCRMUX(1) | PORTD:PCR:IRQC(0b1101);
    NVIC -> ISER[0] = (1 << 12); 

    while(1){
        btn = demux();
        contador(btn);
        LEDs(btn);
    }
}
//FALTA TERMINARLO
