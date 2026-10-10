#ifndef segsvn
#define segsvn

#include "LPC17xx.h"

#define seg_d 0xff<<1
#define seg_1 1<<0
#define seg_2 1<<1
#define seg_3 1<<2
#define seg_4 1<<3
//unsigned char seg_lut[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};//ca
unsigned char seg_lut[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//cc

void delay_ms(unsigned int ms){
	//LPC_SC->PCONP|=(1<<1);//BECAUSE BY DEFAULT IT IS 1(0N)
	LPC_TIM0->PR=25000-1;
	LPC_TIM0->TCR=0X02;
	LPC_TIM0->TCR=0X01;
	while(LPC_TIM0->TC<ms);
	LPC_TIM0->TCR=0X00;
}

void segsvn_init(void){
	LPC_PINCON->PINSEL0&=~(0XFFFFU<<2);
	LPC_PINCON->PINSEL4&=~(0XFFU);
	LPC_GPIO0->FIODIR|=seg_d;
	LPC_GPIO2->FIODIR|=seg_1|seg_2|seg_3|seg_4;
	//LPC_GPIO0->FIOSET = (0xFFU<< 1);
  //LPC_GPIO2->FIOSET = 0x0FU;
}

void fourdigidisp(unsigned int n){
	if (n>=1000){
		LPC_GPIO0->FIOCLR=seg_d;
	  LPC_GPIO0->FIOSET=seg_lut[n/1000]<<1;
	  LPC_GPIO2->FIOCLR=seg_1;
	  delay_ms(5);
	  LPC_GPIO2->FIOSET=seg_1;
	}
	else
		LPC_GPIO2->FIOSET=seg_1;
	if(n>=100){
	  LPC_GPIO0->FIOCLR=seg_d;
	  LPC_GPIO0->FIOSET=seg_lut[(n/100)%10]<<1;
	  LPC_GPIO2->FIOCLR=seg_2;
	  delay_ms(5);
	  LPC_GPIO2->FIOSET=seg_2;
	}
	else
		LPC_GPIO2->FIOSET=seg_2;
	if(n>=10){
	  LPC_GPIO0->FIOCLR=seg_d;
	  LPC_GPIO0->FIOSET=seg_lut[(n/10)%10]<<1;
	  LPC_GPIO2->FIOCLR=seg_3;
	  delay_ms(5);
	  LPC_GPIO2->FIOSET=seg_3;
	}
	else
		LPC_GPIO2->FIOSET=seg_3;
	if(n>=1){
	  LPC_GPIO0->FIOCLR=seg_d;
	  LPC_GPIO0->FIOSET=seg_lut[n%10]<<1;
	  LPC_GPIO2->FIOCLR=seg_4;
	  delay_ms(5);
	  LPC_GPIO2->FIOSET=seg_4;
	}
	else
		LPC_GPIO2->FIOSET=seg_4;
	
}

#endif
