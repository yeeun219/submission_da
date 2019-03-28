/*
 * GccApplication6.c
 *
 * Created: 2019-03-26 am6:51:27
 * Author : llje2
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <avr/interrupt.h>
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Declaration of our functions
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned int data);
void USART_putstring(char* StringPtr);
void USART_putint(int rand_integer); 
void USART_putfloat(char* FloatPtr); 

void InitializeRandomSeed()
{
	srand((unsigned int)time(0));
}

char GetRandomCharacter()
{
	return rand() % 26 + 65 ;
}
 int GetRandomInt(){
	 return rand() % 9+48;
 }

int extraTime=0;

int main(void) {
	USART_init();        //Call the USART initialization code
	InitializeRandomSeed();
	char String[5];//String[] is in fact an array but when we put the text between the " " symbols the compiler threats it as a String and automatically puts the null termination character in the end of the text
	char f_number[3];
	
	 DDRB = 0x01; // setting the LED as an output
	 
	 TCCR0A = (1 << WGM01); // Set CTC Bit
	 OCR0A = 195; // number of ticks we need for our specific time
	 TIMSK0 = (1 << OCIE0A);
	 
	 TCCR0B = (1 << CS02) | (1 << CS00); // use 1024 prescaler
	 sei(); // setting the interrupt

	
	while (1) {      //Infinite loop
		
		for(int i=0;i<5;i++){
			String[i] = GetRandomCharacter();
		}
		USART_putstring(String);//Pass the string to the USART_putstring function and sends it over the serial
		USART_putint(32); //tell from string and random integer
		int rand_integer = GetRandomInt();
		USART_putint(rand_integer);//Pass the random_int to the USART_putstring function and sends it over the serial
		USART_putint(32); //tell from random integer and float
		f_number[0]=GetRandomInt(); //make floating point value
		f_number[1]='.';
		f_number[2]=GetRandomInt();
		USART_putfloat(f_number);//Pass the random_floating point value to the USART_putstring function and sends it over the serial
		
		USART_putint(32); // display SPACE Ascii '32' is space, tell from former and now
		USART_putint(32);
		_delay_ms(1000);
	}

	return 0;
}

ISR(TIMER0_COMPA_vect) // the interrupt service routine(see list of vectors for all interrupt sources!!!!
{
	extraTime++;
	
	if(extraTime > 100)
	{
		PORTB ^= (1<<PORTB0); // toggle LED
		extraTime = 0;
	}
}


void USART_init(void) { //the USART initialization code 

	UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
}

unsigned char USART_receive(void) {
 
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;

}

void USART_send( unsigned int data) { //the USART receive int data code 
 
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;

}



void USART_putstring(char* StringPtr) { //the USART receive string data code 
	int i;
	for(i=0;i<5;i++){ // string length is 5
		USART_send(*StringPtr);
		StringPtr++;
	}

}
void USART_putfloat(char* FloatPtr) { //the USART receive floating value data code
	int i;
	for(i=0;i<3;i++){ //random_floating point value length is 3
		USART_send(*FloatPtr);
		FloatPtr++;
	}

}

void USART_putint(int rand_integer){ //the USART receive int value

		USART_send(rand_integer);
}