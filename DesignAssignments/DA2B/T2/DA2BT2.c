/*
 * GccApplication1.c
 *
 * Created: 2019-03-04 ¿ÀÈÄ 5:28:14
 * Author : llje2
 */ 
#define	F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	//turn led off
	DDRB |=(1<<5);
	PORTB |=(1<<5);
	
	DDRB |=(1<<2);
	PORTB |=(1<<2); //TURN LED OFF
	//SET PORTC.2 FOR INPUT
	DDRC &=(0<<2);
	PORTC |= (1<<2);
	EICRA = 0x2;//make INT0 falling edge triggered

	EIMSK = (1<<INT0);//enable external interrupt 0
	sei ();//enable interrupts

   
    while (1) //Repeat continuously 
    {	
		PORTB &= ~(1<<2); //turn on 
		_delay_ms(435); //0.435SEC DELAY (60%DC)  
		PORTB |=(1<<2);	//TURN LED OFF
		_delay_ms(290); //0.29SEC DELAY (40%DC)
	
			
    }
	return 0;
}

ISR (INT0_vect)//ISR for external interrupt 0
{
	PORTB &= ~(1<<2); //TURN LED ON
	_delay_ms(1250); // DELAY 1.25sec
}