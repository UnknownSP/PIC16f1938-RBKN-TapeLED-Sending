#include "main.h"
#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>

void init(void);
static void blink(BlinkMode_t mode, int tape_num);
void set_rgb(int tape_num, int lednum, char color, int set_data);

void main(void) {

  int j=40;
  
  init();
  while(true){
    RB1 = !RB1;
    blink(INCREMENT,1);
    blink(RAINBOW,2);
    blink(GREEN,3);
    blink(RED,4);
  }
}

static void blink(BlinkMode_t mode, int tape_num){
  
  static int count[4]={0,0,0,0};
  static int count2[4]={0,0,0,0};
  static int increment[4][3]={
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
  }; 
  int i;
  static int red;
  int set_count = 0;
    
  switch(mode){
  case NONE:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 0);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 0);
    }
    SendData(tape_num);
    __delay_ms(10);
    break;
    
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

  case YELLOW:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 255);
      set_rgb(tape_num, i, 'G', 255);
      set_rgb(tape_num, i, 'B', 0);
    }
    SendData(tape_num);
    __delay_ms(10);
    break;

  case PURPLE:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 255);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 255);
    }
    SendData(tape_num);
    __delay_ms(10);
    break;

  case BLINK_RED:
    switch(count[tape_num-1]){
    case 1:
      red = 255;
      break;
    case 4:
      red = 0;
      break;
    case 7:
      red = 255;
      break;
    case 10:
      red = 0;
      break;
    case 20:
      count[tape_num-1] = 0;
      break;
    }
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', red);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 0);
    }
    count[tape_num-1]++;
    SendData(tape_num);
    __delay_ms(10);
    break;

  case INCREMENT:
    if(count2[tape_num-1]%3==0){
      if(increment[tape_num-1][2]==0){
	if(count[tape_num-1]==0){
	  increment[tape_num-1][1] = tape_leds_num[tape_num-1];
	  increment[tape_num-1][0] = 0;
	}
	count[tape_num-1]++;
	if(increment[tape_num-1][0] <= increment[tape_num-1][1]){
	  increment[tape_num-1][0]++;
	}
	if(increment[tape_num-1][0] > increment[tape_num-1][1]){
	  increment[tape_num-1][1]--;
	}
	if(increment[tape_num-1][1] == 0){
	  count[tape_num-1]=0;
	  increment[tape_num-1][2]=1;
	  set_count = 0;
	}
	for(i=count[tape_num-1]-1; i>=0; i--){
	  if(i%2 == (count[tape_num-1]-1)%2){
	    if(i<tape_leds_num[tape_num-1]){
	      switch(set_count%4){
	      case 0:
		set_rgb(tape_num, i, 'R', 0);
		set_rgb(tape_num, i, 'G', 0);
		set_rgb(tape_num, i, 'B', 255);
		break;
	      case 1:
		set_rgb(tape_num, i, 'R', 0);
		set_rgb(tape_num, i, 'G', 255);
		set_rgb(tape_num, i, 'B', 0);
		break;
	      case 2:	
		set_rgb(tape_num, i, 'R', 255);
		set_rgb(tape_num, i, 'G', 255);
		set_rgb(tape_num, i, 'B', 0);
		break;
	      case 3:
		set_rgb(tape_num, i, 'R', 255);
		set_rgb(tape_num, i, 'G', 0);
		set_rgb(tape_num, i, 'B', 255);
		break;
	      }
	    }
	    set_count++;
	  }else{
	    if(i<tape_leds_num[tape_num-1]){
	      set_rgb(tape_num, i, 'R', 0);
	      set_rgb(tape_num, i, 'G', 0);
	      set_rgb(tape_num, i, 'B', 0);
	    }
	  }
	
	}
	for(i=tape_leds_num[tape_num-1]-1; i>=increment[tape_num-1][1]; i--){
	  switch( (i+ 4-((tape_leds_num[tape_num-1]-1)%4) ) %4){
	  case 0:
	    set_rgb(tape_num, i, 'R', 0);
	    set_rgb(tape_num, i, 'G', 0);
	    set_rgb(tape_num, i, 'B', 255);
	    break;
	  case 3:
	    set_rgb(tape_num, i, 'R', 0);
	    set_rgb(tape_num, i, 'G', 255);
	    set_rgb(tape_num, i, 'B', 0);
	    break;
	  case 2:
	    set_rgb(tape_num, i, 'R', 255);
	    set_rgb(tape_num, i, 'G', 255);
	    set_rgb(tape_num, i, 'B', 0);
	    break;
	  case 1:
	    set_rgb(tape_num, i, 'R', 255);
	    set_rgb(tape_num, i, 'G', 0);
	    set_rgb(tape_num, i, 'B', 255);
	    break;
	  }
	}
      }else{
	count[tape_num-1]++;
	for(i=tape_leds_num[tape_num-1]+count[tape_num-1]-1; i>=count[tape_num-1]-tape_leds_num[tape_num-1]; i--){
	  if(abs(i)%2 == (tape_leds_num[tape_num-1]+count[tape_num-1]-1)%2){
	    if(i<tape_leds_num[tape_num-1] && i>=0){
	      switch(set_count%4){
	      case 0:
		set_rgb(tape_num, i, 'R', 0);
		set_rgb(tape_num, i, 'G', 0);
		set_rgb(tape_num, i, 'B', 255);
		break;
	      case 1:
		set_rgb(tape_num, i, 'R', 0);
		set_rgb(tape_num, i, 'G', 255);
		set_rgb(tape_num, i, 'B', 0);
		break;
	      case 2:	
		set_rgb(tape_num, i, 'R', 255);
		set_rgb(tape_num, i, 'G', 255);
		set_rgb(tape_num, i, 'B', 0);
		break;
	      case 3:
		set_rgb(tape_num, i, 'R', 255);
		set_rgb(tape_num, i, 'G', 0);
		set_rgb(tape_num, i, 'B', 255);
		break;
	      }
	    }
	    set_count++;
	  }else{
	    if(i<tape_leds_num[tape_num-1] && i>=0){
	      set_rgb(tape_num, i, 'R', 0);
	      set_rgb(tape_num, i, 'G', 0);
	      set_rgb(tape_num, i, 'B', 0);
	    }
	  }
	}
	for(i=0;i<tape_leds_num[tape_num-1]-count[tape_num-1];i++){
	  switch( (i+(4-tape_leds_num[tape_num-1]%4))%4 ){
	  case 3:
	    set_rgb(tape_num, i, 'R', 0);
	    set_rgb(tape_num, i, 'G', 0);
	    set_rgb(tape_num, i, 'B', 255);
	    break;
	  case 2:
	    set_rgb(tape_num, i, 'R', 0);
	    set_rgb(tape_num, i, 'G', 255);
	    set_rgb(tape_num, i, 'B', 0);
	    break;
	  case 1:
	    set_rgb(tape_num, i, 'R', 255);
	    set_rgb(tape_num, i, 'G', 255);
	    set_rgb(tape_num, i, 'B', 0);
	    break;
	  case 0:
	    set_rgb(tape_num, i, 'R', 255);
	    set_rgb(tape_num, i, 'G', 0);
	    set_rgb(tape_num, i, 'B', 255);
	    break;
	  }
	}
	if(count[tape_num-1]>=2*tape_leds_num[tape_num-1]-1){
	  count[tape_num-1]=0;
	  increment[tape_num-1][2]=0;
	  set_count = 0;
	}
      }
    }
    count2[tape_num-1]++;
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
