;
; interrupt_c_b.asm
;
; Created: 2019-03-14 오전 9:19:16
; Author : llje2
;

.INCLUDE <M328pDEF.INC>
.ORG 0	;location for reset
	JMP	MAIN
.ORG 0x02	 ;location for EXT_INT0
	JMP	EX0_ISR		



MAIN:
	SBI DDRB,5 //TURN OFF THE D1LED
	SBI PORTB,5 
	CBI DDRC,2 //make portc.2 input
	SBI	DDRB, 2
	REPEAT:	SBI		PORTB, 2	   //Sets pin (PB2) high
		    RCALL	DELAY_1		   //0.435SEC DELAY (60%DC)  
		    CBI		PORTB, 2	   //Sets pin (PB2) low
		    RCALL	DELAY_2		   //0.29SEC DELAY (40%DC)

	LDI	R20,HIGH(RAMEND)
	OUT	SPH,R20
	LDI	R20,LOW(RAMEND)
	OUT	SPL,R20 ;initialize stack

	LDI R20,0X2 ;make INT0 falling edge triggered
	STS EICRA,R20		
	SBI	DDRB,2       ;PC.2 = output
	SBI	PORTD,2     ;pull-up activated
	LDI	R20,1<<INT0 ;Enable INT0
	OUT	EIMSK,R20
	SEI	      ;Set I (Enable Interrupts)
	RJMP REPEAT
HERE:JMP	HERE	
	
EX0_ISR: 
	 CBI PORTB,2   
	 RCALL DELAY_3	 //1.25SEC delay
	 RCALL DELAY_2	 
	RETI

DELAY_1:	    LDI		R16, 40			   //Create a Delay of 60%DC
LOOP1_1:	    LDI		R17, 87
LOOP2_1:	    LDI		R18, 109
LOOP3_1:        NOP		
		DEC		R18
		BRNE	LOOP3_1

		DEC		R17
		BRNE	LOOP2_1

		DEC		R16
		BRNE	LOOP1_1
		RET


DELAY_2:	    LDI		R16, 23			   //Create a Delay of 40%DC
LOOP1_2:	        LDI		R17, 58
LOOP2_2:	        LDI		R18, 72
LOOP3_2:	        NOP		
		DEC		R18
		BRNE	LOOP3_2

		DEC		R17
		BRNE	LOOP2_2

		DEC		R16
		BRNE	LOOP1_2
		RET


DELAY_3:	    LDI		R16, 80			   //Create a Delay of 1s
LOOP1_3:	    LDI		R17, 200
LOOP2_3:	    LDI		R18, 250
LOOP3_3:	    NOP		
		DEC		R18
		BRNE	LOOP3_3

		DEC		R17
		BRNE	LOOP2_3

		DEC		R16
		BRNE	LOOP1_3
		RET