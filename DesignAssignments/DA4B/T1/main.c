/*
 * step_motor.c
 *
 * Created: 4/26/2019 7:17:10 AM
 * Author : llje2
 */ 

#include <avr/io.h>
#define  F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	int period;
	DDRC = 0x1F; //make PORTC lower pin as output
	period=10; //set period in between two steps 
    /* Replace with your application code */
    while (1) 
    {
		//rotate stepper motor anticlockwise with full step sequence	
		PORTC=0X09;
		_delay_ms(period);
		PORTC=0X03;
		_delay_ms(period);
		PORTC=0X06;
		_delay_ms(period);
		PORTC=0X0C;
		_delay_ms(period);

    }
}

