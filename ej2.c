//De BECCARI

#include "ej2.h"
#include "MKL25Z4.h"
int BCD[10][4]={
    {0,0,0,0}
    {0,0,0,1}
    {0,0,1,0}
    {0,0,1,1}
    {0,1,0,0}
    {0,1,0,1}
    {0,1,1,0}
    {0,1,1,1}
    [1,0,0,0]
    [1,0,0,1]   
};
int tiempodev;
 int unidad;
 int decena=0;
int unitemp[4];
int bits[7];

int tiempo(){
SIM -> SCGC5 |= SIM_SCGC5_PORTB_MASK;
for(int i=0;i<5;i++){
    PORTB -> PCR[i] |= (1 << 8); 
    PTB -> PDDR |= (1u << i);
}
for(int j=0;j<4;j++){
  unitemp[j]=  PTB -> PDIR & (1 << j);
}
 int aux1=unitemp[1];
 int aux2=unitemp[2]*2;
 int aux3=unitemp[3]*4;
 int aux4=unitemp[4]*8;
 unidad=aux1+aux2+aux3+aux4;
 if(unidad=9){
    decena++;
 }
tiempodev=(decena*10)+unidad;
return tiempodev;
}

int sensorT(){
    SIM -> SCGC5 |= SIM_SCGC5_PORTA_MASK;
    for(int i=0;i<7;i++){
        PORTA -> PCR[i] |= (1 << 8); 
        PTA -> PDDR |= (1u << i);
      bits[i]= PTX -> PDIR & (1 << i);
    }
    int aux1=bits[1];
    int aux2=bits[2]*2;
    int aux3=bits[3]*4;
    int aux4=bits[4]*8;
    int aux5=bits[5]*16;
    int aux6=bits[6]*32;
    int aux7=bits[7]*64;
    int tempdec= aux1+aux2+aux3+aux4+aux5+aux6+aux7;
    if(tempdec=90){
        return 1;
    }
    else if(tempdec=80){
        return 2;
    }
        if(tempdec=70){
        return 3;
    }
    else if(tempdec=60){
        return 4;
    }    if(tempdec=50){
        return 5;
    }
    else if(tempdec=40){
        return 6;
    }
        if(tempdec=30){
        return 7;
    }
    else if(tempdec=20){
        return 8;
    }
        if(tempdec=10){
        return 9;
    }
    else if(tempdec=0){
        return 10;
    }
}
void bcd7(int dec, int uni){
 SIM -> SCGC5 |= SIM_SCGC5_PORTA_MASK;
 for(int i=8;i<16;i++){
     PORTA -> PCR[i] |= (1 << 8); 
        PTA -> PDDR |= (1u << i);
 }
    for(int j=0;j<4;j++){
        if(bcd[dec][j]){
        PTA -> PSOR |= (BCD[dec][j]u<<j+8);
        }else{
                PTA -> PSOR &=∼ (BCD[dec][j]u<<j+8);
        }
    }
        for(int x=0;x<4;x++){
        if(bcd[uni][x]){
        PTA -> PSOR |= (BCD[uni][x]u<<j+8);
        }else{
                PTA -> PSOR &=∼ (BCD[uni][x]u<<j+8);
        }
    }
}
