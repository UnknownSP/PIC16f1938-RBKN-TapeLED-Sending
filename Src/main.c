#include "main.h"
#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>

void init(void);
static void blink(BlinkMode_t mode, int tape_num);
void set_rgb(int tape_num, int lednum, char color, int set_data);
int get_rgb(int tape_num, int lednum, char color);

void main(void) {

  int count=0;
  
  init();
  while(true){
    if(count==8){
      RB1 = !RB1;
      count = 0;
    }
    blink(INCREMENT,1);
    blink(INCREMENT,2);
    blink(INCREMENT,3);
    blink(INCREMENT,4);
    blink(RAINBOW,5);
    blink(YELLOW,6);
    blink(PURPLE,7);
    blink(BLINK_RED,8);
    count++;
  }
}

static void blink(BlinkMode_t mode, int tape_num){
  
  static int count[8]={0,0,0,0,0,0,0,0};
  static int count2[8]={0,0,0,0,0,0,0,0};
  static int increment[8][3]={
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
  };
  static int RGB[8][3]={
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
  };
  static int RGB_BLINK[8][3]={
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
  };
  int i,j;
  static int red[8],green[8],blue[8];
  static char rgb;
  static bool change_binary = true;
  static bool setup[8] ={false,false,false,false,false,false,false,false};
  int set_count = 0;
  
  switch(mode){
  case NONE:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 0);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 0);
    }
    SendData(tape_num);
    //__delay_ms(10);
    break;
  case DIMING_RAINBOW:
  case DIMING_RED:
  case DIMING_GREEN:
  case DIMING_BLUE:
  case DIMING_YELLOW:
  case DIMING_PURPLE:
    switch(mode){
    case DIMING_RAINBOW:
      RGB[tape_num-1][0] = 1;
      RGB[tape_num-1][1] = 11;
      RGB[tape_num-1][2] = 5;
      break;
    case DIMING_RED:
      RGB[tape_num-1][0] = 13;
      RGB[tape_num-1][1] = 0;
      RGB[tape_num-1][2] = 0;
      break;
    case DIMING_GREEN:
      RGB[tape_num-1][0] = 0;
      RGB[tape_num-1][1] = 13;
      RGB[tape_num-1][2] = 0;
      break;
    case DIMING_BLUE:
      RGB[tape_num-1][0] = 0;
      RGB[tape_num-1][1] = 0;
      RGB[tape_num-1][2] = 13;
      break;
    case DIMING_YELLOW:
      RGB[tape_num-1][0] = 13;
      RGB[tape_num-1][1] = 13;
      RGB[tape_num-1][2] = 0;
      break;
    case DIMING_PURPLE:
      RGB[tape_num-1][0] = 13;
      RGB[tape_num-1][1] = 0;
      RGB[tape_num-1][2] = 13;
      break;
    }
    if(count[tape_num-1]==0){
      for(i=0;i<tape_leds_num[tape_num-1];i++){
	set_rgb(tape_num, i, 'R', RGB[tape_num-1][0]*diming[i%20]);
	set_rgb(tape_num, i, 'G', RGB[tape_num-1][1]*diming[i%20]);
	set_rgb(tape_num, i, 'B', RGB[tape_num-1][2]*diming[i%20]);
      }
    }
    count[tape_num-1]++;
    for(i=0;i<tape_leds_num[tape_num-1];i++){
      if(get_rgb(tape_num,i,'R')>0){
	if(get_rgb(tape_num,i,'R')%2==0){
	  set_rgb(tape_num, i, 'R', get_rgb(tape_num,i,'R')+4);
	}else{
	  set_rgb(tape_num, i, 'R', get_rgb(tape_num,i,'R')-4);
	}
      }
      if(get_rgb(tape_num,i,'R')>247){
	set_rgb(tape_num, i, 'R', 245);
      }else if(get_rgb(tape_num,i,'R')<12 && get_rgb(tape_num,i,'R')>0){
	set_rgb(tape_num, i, 'R', 12);
      }

      if(get_rgb(tape_num,i,'G')>0){
	if(get_rgb(tape_num,i,'G')%2==0){
	  set_rgb(tape_num, i, 'G', get_rgb(tape_num,i,'G')+4);
	}else{
	  set_rgb(tape_num, i, 'G', get_rgb(tape_num,i,'G')-4);
	}
      }
      if(get_rgb(tape_num,i,'G')>247){
	set_rgb(tape_num, i, 'G', 245);
      }else if(get_rgb(tape_num,i,'G')<12 && get_rgb(tape_num,i,'G')>0){
	set_rgb(tape_num, i, 'G', 12);
      }

      if(get_rgb(tape_num,i,'B')>0){
	if(get_rgb(tape_num,i,'B')%2==0){
	  set_rgb(tape_num, i, 'B', get_rgb(tape_num,i,'B')+4);
	}else{
	  set_rgb(tape_num, i, 'B', get_rgb(tape_num,i,'B')-4);
	}
      }
      if(get_rgb(tape_num,i,'B')>247){
	set_rgb(tape_num, i, 'B', 245);
      }else if(get_rgb(tape_num,i,'B')<12 && get_rgb(tape_num,i,'B')>0){
	set_rgb(tape_num, i, 'B', 12);
      }
    }
    SendData(tape_num);
    break;
  case BINARY_RED:
  case BINARY_GREEN:
  case BINARY_BLUE:
    switch(mode){
    case BINARY_RED:
      rgb = 'R';
      break;
    case BINARY_GREEN:
      rgb = 'G';
      break;
    case BINARY_BLUE:
      rgb = 'B';
      break;
    }
    if(count2[tape_num-1]%1==0){
      for(i=0;i<tape_leds_num[tape_num-1];i++){
	for(j=0;j<i;j++){
	  if(get_rgb(tape_num,j,rgb)!=0){
	    change_binary = false;
	  }
	}
	if(i==0){
	  if(get_rgb(tape_num,0,rgb)==0){
	    set_rgb(tape_num, 0, rgb, 255);
	  }else{set_rgb(tape_num, 0, rgb, 0);}
	  continue;
	}
	if(change_binary){
	  if(get_rgb(tape_num,i,rgb)==0){
	    set_rgb(tape_num, i, rgb, 255);
	  }else{set_rgb(tape_num, i, rgb, 0);}
	}
	change_binary = true;
      }
    }
    count2[tape_num-1]++;
    SendData(tape_num);
    break;
  case RAINBOW:
    if(count2[tape_num-1]%3==0){
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
    }
    count2[tape_num-1]++;
    SendData(tape_num);
    //__delay_ms(10);
    break;
    
  case RED:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 255);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 0);
    }
    SendData(tape_num);
    //__delay_ms(10);
    break;
    
  case GREEN:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 0);
      set_rgb(tape_num, i, 'G', 255);
      set_rgb(tape_num, i, 'B', 0);
    }
    SendData(tape_num);
    //__delay_ms(10);
    break;
    
  case BLUE:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 0);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 255);
    }
    SendData(tape_num);
    //__delay_ms(10);
    break;

  case YELLOW:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 255);
      set_rgb(tape_num, i, 'G', 255);
      set_rgb(tape_num, i, 'B', 0);
    }
    SendData(tape_num);
    //__delay_ms(10);
    break;

  case PURPLE:
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', 255);
      set_rgb(tape_num, i, 'G', 0);
      set_rgb(tape_num, i, 'B', 255);
    }
    SendData(tape_num);
    //__delay_ms(10);
    break;

  case BLINK_RED:
  case BLINK_GREEN:
  case BLINK_BLUE:
  case BLINK_YELLOW:
  case BLINK_PURPLE:
    switch(mode){
    case BLINK_RED:
      RGB_BLINK[tape_num-1][0] = 1;
      RGB_BLINK[tape_num-1][1] = 0;
      RGB_BLINK[tape_num-1][2] = 0;
      break;
    case BLINK_GREEN:
      RGB_BLINK[tape_num-1][0] = 0;
      RGB_BLINK[tape_num-1][1] = 1;
      RGB_BLINK[tape_num-1][2] = 0;
      break;
    case BLINK_BLUE:
      RGB_BLINK[tape_num-1][0] = 0;
      RGB_BLINK[tape_num-1][1] = 0;
      RGB_BLINK[tape_num-1][2] = 1;
      break;
    case BLINK_YELLOW:
      RGB_BLINK[tape_num-1][0] = 1;
      RGB_BLINK[tape_num-1][1] = 1;
      RGB_BLINK[tape_num-1][2] = 0;
      break;
    case BLINK_PURPLE:
      RGB_BLINK[tape_num-1][0] = 1;
      RGB_BLINK[tape_num-1][1] = 0;
      RGB_BLINK[tape_num-1][2] = 1;
      break;
    }
    switch(count[tape_num-1]){
    case 1:
      red[tape_num-1] = RGB_BLINK[tape_num-1][0]   * 255;
      green[tape_num-1] = RGB_BLINK[tape_num-1][1] * 255;
      blue[tape_num-1] = RGB_BLINK[tape_num-1][2]  * 255;
      break;
    case 8:
      red[tape_num-1] = RGB_BLINK[tape_num-1][0]   * 0;
      green[tape_num-1] = RGB_BLINK[tape_num-1][1] * 0;
      blue[tape_num-1] = RGB_BLINK[tape_num-1][2]  * 0;
      break;
    case 15:
      red[tape_num-1] = RGB_BLINK[tape_num-1][0]   * 255;
      green[tape_num-1] = RGB_BLINK[tape_num-1][1] * 255;
      blue[tape_num-1] = RGB_BLINK[tape_num-1][2]  * 255;
      break;
    case 22:
      red[tape_num-1] = RGB_BLINK[tape_num-1][0]   * 0;
      green[tape_num-1] = RGB_BLINK[tape_num-1][1] * 0;
      blue[tape_num-1] = RGB_BLINK[tape_num-1][2]  * 0;
      break;
    case 49:
      count[tape_num-1] = 0;
      break;
    }
    for(i=0; i<tape_leds_num[tape_num-1]; i++){
      set_rgb(tape_num, i, 'R', red[tape_num-1]);
      set_rgb(tape_num, i, 'G', green[tape_num-1]);
      set_rgb(tape_num, i, 'B', blue[tape_num-1]);
    }
    count[tape_num-1]++;
    SendData(tape_num);
    //__delay_ms(10);
    break;

  case INCREMENT:
    if(count2[tape_num-1]%5==0){
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
    //__delay_ms(10);
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
  case 5:
    switch(color){
    case 'R':
      R5[lednum] = set_data;
      break;
    case 'G':
      G5[lednum] = set_data;
      break;
    case 'B':
      B5[lednum] = set_data;
      break;
    }
    break;
    
  case 6:
    switch(color){
    case 'R':
      R6[lednum] = set_data;
      break;
    case 'G':
      G6[lednum] = set_data;
      break;
    case 'B':
      B6[lednum] = set_data;
      break;
    }
    break;
  case 7:
    switch(color){
    case 'R':
      R7[lednum] = set_data;
      break;
    case 'G':
      G7[lednum] = set_data;
      break;
    case 'B':
      B7[lednum] = set_data;
      break;
    }
    break;
  case 8:
    switch(color){
    case 'R':
      R8[lednum] = set_data;
      break;
    case 'G':
      G8[lednum] = set_data;
      break;
    case 'B':
      B8[lednum] = set_data;
      break;
    }
    break;
  }
}

int get_rgb(int tape_num, int lednum, char color){
  int return_rgb = 0;
  switch(tape_num){
  case 1:
    switch(color){
    case 'R':
      return_rgb = R1[lednum];
      break;
    case 'G':
      return_rgb = G1[lednum];
      break;
    case 'B':
      return_rgb = B1[lednum];
      break;
    }
    break;
  case 2:
    switch(color){
    case 'R':
      return_rgb = R2[lednum];
      break;
    case 'G':
      return_rgb = G2[lednum];
      break;
    case 'B':
      return_rgb = B2[lednum];
      break;
    }
    break;
  case 3:
    switch(color){
    case 'R':
      return_rgb = R3[lednum];
      break;
    case 'G':
      return_rgb = G3[lednum];
      break;
    case 'B':
      return_rgb = B3[lednum];
      break;
    }
    break;
  case 4:
    switch(color){
    case 'R':
      return_rgb = R4[lednum];
      break;
    case 'G':
      return_rgb = G4[lednum];
      break;
    case 'B':
      return_rgb = B4[lednum];
      break;
    }
    break;
  case 5:
    switch(color){
    case 'R':
      return_rgb = R5[lednum];
      break;
    case 'G':
      return_rgb = G5[lednum];
      break;
    case 'B':
      return_rgb = B5[lednum];
      break;
    }
    break;
  case 6:
    switch(color){
    case 'R':
      return_rgb = R6[lednum];
      break;
    case 'G':
      return_rgb = G6[lednum];
      break;
    case 'B':
      return_rgb = B6[lednum];
      break;
    }
    break;
  case 7:
    switch(color){
    case 'R':
      return_rgb = R7[lednum];
      break;
    case 'G':
      return_rgb = G7[lednum];
      break;
    case 'B':
      return_rgb = B7[lednum];
      break;
    }
    break;
  case 8:
    switch(color){
    case 'R':
      return_rgb = R8[lednum];
      break;
    case 'G':
      return_rgb = G8[lednum];
      break;
    case 'B':
      return_rgb = B8[lednum];
      break;
    }
    break;
  }
  return return_rgb;
}

void init(void){

  // Set oscilation
  OSCCON = 0xF0; //PLL　Enable

  // Set pin mode
  ANSELA = 0b00000000;
  ANSELB = 0b00000000;
  TRISA  = 0b00000000;
  TRISB  = 0b00000000;
  TRISC  = 0b00000000;
  
}

void interrupt  HAND(void){
    
}
