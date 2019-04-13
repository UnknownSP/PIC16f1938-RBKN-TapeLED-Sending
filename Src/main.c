#include "main.h"
#include <xc.h>
#include <stdbool.h>

#define DATA_HI(){LATBbits.LATB0=1;}
#define DATA_LOW(){LATBbits.LATB0=0;}

void init(void);

void main(void) {


  char rainbow[20][3]={
    {0,0,255},{0,51,204},{0,102,153},{0,153,102},{0,204,51},
    {0,255,0},{31,207,0},{60,159,0},{110,111,0},{160,63,0},
    {150,50,0},{180,40,10},{200,30,20},{220,20,30},{180,10,60},
    {160,6,120},{140,5,130},{120,4,150},{80,3,180},{40,2,220},
  };
  int j=0;
  
  init();
  for(int i=0; i<LEDs; i++){
    R[i] = rainbow[i][0];
    G[i] = rainbow[i][1];
    B[i] = rainbow[i][2];
  }
  while(true){
    SendData();
    for(int i=0; i<LEDs; i++){
      int num = i+j;
      num %= 20; 
      R[i] = rainbow[num][0];
      G[i] = rainbow[num][1];
      B[i] = rainbow[num][2];
    }
    __delay_ms(50);
    RB1 = !RB1;
    j++;
    if(j>19){
      j = 0;
    }
  }
}

void init(void){

  // Set oscilation
  OSCCON = 0xF0; //PLL　Enable

  // Set pin mode
  ANSELA = 0b00000000;
  ANSELB = 0b00000000;
  TRISA  = 0b00000000;
  TRISB  = 0b00000000;
  
 }

void interrupt  HAND(void){
    
}
