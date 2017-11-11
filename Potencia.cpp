#include "mbed.h"
#include "Potencia.h"

Potencia::Potencia(PinName _vento, PinName _dir1, PinName _dir2, PinName _releFraco, PinName _releForte) : ventoinha(_vento), dir1(_dir1), dir2(_dir2), releFraco(_releFraco), releForte(_releForte){
    ventoinha.period(0.0001);
    //direcaoPonte(0);
}
Potencia::~Potencia(){

}

void Potencia::ventoControl(float pot){
    if(pot<=1.0 && pot>=0.0){
        ventoinha = pot;
    }
}


void Potencia::ligarRele(bool opcao){
    if(opcao){
        releForte = 1;
    }
    if(!opcao){
        releFraco = 1;
    }
}

void Potencia::desligarRele(bool opcao){
    if(opcao){
        releForte = 0;
    }
    if(!opcao){
        releFraco = 0;
    }
}


