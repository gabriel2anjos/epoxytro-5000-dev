#include "mbed.h"
#include "Operacao.h"
#include "Leds.h"
#include "DS1820.h"
#include "NewTextLCD.h"
#include "Potencia.h"
#include "KeypadMelhorado.h"

Operacao::Operacao(Potencia* _potencia, TextLCD* _lcd, Leds* _leds, DS1820* _termo, KeypadMelhorado* _keypad) : potencia(_potencia), lcd(_lcd), leds(_leds), termo(_termo), keypad(_keypad){
    Temp=0.0; Erro = 0.0; Ref = 0.0;
    Acao=0; Acao_ant=0; Erro_ant=0.0;
    Kp = 0.2; Ki = 0.009; //Controle PI
}

Operacao::~Operacao(){}


void Operacao::ticker60s(){
    int calculoTempo;
    float temp;
    int tempExib;
    int var;
    tempoRestante -= 1;
    if (tempoRestante <= 0){
        Operacao::acabou = true;
        lcd->cls();
        lcd->printf("Acabou! Aperte\nqualquer tecla");
        keypad->esperarTecla();
        wait(0.5);
        tick60s.detach();
        tick500ms.detach();
        }
    else {
        if(!inMenu){
        calculoTempo = tempoRestante;
        lcd->cls();
        lcd->printf("Operando...");
        lcd->locate(0,1);
        lcd->printf(" d  h  m      oC");
        var = 0;
        var = (calculoTempo/1440);
        lcd->locate(0,1);
        lcd->printf("%d", var);
        calculoTempo -= (var*1440);
        lcd->locate(2,1);
        var = (calculoTempo/60);
        if(var >= 10){
            lcd->printf("%d", var);
        }
        else{
            lcd->printf("0%d", var);
        }
        calculoTempo -= (var*60);
        lcd->locate(5,1);
        if(calculoTempo >= 10){
            lcd->printf("%d", calculoTempo);
        }
        else{
            lcd->printf("0%d", calculoTempo);
        }
        lcd->locate(12,1);
        temp = 0;
        termo->startConversion();
        tempExib = (int)termo->read();
        if (tempExib >= 10){
            lcd->printf("%d", tempExib);
        }
        else {
            lcd->printf("0%d", tempExib);
        }
    }
    }
}

void Operacao::ticker500ms(){
    termo->startConversion();
    Temp=termo->read();
    Erro = -(Ref - Temp);
    Acao = Acao_ant +Kp*(Erro - Erro_ant)+Ki*0.5*Erro;

    if (Acao > 0.8) {
        Acao = 0.8;
    }
    else if (Acao < 0) {
        Acao = 0;
    }
    potencia->ventoControl(1.0-(Acao+0.20));
    Erro_ant = Erro; Acao_ant = Acao;
    if(Temp <= (Ref-2)){
        potencia->ligarRele(0);
        potencia->ligarRele(1);
    }
    if(Temp > (Ref-2.0) && Temp < (Ref+2.0)){
        potencia->desligarRele(0);
        potencia->ligarRele(1);
    }
    if(Temp > (Ref+2.0)){
        potencia->desligarRele(0);
        potencia->desligarRele(1);
    }
}

bool Operacao::iniciarOperacao(int calor, int tempo){
    tempoInicial = tempo;
    tempoRestante = tempo + 1;
    calorInicial = calor;
    inMenu = false;
    acabou = false;
    Ref = (float)calor;
    lcd->cls();
    lcd->printf("Aperte para\niniciar!");
    keypad->esperarTecla();
    tick60s.attach(callback(this, &Operacao::ticker60s), 60);
    tick500ms.attach(callback(this, &Operacao::ticker500ms), 0.5);
    Operacao::ticker60s();
    while(tempoRestante>0){
        if(acabou){
            
            break;
        }
        /*
        if(keypad->ReadKey() != '\0'){
            inMenu = true;
            lcd->cls();
            lcd->printf("Aperte D para\ncancelar!");
            wait(0.5);
            for  (i = 0; i < 8; i++){
                if (keypad->ReadKey() == 'D') {
                    lcd->cls();
                    lcd->printf("Parando!");
                    wait(2);
                    leds->ligar('g');
                    leds->desligar('y');
                    return false;
                }
                wait(0.5);
            }
            Operacao::ticker60s();
            inMenu = false;
        }*/
    }
    leds->ligar('g');
    leds->desligar('y');
    lcd->cls();
    lcd->printf("Acabou! Aperte\nqualquer tecla");
    keypad->esperarTecla();
    return true;
}



