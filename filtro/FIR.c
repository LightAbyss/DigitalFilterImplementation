//Library
#include <stdio.h>
#include <stdlib.h>
//Self library
#include "MccVar.h"

//Coeficientes
const int BL = 8;
const uint8_t B[8] = {0,    8,   40,   80,   80,   40,    8,    0};

//Señal
uint16_t Sign[29] = {2048,2493,2916,3295,3612,3850,3998,4048,3998,3850
                    ,3612,3295,2916,2493,2048,1603,1180,801,484,246,98
                    ,48,98,246,484,801,1180,1603,2048};

//Entrada
int x[8] = {0,0,0,0,0,0,0,0};
//Apuntador señal
uint16_t* ptrS = &Sign[0];
//Apuntador Filtro
const uint8_t* ptrFil = &B[0];
//Apuntador entrada
int* ptrXf = &x[7];
int* ptrXi = &x[0];

volatile uint32_t Y;
uint16_t mY;

int i;
int N = 0;

void FIRCalc(void);


int main(){
    FILE* fp;
    fp = fopen("DataOut.txt","a");

    while (N < 29){
        FIRCalc();
        N+=1;
        fprintf(fp,"%x,",mY);
    }

    fclose(fp);

    return(0);
}

void FIRCalc(){

    Y = 0;                                      //Reset Out
    //Actualizacion vector entrada
    for (i = 0;i < 7; i++){
        *(ptrXf)=*(ptrXf-1);
        ptrXf -= 1;
    }
    ptrXf = &x[7];
    *(ptrXi) = Sign[N];
    
    for (i = 0; i < BL/2; i++){
        Y += ( (uint32_t) *(ptrFil) ) * ( ( (uint32_t) *(ptrXf-i) ) + ( (uint32_t) *(ptrXi+i) ) );
        ptrFil++;
    }
    mY = Y >> 8;
    
    ptrFil = &B[0];
}