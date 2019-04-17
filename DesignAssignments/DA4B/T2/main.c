/*
 * servo_motor.c
 *
 * Created: 4/30/2019 10:59:07 AM
 * Author : llje2
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{	
	//configure Timer1
	TCCR1A |=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11); //NON inverted PWM
	//PRESCALER=64MODE 14(FAST PWM)
	TCCR1B |=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);
	ICR1=4999; //fPWM=50HZ(PERIOD =20MS STANDARD)
	DDRB|=(1<<PB1);
    /* Replace with your application code */
    while (1) 
    {
		OCR1A=70; //0 degree
		_delay_ms(1000); //wait for 1sec
		OCR1A=375; //90 degree
		_delay_ms(1000);
		OCR1A=600; //180degree
		_delay_ms(1000);

		
    }
}

