#ifndef KEYPADMELHORADO_H
#define KEYPADMELHORADO_H
#include "mbed.h"
#include "portas.h"
#include "Keypad.h"

class KeypadMelhorado : public Keypad {
public:
    KeypadMelhorado(PinName col1, PinName col2, PinName col3, PinName col4, PinName row1, PinName row2, PinName row3, PinName row4);
    void esperarTecla();
    char teclaApertada();
    int numeroApertado();
};


#endif


