/* 1. Se requiere una solución programable para resolver la siguiente problemática de tránsito
vehicular. Dónde S1 y S2 (semáforos) contarán con las luces rojo amarillo y verde, pero además
contendrán un semáforo de giro (rojo y verde) haciendo que el giro de S1 sea para la derecha y
de S2 hacia la izquierda. Como se puede observar hay una vía de tren con su respectiva barrera
la cual funciona con un sensor que ingresa por el pin 17 del puerto C que, al devolver un 1
lógico, indica que el tren está por pasar. Lo que deberán realizar es el control tanto de los
semáforos como de la barrera, esta última controlada por un motor paso a paso NEMA 17 y,
para concretar esta consigna, deberán realizar la siguiente/s función/es:
SEMÁFOROS: Deberán crear una función de inicio a los semáforos y otra en la que se le
ingresará que semáforo se utiliza (‘1’, ‘2’), si es de giro o “normal” (‘g’, ‘n’) y finalmente el color
(‘r’, ‘a’, ‘v’).
BARRERA: Para la barrera deberán crear una función que controle el motor paso a paso,
utilizándolo como un servomotor. Para ello se le deberá ingresar la angulación que se quiera
(número en grados) y el tipo de paso a realizar (‘f’ completo, ‘n’ normal, ‘m’ medio paso).
Además de su función de inicio de pines.
En conclusión, deberán crear la/s librería/s y utilizarlas en un código principal que realice
correctamente esta situación de tránsito. Tener en cuenta un botón por si ocurre alguna
anomalía y se tenga que poner el semáforo 2 en rojo. */

#include "MKL25Z4.h"
#include "semaforos.h"

//Utilizamos variables para asignarle nombre a cada luz del semáforo
cons uint8_t r1 = 0, a1= 1, v1 = 2, gr1 = 3, gv1 = 4, r2 = 5, a2= 6, v2 = 7, gr2 = 8, gv2 = 9; 
int main() {
    SIM -> SCGC5 |= SIM_SCGC5_PORTC_MASK; //Habilito el clock del puerto de las interrupciónes
    //El pin 17 será el sensor de la barrera y el 18 el asociado al botón de emergencia
    for(int i = 17; i <= 18; i++){
        PORTC -> PCR[i] |= (1 << 8);//Establezco el pin de las interrupciónes como GPIO 
        PTC -> PDDR |= (1u << i);//Defino los pines de las interrupciones como entradas
        PORTC -> PCR[i] = PORT_PCR_MUX(1) | PORTC_PCR_IRQC(0b1101)//Seteo la interrupción para el flanco de subida
    }
    //Seteamos la prioridad de las interrupciones
    NVIC -> IPR[17 >> 2] = (0 << ((17 & 0x3)*8+6));
    NVIC -> IPR[18 >> 2] = (1 << ((18 & 0x3)*8+6));
    inicioSemaforos();
    inicioMotores();
    while(1){
        int i = 0;
        semaforo(1, n, v);
        PTA -> PSOR &=~ (1u << r1);
        PTA -> PSOR &=~ (1u << a1);
        semaforo(1, g, v);
        PTA -> PSOR &=~ (1u << gr1);
        semaforo(2, n, r);
        PTA -> PSOR &=~ (1u << a2);
        PTA -> PSOR &=~ (1u << v2);
        semaforo(2, g, r);
        PTA -> PSOR &=~ (1u << gv2);
        barrera(90, n); //Barrera levantada
        for(i = 0; i <= 10000000){
        }
        PTA -> PTOR(1 << gv1);
        semaforo( 1, g, r);
        for(i = 0; i <= 15000000){
        }
        semaforo(1, n, a);
        for(i = 0; i <= 5000000){
        }
        //Ahora lo mismo pero con S2
        semaforo(2, n, v);
        PTA -> PSOR &=~ (1u << r2);
        PTA -> PSOR &=~ (1u << a2);
        semaforo(2, g, v);
        PTA -> PSOR &=~ (1u << gr2);
        semaforo(2, n, r);
        PTA -> PSOR &=~ (1u << a1);
        PTA -> PSOR &=~ (1u << v1);
        semaforo(1, g, r);
        PTA -> PSOR &=~ (1u << gv1);
        barrera(0, n); //Barrera baja
        for(i = 0; i <= 10000000){
        }
        PTA -> PTOR(1 << gv2);
        semaforo( 2, g, r);
        for(i = 0; i <= 15000000){
        }
        semaforo(2, n, a);
        for(i = 0; i <= 5000000){
        }

    }
    return 0;
}

void SensorBarrera(){ //Se baja la barrera y S1 se pone en rojo(tamto el normal como el giro) y S2 en verde(tanto el normal como el giro)
    if(PORTC -> ISFR & (1 << 17)){
        PORTC -> ISFR |= (1 << 17);
        semaforo( 1, n, r);
        semaforo( 1, g, r);
        PTA -> PSOR &=~(1u << a1);
        PTA -> PSOR &=~(1u << v1);
        PTA -> PSOR &=~(1u << r2);
        barrera(0, n);
        semaforo( 2, n, v);
        semaforo( 2, g, v);
    }
}

void BotonEmergencia(){
    if(PORTC -> ISFR & (1 << 18)){
        PORTC -> ISFR |= (1 << 18);
        semaforo( 2, n, r);
        semaforo( 2, g, r);
    }
}