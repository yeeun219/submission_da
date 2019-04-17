/*
 * motor_execution.c
 *
 * Created: 4/16/2019 9:35:09 AM
 * Author : llje2
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define ENABLE 1
#define MTR_1 2
#define MTR_2 3
#define SW (PINC&(1<<0))

int main ( )
{
	PORTC |= (1<<0); //enable pull-up
	DDRC |= 0b00001110;	 //PC1, PC2, and PC3 as outputs
	PORTC &= ~(1<<ENABLE); //Enable = 0
	PORTC &= ~(1<<MTR_1);  //MTR_1 = 0
	PORTC &= ~(1<<MTR_2);  //MTR_2 = 0
	DDRC |=(1<<0); //PC0 as output
	OCR0A=50;//set the duty cycle of PWM
	
	//FAST PWM, NON INVERTED
	TCCR0A =(1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
	TCCR0B=0X02;//N=8

	while (1)
	{
		PORTC |= (1<<ENABLE);  //Enable = 1

		if(SW != 0) //if PC0 is high
		{
			// Clockwise Rotation
			_delay_ms(1000);
			PORTC |= (1<<MTR_1);     //MTR_1 = 1
			PORTC &= (~(1<<MTR_2));  //MTR_2 = 0
		}
		else{
			// Anti-Clockwise Rotation
			_delay_ms(1000);
			PORTC &= (~(1<<MTR_1)); //MTR_1 = 0
			PORTC |= (1<<MTR_2);    //MTR_2 = 1
		}
		_delay_ms(5000);
		if(OCR0A>250){
			OCR0A=50;
			_delay_ms(1000);}
		else
			OCR0A=OCR0A+25;	
	}
}
