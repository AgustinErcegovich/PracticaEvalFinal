/*4. Se solicita una solución programable para que la placa KL25Z funcione de la siguiente
manera. Se deberá realizar un demultiplexor de 1 a 2 donde su entrada selectora se maneja
mediante un pulsador y su entrada estarán a un ‘1’ lógico enviado por el microcontrolador. Si se
selecciona la primera entrada se activará un contador descendente el cuál será mostrado a
través de dos contadores BCD a sus correspondientes displays 7 segmentos, indicando también
que estos displays están encendidos mediante un led verde, que, cuando llegue a su número
máximo se resetee y arranque nuevamente.
Si por el contrario, se selecciona la segunda entrada se deberá habilitar un contador conectado a
otros dos BCD con sus respectivos displays, donde se hará una cuenta ascendente desde el
número “99” y, también, se encenderá un led rojo y se reiniciará. Cómo último en el pin 12 del
puerto D habrá un pulsador que reiniciará a los dos pulsadores, poniéndolos a los dos en “00”,
para luego esperar a que se elija en el demultiplexor.
Para realizar llevar a cabo este código deberán crear una librería que contenga las siguientes
funciones:
• Función del demultiplexor, que contendrá la inicialización, funcionalidad.
• Una función para cada contador (ascendente y descendente) con su inicialización
correspondiente.
• Una función para el control de leds (estilo DigitalWrite)
Por último, recuerden que se deberá volcar lo necesario para que funcione dentro de un código
fuente y que, salvo lo que se especifique anteriormente, todo sucede dentro del puerto C. */

#include "ej4.h"
#include "MKL25Z4.h"

SIM -> SCGC5 |= SIM_SCGC5_PORTC_MASK;

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

int demux(){
    PORTC -> PCR[0] |= (1 << 8);
    PTC -> PDDR |= (1u << 0)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
    if(PTC -> PDIR & (1 << 0)){
        return 1;
    } else{
        return 0;
    }
}

void contador(int s){
    for(int i = 1; i <= 9; i++){
        PORTC -> PCR[i] |= (1 << 8);
        PTC -> PDDR &=~ (1u << i);
    }
    if(s){
        for(i = 0; i <= 9; i++){
            for(int l = 0; l < 4; l++){
                    if(BCD[i][l]){
                    PTC -> PSOR |= (1u << (l + 4));
                } else{
                    PTC -> PSOR &=~ (1u << (l +4));
                }
            for(int j = 0; i <= 9; i++){
                for(int k = 0; k < 4; k++){
                    if(BCD[j][k]){
                    PTC -> PSOR |= (1u << k);
                } else{
                    PTC -> PSOR &=~ (1u << k);
                }
                }
            }
        }
        for(i = 0; i < 4; i++){
            PTC -> PSOR &=~ (1u << i);
            PTC -> PSOR &=~ (1u << (i +4));
        }
    } else{
        for(i = 9; i >= 0; i--){
            for(int l = 0; l < 4; l++){
                    if(BCD[i][l]){
                    PTC -> PSOR |= (1u << (l + 4));
                } else{
                    PTC - PSOR &=~ (1u << (l +4));
                }
            for(int j = 9; i >= 0; i--){
                for(int k = 0; k < 4; k++){
                    if(BCD[j][k]){
                    PTC -> PSOR |= (1u << k);
                } else{
                    PTC - PSOR &=~ (1u << k);
                }
                }
            }
        }
        for(i = 0; i < 4; i++){
            PTC -> PSOR |= (1u << i);
            PTC -> PSOR |= (1u << (i +4));
        }
    }
}

void LEDs(int estado){
    const uint8_t ledv = 8, ledr = 9;
    PORTC -> PCR[ledv] |= (1 << 8);
    PORTC -> PCR[ledr] |= (1 << 8);
    PTC -> PDDR &=~ (1u << ledv);
    PTC -> PDDR &=~ (1u << ledr);
    if(estado){
        PTC -> PSOR |= (1u<<ledr);
    } else{
        PTC -> PSOR |= (1u<<ledv);
    }
}
