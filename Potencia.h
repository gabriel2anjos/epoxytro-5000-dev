#ifndef POTENCIA_H
#define POTENCIA_H
#include "mbed.h"

class Potencia {
public:
    Potencia(PinName _vento, PinName _dir1, PinName _dir2, PinName _releFraco, PinName _releForte);
//    Potencia(PinName _vento, PinName _releFraco, PinName _releForte, PinName _servo);
    ~Potencia();

    void ventoControl(float pot);
    //void direcaoPonte(bool opcao);
    void ligarRele(bool opcao);
    void desligarRele(bool opcao);

private:
    PwmOut ventoinha;
    DigitalOut dir1;
    DigitalOut dir2;
    DigitalOut releFraco;
    DigitalOut releForte;
};

#endif


