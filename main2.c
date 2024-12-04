//DE BECCARI

#include "MKL25Z4.h"
#include "ej2.h"
int temptrans;
int devtem;

int main(){
SIM -> SCGC5 |= SIM_SCGC5_PORTB_MASK;
SIM -> SCGC5 |= SIM_SCGC5_PORTA_MASK;
PORTA -> PCR[9] |= (1 << 8); 
PORTX -> PCR[9] = PORT_PCR_MUX(1) | PORTA_PCR_IRQC(0b1101);
NVIC -> ISER[0] = (1 << 9);
NVIC -> IPR [9>>2] = (0 << (( 9 & 0x3)*8+6));
while(1){
devtem=sensorT;
if(devtem!=1){
if(PTB->PDIR&(1<<1)){
 temptrans= tiempo(); 
 int decenasT=temptrans/10;
 int decenai=decenasT*10;
 int unidadT=temptrans-decenai
bcd7(decenasT,unidadT);
            }
        }else{
        bcd7(9,0);    
        }
    }
}
void interrupcion(){
    if(PORTB -> ISFR & (1 << 9)){
        PORTB -> ISFR |= (1 << 9);
     int tempactual= 10-sensorT();
     bcd7(tempactual,0);
    }
}
