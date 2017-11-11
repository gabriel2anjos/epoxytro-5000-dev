#include "mbed.h"
#include "Leds.h"

Leds::Leds(PinName _RLED, PinName _YLED, PinName _GLED) : redLed(_RLED), greenLed(_GLED), yellowLed(_YLED){
}

Leds::~Leds(){

}

void Leds::ligar(char opcao){
    if(opcao == 'R' || opcao == 'r') redLed = 0;
    else if(opcao == 'Y' || opcao == 'y') yellowLed = 0;
    else if(opcao == 'G' || opcao == 'g') greenLed = 0;
    else{}
}

void Leds::desligar(char opcao){
    if(opcao == 'R' || opcao == 'r') redLed = 1;
    else if(opcao == 'Y' || opcao == 'y') yellowLed = 1;
    else if(opcao == 'G' || opcao == 'g') greenLed = 1;
    else{}
}

void Leds::inverter(char opcao){
    if(opcao == 'R' || opcao == 'r') redLed = !redLed;
    else if(opcao == 'Y' || opcao == 'y') yellowLed = !yellowLed;
    else if(opcao == 'G' || opcao == 'g') greenLed = !greenLed;
    else{}
}


