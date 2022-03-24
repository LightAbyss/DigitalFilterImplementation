//Libreias
#include <stdio.h>
#include <stdlib.h>
//Self library
#include "MccVar.h"

//Señal
uint16_t Sign[21] = {2048,2666,3224,3666,3950,4048,3950,3666,3224
                    ,2666,2048,1430,872,430,146,48,146,430,872,1430,2048};
//Parámetros filtro
const float G1 = 0.9355121851;
const float G2 = 0.9355121851;
const float NUM[3] = {1,0.6207890511,1};
const float DEN1[3] = {1,0.6996148825,0.8777751923};
const float DEN2[3] = {1,0.459623605,0.8726683259};
//Aux
volatile float w1[3] = {0,0,0};
volatile float w2[3] = {0,0,0};
//Entrada
volatile float x1;
volatile float x2;
//Salida
volatile float y;

//Declarar funcion
void IIRCalc (void);
void IIRIni ();

int main(){



    return(0);
}

void IIRCalc (){
    //Seccion 1.1
    w1[0] = (DEN1[0] * x1) - (DEN1[1] * w1[1]) - (DEN1[2] * w1[2]);
    //Seccion 1.2
    x2 = (NUM[0] * w1[0]) + (NUM[1] * w1[1]) + (NUM[2] * w1[2]);
    //Seccion 2.1
    w2[0] = (DEN2[0] * x2) - (DEN2[1] * w2[1]) - (DEN2[2] * w2[2]);
    //Seccion 2.2
    y = (NUM[0] * w2[0]) + (NUM[1] * w2[1]) + (NUM[2] * w2[2]);
    //Corrimiento S1
    w1[2] = w1[1];
    w1[1] = w1[0];
    //Corrimiento S2
    w2[2] = w2[1];
    w2[1] = w2[0];
}