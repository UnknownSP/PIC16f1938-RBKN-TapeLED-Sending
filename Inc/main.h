#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

#define _XTAL_FREQ 32000000

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#include <pic16f1938.h>
#include "LEDDrive.h"

#define MAX_LEDs 200
  
#define TAPE1_LEDs 20
#define TAPE2_LEDs 20
#define TAPE3_LEDs 20
#define TAPE4_LEDs 20
#define TAPE5_LEDs 20
#define TAPE6_LEDs 20
#define TAPE7_LEDs 20
#define TAPE8_LEDs 20

unsigned char R1[TAPE1_LEDs];
unsigned char B1[TAPE1_LEDs];
unsigned char G1[TAPE1_LEDs];
unsigned char R2[TAPE2_LEDs];
unsigned char B2[TAPE2_LEDs];
unsigned char G2[TAPE2_LEDs];
unsigned char R3[TAPE3_LEDs];
unsigned char B3[TAPE3_LEDs];
unsigned char G3[TAPE3_LEDs];
unsigned char R4[TAPE4_LEDs];
unsigned char B4[TAPE4_LEDs];
unsigned char G4[TAPE4_LEDs];
unsigned char R5[TAPE5_LEDs];
unsigned char B5[TAPE5_LEDs];
unsigned char G5[TAPE5_LEDs];
unsigned char R6[TAPE6_LEDs];
unsigned char B6[TAPE6_LEDs];
unsigned char G6[TAPE6_LEDs];
unsigned char R7[TAPE7_LEDs];
unsigned char B7[TAPE7_LEDs];
unsigned char G7[TAPE7_LEDs];
unsigned char R8[TAPE8_LEDs];
unsigned char B8[TAPE8_LEDs];
unsigned char G8[TAPE8_LEDs];

const int tape_leds_num[8] = {TAPE1_LEDs,TAPE2_LEDs,TAPE3_LEDs,TAPE4_LEDs,TAPE5_LEDs,TAPE6_LEDs,TAPE7_LEDs,TAPE8_LEDs};
  
typedef enum{
  NONE = 0,
  RAINBOW = 1,
  RED = 2,
  GREEN = 3,
  BLUE = 4,
  YELLOW = 5,
  PURPLE = 6,
  BLINK_RED = 7,
  INCREMENT = 8,
}BlinkMode_t;

const char rainbow[20][3]={
    {0,0,255},{0,51,204},{0,102,153},{0,153,102},{0,204,51},
    {0,255,0},{31,207,0},{60,159,0},{110,111,0},{160,63,0},
    {150,50,0},{180,40,10},{200,30,20},{220,20,30},{180,10,60},
    {160,6,120},{140,5,130},{120,4,150},{80,3,180},{40,2,220},
};
  
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */
