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

#include "semaforos.h"
#include "MKL25Z4.h"

int completo [4][4] =   {{0, 0, 0, 1}, 
                        {0, 0, 1, 0},
                        {0, 1, 0, 0},
                        {1, 0, 0, 0}};

int medio [4] [8] =     {{0, 0, 0, 1}, 
                        {0, 0, 1, 1},
                        {0, 0, 1, 0},
                        {0, 1, 1, 0},
                        {0, 1, 0, 0},
                        {1, 1, 0, 0},
                        {1, 0, 0, 0},
                        {1, 0, 0, 1}};

int normal [4] [4] =    {{0, 0, 1, 1},
                        {0, 1, 1, 0},
                        {1, 1, 0, 0},
                        {1, 0, 0, 1}};
void inicioSemaforos(){
    SIM -> SCGC5 |= SIM_SCGC5_PORTA_MASK;
    for(int i = 0; i < 10; i++){
        PORTA -> PCR[i] |= (1<<8);
        PTA -> PDDR &= ~(1u << i);
    }
}

void semaforo(int num, char t, char c){
    char tipo = tolower(t);
    char color = tolower(c);
    if(num == 1){
        if(tipo == 'g'){
            if(color == 'r'){
                PTA -> PSOR |= (1u << 3);
            } else if(color == 'v'){
                PTA -> PSOR |= (1u << 4);
            } 
        }
        else if(tipo == 'n'){
            if(color == 'r'){
                PTA -> PSOR |= (1u << 0);
            } else if(color == 'a'){
                PTA -> PSOR |= (1u << 1);
            } else if(color == 'v'){
                PTA -> PSOR |= (1u << 2);
            }
        }
    } else if(num == 2){
        if(tipo == 'g'){
            if(color == 'r'){
                PTA -> PSOR |= (1u << 8);
            } else if(color == 'v'){
                PTA -> PSOR |= (1u << 9);
            } 
        }
        else if(tipo == 'n'){
            if(color == 'r'){
                PTA -> PSOR |= (1u << 5);
            } else if(color == 'a'){
                PTA -> PSOR |= (1u << 6);
            } else if(color == 'v'){
                PTA -> PSOR |= (1u << 7);
            }
    }
}

void inicioMotores(){
    SIM -> SCGC5 |= SIM_SCGC5_PORTB_MASK;
    for(int i = 0; i < 4; i++){
        PORTB -> PCR[i] |= (1 << 8);
        PTA -> PDDR &=~(1u << i);
    }
}

void barrera(float angulo, char secuencia){
    char s = tolower(secuencia);
    int cant = angulo/1.8;
    if(s == 'c'){
        for(int i = 0; i < cant; i++){
            int paso = i%4;
            for(int j = 0; j < 4; j++){
                if(completo[j][i]){
                    PTB -> PSOR |= (1u << j);
                } else{
                    PTB - PSOR &=~ (1u << j);
                }
            } 
        }
    } else if(paso == 'n'){
        for(int i = 0; i < cant; i++){
            int paso = i%4;
            for(int j = 0; j < 4; j++){
                if(completo[j][i]){
                    PTB -> PSOR |= (1u << j);
                } else{
                    PTB - PSOR &=~ (1u << j);
                }
            } 
        }
    } else if(paso == 'm'){
        for(int i = 0; i < cant; i++){
            int paso = i%8;
            for(int j = 0; j < 4; j++){
                if(completo[j][i]){
                    PTB -> PSOR |= (1u << j);
                } else{
                    PTB - PSOR &=~ (1u << j);
                }
            } 
        }
    }
}