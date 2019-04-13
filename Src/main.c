#include "main.h"
#include <xc.h>
#include <stdbool.h>

#define DATA_HI(){LATBbits.LATB0=1;}
#define DATA_LOW(){LATBbits.LATB0=0;}

void init(void);
static void blink(BlinkMode_t mode, int tape_num);
void set_rgb(int tape_num, int lednum, char color, int set_data);

void main(void) {

  int j=40;
  
  init();
  while(true){
    RB1 = !RB1;
    blink(NONE,1);
    blink(NONE,2);
    blink(GREEN,3);
    blink(RED,4);
  }
}

static void blink(BlinkMode_t mode, int tape_num){
  
  static int count[4]={0,0,0,0};
  int i;
  
  switch(mode){
  case RAINBOW:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      int num = i+count[tape_num-1];
      num %= 20;//tape_leds_num[tape_num-1];
      set_rgb(tape_num, i, 'R', rainbow[num][0]);
      set_rgb(tape_num, i, 'G', rainbow[num][1]);
      set_rgb(tape_num, i, 'B', rainbow[num][2]);
    }
    count[tape_num-1]++;
    if(count[tape_num-1]>=20){
      count[tape_num-1] = 0;
    }
    SendData(tape_num);
    __delay_ms(10);
    break;
    
  case RED:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 255);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 0);
    }
    SendData(tape_num);
    __delay_ms(10);
    break;
    
  case GREEN:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 0);
      set_rgb(tape_num, i, 'G', 255);
      set_rgb(tape_num, i, 'B', 0);
    }
    SendData(tape_num);
    __delay_ms(10);
    break;
    
  case BLUE:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 0);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 255);
    }
    SendData(tape_num);
    __delay_ms(10);
    break;
    
  case NONE:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 0);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 0);
    }
    SendData(tape_num);
    __delay_ms(10);
    break;
  }
}

void set_rgb(int tape_num, int lednum, char color, int set_data){
  switch(tape_num){
  case 1:
    switch(color){
    case 'R':
      R1[lednum] = set_data;
      break;
    case 'G':
      G1[lednum] = set_data;
      break;
    case 'B':
      B1[lednum] = set_data;
      break;
    }
    break;
    
  case 2:
    switch(color){
    case 'R':
      R2[lednum] = set_data;
      break;
    case 'G':
      G2[lednum] = set_data;
      break;
    case 'B':
      B2[lednum] = set_data;
      break;
    }
    break;
  case 3:
    switch(color){
    case 'R':
      R3[lednum] = set_data;
      break;
    case 'G':
      G3[lednum] = set_data;
      break;
    case 'B':
      B3[lednum] = set_data;
      break;
    }
    break;
  case 4:
    switch(color){
    case 'R':
      R4[lednum] = set_data;
      break;
    case 'G':
      G4[lednum] = set_data;
      break;
    case 'B':
      B4[lednum] = set_data;
      break;
    }
    break;
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
