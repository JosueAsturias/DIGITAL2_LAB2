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
#include <pic16f887.h>
#include "Display_7.h"
#include "ADC.h"
#define _XTAL_FREQ 4000000




void config_PUERTOS(void);
void press_Subir(void);
void press_Bajar(void);
uint8_t banderaBoton = 0;
uint8_t banderaUP = 0;
uint8_t banderaDO = 0;
uint8_t banderaTMR0 = 0;
uint8_t banderaADC = 0;
uint8_t valorDisplay_Dec;
uint8_t valorDisplay_Uni;


void __interrupt() ISR(void){
    
    if (PIR1bits.ADIF && PIE1bits.ADIE){
        PIE1bits.ADIE = 0;
        banderaADC = 1;
    }
    
    if (INTCONbits.RBIF == 1 && INTCONbits.RBIE == 1){   //atencion IOCB
        INTCONbits.RBIF = 0;
        if (banderaBoton == 0){
            banderaBoton = 1;
            INTCONbits.RBIE = 0;
        }
    }
    
    if (INTCONbits.T0IF == 1 && INTCONbits.T0IE == 1){
        banderaTMR0 = ~banderaTMR0;
        cambioDisplay(valorDisplay_Uni, valorDisplay_Dec, banderaTMR0);
        INTCONbits.T0IF = 0;
    }
      return;  
    }


void main(void) { 
    config_PUERTOS();
    config2Display(8000);
    ADConfig(8, 5, 'H');
    INTCONbits.GIE = 1;
    while(1){
        if (banderaADC == 1){
            valorDisplay_Uni = 9;
            uint8_t lectura = AnalogRead_8('H');
            if(lectura > PORTA){
                PORTEbits.RE1 = 1;
            }
            else if (lectura <= PORTA){
                PORTEbits.RE1 = 0;
            }
            valorDisplay_Uni = lectura & 0x0F;
            valorDisplay_Dec = (lectura & 0xF0) >> 4;
            banderaADC = 0;
            ADCinit();
        }
        press_Subir();
        press_Bajar();
        }
    return;
}

void config_PUERTOS(void){
    //PUERTOS
    TRISD = 255;
    TRISC = 255;
    TRISA = 0;
    TRISB = 0b00000101;
    TRISE = 0;
    PORTE = 0;
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
void press_Subir(void){
    if (banderaBoton == 1){
        if (banderaUP == 0){
            if (PORTBbits.RB0 == 0){
                __delay_ms(69);
                PORTA = PORTA + 1;
                banderaBoton = 0;
                banderaUP = 1;
                INTCONbits.RBIE = 1;
            }  
        }  
    }
    if (banderaUP == 1){
        if (PORTBbits.RB0 == 1){
        __delay_ms(69);
        banderaUP = 0;
        }
    }    
}
void press_Bajar(void){
    if (banderaBoton == 1){
        if (banderaDO == 0){
            if (PORTBbits.RB2 == 0){
                __delay_ms(69);
                PORTA = PORTA - 1;
                banderaBoton = 0;
                banderaDO = 1;
                INTCONbits.RBIE = 1;
            }  
        }  
    }
    if (banderaDO == 1){
        if (PORTBbits.RB2 == 1){
        __delay_ms(69);
        banderaDO = 0;
        }
    }    
}