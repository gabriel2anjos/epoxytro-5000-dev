#ifndef PORTAS_H
#define PORTAS_H
//DEFINICAO DAS PORTAS

//LCD - O pino RW deve ficar em GROUND
#define LCDRS       PTC12
#define LCDE        PTC13
#define LCD1        PTC16
#define LCD2        PTC17
#define LCD3        PTA16
#define LCD4        PTA17

//KeyPad
#define COL1        PTC4
#define COL2        PTC3
#define COL3        PTC0
#define COL4        PTC7
#define LIN1        PTC11
#define LIN2        PTC10
#define LIN3        PTC6
#define LIN4        PTC5

//Termometro
#define TERMO       PTA13

//Servo
#define SERVO       PTB1

//Controle de Potencia
#define VENTO       PTD5 //Quarta output digital
#define DIR1        PTA1 //
#define DIR2        PTA2 //
#define RELEFRACO   PTA12//Primeira output digital(rele da esquerda)
#define RELEFORTE   PTA12//Primeira output digital
//LEDS
#define RLED        PTB1
#define YLED        PTB1
#define GLED        PTB1

#endif


