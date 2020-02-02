/* 
 * File:     Display_7.h
 * Author:   Josue Asturias
 * Comments: Libreria para multiplexado de display de 7 segmentos
 * Revision history: 
 */

#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

// se debe cambiar esto de acuerdo a lo que se tenga
#define TRport TRISD             
#define PUERTOdisplay PORTD
#define Tr1 PORTCbits.RC2
#define Tr2 PORTCbits.RC0
#define TRpin1 TRISCbits.TRISC2
#define TRpin2 TRISCbits.TRISC0

uint8_t numerosDisplay[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
                                0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void config2Display(uint16_t FreqOsc);
//void config2Display(char Pnum, uint8_t Pcambio, 
//                    uint8_t Pin1, uint8_t Pin2, uint16_t FreqOsc);

/* Pnum     ---->   PUERTO de salida para los numeros (es una letra, p. ej. 'B')
 *                  si no escribe A, B, C o D, se aplica en el PORTD
 * Pcambio  ---->   PUERTO elegido para el cambio (es una letra, p. ej. 'B')
 *                  si no escribe A, B, C, D o E, se aplica en el PORTC
 * Pin1     ---->   PIN para activar/desactivar Display unidades
 * Pin2     ---->   PIN para activar/desactivar Display decenas
 * FreqOsc     ---->   Frecuencia de Oscilador escogido (lo congigurará)
 ----------------------------------------------------------------------------
 */

void cambioDisplay(uint8_t valUni, uint8_t valDec, uint8_t bandera);

#endif	/* XC_HEADER_TEMPLATE_H */

