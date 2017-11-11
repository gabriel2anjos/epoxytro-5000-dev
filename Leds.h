#ifndef LEDS_H
#define LEDS_H
#include "mbed.h"

class Leds {
public:
    Leds(PinName _RLED, PinName _YLED, PinName _GLED);
    ~Leds();

    void ligar(char opcao);
    void desligar(char opcao);
    void inverter(char opcao);
private:
    DigitalOut greenLed;
    DigitalOut redLed;
    DigitalOut yellowLed;
};

#endif


