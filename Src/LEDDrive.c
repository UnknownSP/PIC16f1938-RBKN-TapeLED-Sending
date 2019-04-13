#include <pic16f1938.h>
#include "LEDDrive.h"

#define DATA_HI(){LATBbits.LATB0=1;}
#define DATA_LOW(){LATBbits.LATB0=0;}

void SendDat(char dat){
  //asm("disi #382");
    if(dat>>7&0x01){
      DATA_HI();
      asm("nop");asm("nop");asm("nop");
      DATA_LOW();
    }else{
      DATA_HI();
      asm("nop");
      DATA_LOW();
    }
    if(dat>>6&0x01){
      DATA_HI();
      asm("nop");asm("nop");asm("nop");
      DATA_LOW();
    }else{
      DATA_HI();
      asm("nop");
      DATA_LOW();
    }
    if(dat>>5&0x01){
      DATA_HI();
      asm("nop");asm("nop");asm("nop");
      DATA_LOW();
    }else{
      DATA_HI();
      asm("nop");
      DATA_LOW();
    }
    if(dat>>4&0x01){
      DATA_HI();
      asm("nop");asm("nop");asm("nop");
      DATA_LOW();
    }else{
      DATA_HI();
      DATA_LOW();
    }
    if(dat>>3&0x01){
      DATA_HI();
      asm("nop");asm("nop");asm("nop");
      DATA_LOW();
    }else{
      DATA_HI();
      asm("nop");
      DATA_LOW();
    }
    if(dat>>2&0x01){
      DATA_HI();
      asm("nop");asm("nop");asm("nop");
      DATA_LOW();
    }else{
      DATA_HI();
      asm("nop");
      DATA_LOW();
    }
    if(dat>>1&0x01){
      DATA_HI();
      asm("nop");asm("nop");asm("nop");
      DATA_LOW();
    }else{
      DATA_HI();
      asm("nop");
      DATA_LOW();
    }
    if(dat>>0&0x01){
      DATA_HI();
      asm("nop");asm("nop");asm("nop");
      DATA_LOW();
    }else{
      DATA_HI();
      asm("nop");
      DATA_LOW();
    }
    
}

void SendData(void){
#if(LEDs > 0)
  SendDat(G[0]);//RedData
  SendDat(R[0]);//GreenData
  SendDat(B[0]);//Bluedata
#endif
#if(LEDs > 1)
  SendDat(G[1]);//RedData
  SendDat(R[1]);//GreenData
  SendDat(B[1]);//BlueData
#endif
#if(LEDs > 2)
  SendDat(G[2]);//RedData
  SendDat(R[2]);//GreenData
  SendDat(B[2]);//BlueData
#endif
#if(LEDs > 3)
  SendDat(G[3]);//RedData
  SendDat(R[3]);//GreenData
  SendDat(B[3]);//BlueData
#endif
#if(LEDs > 4)
  SendDat(G[4]);//RedData
  SendDat(R[4]);//GreenData
  SendDat(B[4]);//BlueData
#endif
#if(LEDs > 5)
  SendDat(G[5]);//RedData
  SendDat(R[5]);//GreenData
  SendDat(B[5]);//BlueData
#endif
#if(LEDs > 6)
  SendDat(G[6]);//RedData
  SendDat(R[6]);//GreenData
  SendDat(B[6]);//BlueData
#endif
#if(LEDs > 7)
  SendDat(G[7]);//RedData
  SendDat(R[7]);//GreenData
  SendDat(B[7]);//BlueData
#endif
#if(LEDs > 8)
  SendDat(G[8]);//RedData
  SendDat(R[8]);//GreenData
  SendDat(B[8]);//BlueData
#endif
#if(LEDs > 9)
  SendDat(G[9]);//RedData
  SendDat(R[9]);//GreenData
  SendDat(B[9]);//BlueData
#endif
#if(LEDs > 10)
  SendDat(G[10]);//RedData
  SendDat(R[10]);//GreenData
  SendDat(B[10]);//BlueData
#endif
#if(LEDs > 11)
  SendDat(G[11]);//RedData
  SendDat(R[11]);//GreenData
  SendDat(B[11]);//BlueData
#endif
#if(LEDs > 12)
  SendDat(G[12]);//RedData
  SendDat(R[12]);//GreenData
  SendDat(B[12]);//BlueData
#endif
#if(LEDs > 13)
  SendDat(G[13]);//RedData
  SendDat(R[13]);//GreenData
  SendDat(B[13]);//BlueData
#endif
#if(LEDs > 14)
  SendDat(G[14]);//RedData
  SendDat(R[14]);//GreenData
  SendDat(B[14]);//BlueData
#endif
#if(LEDs > 15)
  SendDat(G[15]);//RedData
  SendDat(R[15]);//GreenData
  SendDat(B[15]);//BlueData
#endif
#if(LEDs > 16)
  SendDat(G[16]);//RedData
  SendDat(R[16]);//GreenData
  SendDat(B[16]);//BlueData
#endif
#if(LEDs > 17)
  SendDat(G[17]);//RedData
  SendDat(R[17]);//GreenData
  SendDat(B[17]);//BlueData
#endif
#if(LEDs > 18)
  SendDat(G[18]);//RedData
  SendDat(R[18]);//GreenData
  SendDat(B[18]);//BlueData
#endif
#if(LEDs > 19)
  SendDat(G[19]);//RedData
  SendDat(R[19]);//GreenData
  SendDat(B[19]);//BlueData
#endif
#if(LEDs > 20)
  SendDat(G[20]);//RedData
  SendDat(R[20]);//GreenData
  SendDat(B[20]);//BlueData
#endif
}
