#include "mbed.h"
#include "portas.h"
#include "Keypad.h"
#include "KeypadMelhorado.h"

KeypadMelhorado::KeypadMelhorado (PinName col1, PinName col2, PinName col3, PinName col4, PinName row1, PinName row2, PinName row3, PinName row4) : Keypad( col1, col2, col3, col4, row1, row2, row3, row4){
}

char KeypadMelhorado::teclaApertada() {
    char key;
    int released = 1;
    while(1){
        key = Keypad::ReadKey();
        if(Keypad::ReadKey() != '\0') {
            while(Keypad::ReadKey() != '\0'){
                wait(0.1);
            }
            return key;
        }
        wait(0.1);
    }
}


int KeypadMelhorado::numeroApertado() {
    char key;
    int num;
    while(1){
        key = Keypad::ReadKey();
        if((key != '\0')&& (key != 'A') && (key != 'B')&& (key != 'C')&& (key != 'D')&& (key != '*') && (key != '#')) {
            while((Keypad::ReadKey() != '\0')&& (Keypad::ReadKey() != 'A') && (Keypad::ReadKey()!= 'B')&& (Keypad::ReadKey() != 'C')&& (Keypad::ReadKey() != 'D')&& (Keypad::ReadKey() != '#')&& (Keypad::ReadKey() != '#')){
                wait(0.1);
            }
            num = key  - '0';
            return num;
        }
        wait(0.1);
    }
}

void KeypadMelhorado::esperarTecla(){
    while(1){
        if(Keypad::ReadKey() != '\0'){
            while(Keypad::ReadKey() != '\0'){
                wait(0.1);
            }
            wait(0.1);
            return;
        }
        wait (0.1);
    }
}


