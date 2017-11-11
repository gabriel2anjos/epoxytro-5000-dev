#ifndef OPERACAO_H
#define OPERACAO_H
#include "mbed.h"
#include "Leds.h"
#include "DS1820.h"
#include "NewTextLCD.h"
#include "Potencia.h"
#include "KeypadMelhorado.h"


class Operacao {
public:
    Operacao(Potencia* _potencia, TextLCD* _lcd, Leds* _leds, DS1820* _termo, KeypadMelhorado* _keypad);
    ~Operacao();
    bool iniciarOperacao(int calor, int tempo);
    void ticker60s();
    void ticker500ms();
    Ticker tick60s;
    Ticker tick500ms;
protected:
    Potencia* potencia;
    TextLCD* lcd;
    Leds* leds;
    DS1820* termo;
    KeypadMelhorado* keypad;
    bool acabou;
    bool inMenu;
    int calorInicial;
    int tempoInicial;
    int tempoRestante;
    float Temp, Erro, Ref;
    float Acao, Acao_ant, Erro_ant, Kp, Ki;
};

#endif



