#include "LPC17xx.h"
#include "system_LPC17xx.h"
#include "segsvn.h"

volatile unsigned int ir_count=0;
int n=4;

void eint1_init(void);
void EINT1_IRQHandler(void);

int main(){
	SystemInit();
	segsvn_init();
	eint1_init();
	
	//use in level trigger
	while (1) {
    fourdigidisp(ir_count);
		switch(n){
			case 3: 
        if (!(LPC_GPIO2->FIOPIN & (1U << 11))) {   //high level gone (!) //low level gone 
          LPC_SC->EXTINT = (1U << 1);
          NVIC_ClearPendingIRQ(EINT1_IRQn);
          NVIC_EnableIRQ(EINT1_IRQn);
       }
				break;
			case 4:
				if ((LPC_GPIO2->FIOPIN & (1U << 11))) {   //high level gone (!) //low level gone 
          LPC_SC->EXTINT = (1U << 1);
          NVIC_ClearPendingIRQ(EINT1_IRQn);
          NVIC_EnableIRQ(EINT1_IRQn);
       }
				break;
    }	
  }
}

void eint1_init(void){
	LPC_PINCON->PINSEL4|=(1<<22);
	switch(n){
		case 1:
			//rising edge
		  LPC_SC->EXTMODE|=(1<<1);
		  LPC_SC->EXTPOLAR|=(1<<1); 
		  break;
		case 2://falling edge
			LPC_SC->EXTMODE|=(1<<1);
		  LPC_SC->EXTPOLAR|=(0<<1);
		  break;
		case 3: //high level
	    LPC_SC->EXTMODE&=~(1<<1);
	    LPC_SC->EXTPOLAR|=(1<<1); 
		  break;
	  case 4://low level
	    LPC_SC->EXTMODE&=~(1<<1);
	    LPC_SC->EXTPOLAR&=~(1<<1);
		  break;
	}
	LPC_SC->EXTINT = (1 << 1);
  NVIC_ClearPendingIRQ(EINT1_IRQn);
	ir_count=0;
	switch(n){
		case 1:case 2:
			NVIC_EnableIRQ(EINT1_IRQn);//use in edge trigger
	}
}

void EINT1_IRQHandler(void){
	switch(n){
		case 4:case 3:	
			NVIC_DisableIRQ(EINT1_IRQn); //use in level trigger
	}
	LPC_SC->EXTINT=(1<<1);
	ir_count++;
}
