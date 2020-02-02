/*
 * File:   main.c
 * Author: josue A
 * DIG2_LAB2
 * Created on January 29, 2020, 3:09 PM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000

void config_PUERTOS(void);
uint8_t  banderaBoton = 0;



void __interrupt() ISR(void){
    if (INTCONbits.RBIF == 1){             // IOCB
        if (banderaBoton == 0){
            if (PORTBbits.RB0 == 0){
                banderaBoton = 1;
                INTCONbits.RBIE = 0;
            }
            else if (PORTBbits.RB2 == 0){
                banderaBoton = 2;
                INTCONbits.RBIE = 0;
            }
        }
        INTCONbits.RBIF = 0;
    }
    
    
      return;  
    }

void main(void) {
    config_PUERTOS();
    INTCONbits.GIE = 1;
    INTCONbits.RBIF = 0;
    while(1){
        switch (banderaBoton){
            case 1:
                __delay_ms(150);
                PORTA = PORTA + 1;
                banderaBoton = 0;
                INTCONbits.RBIE = 1;
                
                break;
            case 2:
                __delay_ms(150);
                PORTA = PORTA - 1;
                banderaBoton = 0;
                INTCONbits.RBIE = 1;
                break;
            default:
                PORTA = PORTA;
            }

        }
    return;
}

void config_PUERTOS(void){
    //PUERTOS
    TRISD = 0;
    TRISC = 0;
    TRISA = 0;
    TRISB = 0b00000101;
    PORTA = 0; 
    PORTB = 0; 
    PORTC = 0; 
    PORTD = 0;
    ANSEL = 0;
    ANSELH = 0; 
    WPUB = 0b00000101;
    OPTION_REGbits.nRBPU = 0;
    
    //Interrupciones
    IOCB = 0b00000101;;  //RB0 y RB2 tiene interrupcion
    INTCONbits.RBIE = 1;
    return;
}
