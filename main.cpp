#include "mbed.h"
#include "portas.h"
#include "Keypad.h"
#include "DS1820.h"
#include "NewTextLCD.h"
#include "Potencia.h"
#include "Operacao.h"
#include "Leds.h"
#include "KeypadMelhorado.h"


TextLCD lcd(LCDRS, LCDE, LCD1, LCD2, LCD3, LCD4); // rs, e, d0-d3
KeypadMelhorado keypad(COL1, COL2, COL3, COL4, LIN1, LIN2, LIN3, LIN4);
DS1820 termo(TERMO);
Serial PC (USBTX, USBRX);
Potencia potencia(VENTO, DIR1, DIR2, RELEFRACO, RELEFORTE);
Leds leds(GLED, YLED, GLED);
Operacao operacao(&potencia, &lcd, &leds, &termo, &keypad);
const char fb = 0b11111111; //tudo preto

void diagnostico() {
    int i;
    lcd.cls();
    lcd.printf("DIAGNOSTICO");
    PC.printf("DIAGNOSTICO\n");
    wait(1);
    lcd.cls();
    lcd.printf("Teste 1:KeyPad");
    wait(3);
    if(!(keypad.ReadKey() == 'D')){
        lcd.locate(0,1);
        lcd.printf("1");
        while(keypad.ReadKey() != '1'){}
        lcd.locate(0,1);
        lcd.printf("2");
        while(keypad.teclaApertada() != '2'){}
        lcd.locate(0,1);
        lcd.printf("3");
        while(keypad.teclaApertada() != '3'){}
        lcd.locate(0,1);
        lcd.printf("A");
        while(keypad.teclaApertada() != 'A'){}
        lcd.locate(0,1);
        lcd.printf("4");
        while(keypad.teclaApertada() != '4'){}
        lcd.locate(0,1);
        lcd.printf("5");
        while(keypad.teclaApertada() != '5'){}
        lcd.locate(0,1);
        lcd.printf("6");
        while(keypad.teclaApertada() != '6'){}
        lcd.locate(0,1);
        lcd.printf("B");
        while(keypad.teclaApertada() != 'B'){}
        lcd.locate(0,1);
        lcd.printf("7");
        while(keypad.teclaApertada() != '7'){}
        lcd.locate(0,1);
        lcd.printf("8");
        while(keypad.teclaApertada() != '8'){}
        lcd.locate(0,1);
        lcd.printf("9");
        while(keypad.teclaApertada() != '9'){}
        lcd.locate(0,1);
        lcd.printf("C");
        while(keypad.teclaApertada() != 'C'){}
        lcd.locate(0,1);
        lcd.printf("*");
        while(keypad.teclaApertada() != '*'){}
        lcd.locate(0,1);
        lcd.printf("0");
        while(keypad.teclaApertada() != '0'){}
        lcd.locate(0,1);
        lcd.printf("#");
        while(keypad.teclaApertada() != '#'){}
        lcd.locate(0,1);
        lcd.printf("D");
        while(keypad.teclaApertada() != 'D'){}
    }
    lcd.cls();
    lcd.printf("Teste 2:Termo");
    if(termo.isPresent()){
        lcd.locate(0,1);
        lcd.printf("OK 1");
        wait(1);
        lcd.cls();
        while(keypad.ReadKey() != 'A'){
            termo.startConversion();
            lcd.cls();
            lcd.printf("%d", (int)termo.read());
            PC.printf("%f", termo.read());
            wait(1);
        }
    }
        
    lcd.cls();
    lcd.printf("Teste 3:Vento\nVel 1");
    potencia.ventoControl(0.25);
    wait(1);
    keypad.esperarTecla();
    lcd.cls();
    lcd.printf("Teste 3:Vento\nVel 2");
    potencia.ventoControl(0.75);
    wait(1);
    keypad.esperarTecla();
    lcd.cls();
    lcd.printf("Teste 4:Rele\nRele Forte");
    potencia.ligarRele(1);
    wait(1);
    keypad.esperarTecla();
    potencia.desligarRele(1);
    lcd.cls();
    lcd.printf("Teste 4:Rele\nRele Fraco");
    potencia.ligarRele(0);
    wait(1);
    potencia.desligarRele(0);
    keypad.esperarTecla();
    lcd.cls();
    lcd.printf("Teste 5:LEDS");
    leds.desligar('G'); leds.desligar('Y'); leds.desligar('R');
    for(i = 0; i < 5; i ++){
        leds.inverter('G'); leds.inverter('Y'); leds.inverter('R');
        wait(0.5);
    }
    leds.ligar('G'); leds.desligar('Y'); leds.desligar('R');
    lcd.cls();
    lcd.printf("Tudo Ok!");
    wait(5);
    lcd.cls();
}

void inicializacao(){
    leds.ligar('G'); leds.desligar('Y'); leds.desligar('R');
    potencia.desligarRele(0);
    potencia.desligarRele(1);
    lcd.cls();
    PC.printf("Inicializando\n");
    termo.begin();
    termo.setResolution(12);
    lcd.printf(" EPOXYTRON 5000 ");
    wait(5);
    if (keypad.ReadKey() == 'D') {
        diagnostico();
        lcd.printf(" EPOXYTRON 5000 ");
        wait(5);
        }
    lcd.cls();
}


void telaSelecao(int& tempoOp, int& calorOp){
    lcd.cls();
    bool flag = false;
    int horas = 0;
    int numero;
    while (true) {
        lcd.cls();
        lcd.printf("Digite o tempo:");
        lcd.locate(0,1);
        lcd.printf(" d  h  m");
        while(!flag){
            lcd.locate(0,1);
            lcd.putc(fb);
            numero = (int) keypad.numeroApertado();
            if(numero <= 7){
                flag = true;
                lcd.locate(0,1);
                tempoOp += 24*60*numero;
                lcd.printf("%d", numero);
            }
        }
        flag = false;
        while(!flag){
            lcd.locate(2,1);
            lcd.putc(fb);
            numero = (int) keypad.numeroApertado();
            if(numero <= 2){
                flag = true;
                lcd.locate(2,1);
                horas = numero*10;
                lcd.printf("%d", numero);
            }
        }
        flag = false;
        while(!flag){
            lcd.locate(3,1);
            lcd.putc(fb);
            numero = (int) keypad.numeroApertado();
            if((horas < 20 && numero <= 9) || (horas >= 20 && numero <= 3)){
                flag = true;
                lcd.locate(3,1);
                horas = horas + numero;
                tempoOp += 60*horas;
                lcd.printf("%d", numero);
            }
        }
        flag = false;
        while(!flag){
            lcd.locate(5,1);
            lcd.putc(fb);
            numero = (int) keypad.numeroApertado();
            if(numero < 6){
                flag = true;
                lcd.locate(5,1);
                tempoOp += numero*10;
                lcd.printf("%d", numero);
            }
        }
        flag = false;
        while(!flag){
            lcd.locate(6,1);
            lcd.putc(fb);
            numero = (int) keypad.numeroApertado();
            if(numero <= 9 && (tempoOp+numero >= 1)){
                flag = true;
                lcd.locate(6,1);
                tempoOp += numero;
                lcd.printf("%d", numero);
            }
        }
        flag = false;
        lcd.locate(0,0);
        char opcao;
        lcd.printf("Ok? A)Sim B)Nao");
        while(!flag){
            opcao = keypad.teclaApertada();
            if(opcao == 'A'){
                flag = true;
                lcd.cls();
            }
            else if(opcao == 'B'){
                flag = true;
                lcd.cls();
                tempoOp = 0;
                return;
            }
        }
        flag = false;
        lcd.cls();
        lcd.printf("Temperatura:\n  oC");
        lcd.locate(0,1);
        while(!flag){
            lcd.locate(0,1);
            lcd.putc(fb);
            numero = (int) keypad.numeroApertado();
            if(numero >= 2 && numero <= 6){
                flag = true;
                lcd.locate(0,1);
                calorOp = numero*10;
                lcd.printf("%d", numero);
            }
        }
        flag = false;
        while(!flag){
            lcd.locate(1,1);
            lcd.putc(fb);
            numero = (int) keypad.numeroApertado();
            if((numero == 0 && calorOp == 60) || (calorOp < 60)){
                flag = true;
                lcd.locate(1,1);
                calorOp += numero;
                lcd.printf("%d", numero);
            }
        }
        flag = false;
        lcd.locate(0,0);
        lcd.printf("Ok? A)Sim B)Nao");
        while(!flag){
            opcao = keypad.teclaApertada();
            if(opcao == 'A'){
                flag = true;
                lcd.cls();
                PC.printf("%d %d \n", tempoOp, calorOp);
                return;
            }
            else if(opcao == 'B'){
                flag = true;
                lcd.cls();
                calorOp = 0;
                return;
            }
        }
    }
}

int main() {
    while(1){
    inicializacao();
    while(1){
        int tempoOp = 0;
        int calorOp = 0;
        telaSelecao(tempoOp, calorOp);
        if(tempoOp == 0 || calorOp == 0) break;
        else{
            leds.ligar('y');
            leds.desligar('g');
            operacao.iniciarOperacao(calorOp,tempoOp);
            break;
        }

    }
    }

}


