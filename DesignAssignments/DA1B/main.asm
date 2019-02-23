;
; AssemblerApplication9.asm
;
; Created: 2019-02-23 오전 8:17:45
; Author : llje2
;
.ORG 0
LDI ZL, LOW($200) ;pointer of STARTDDS
LDI ZH, HIGH($200) 
LDI XL, LOW($400)  ; x pointer that point value storing divisible by 3 
LDI XH, HIGH($400)
LDI YL, LOW($600) ;  y pointer that point value storing not divisible by 3 
LDI YH, HIGH($600)
LDI R20, 12 ; initial value of STARTDDS, increasing by 1
LDI R24, 99 ; counter of fill_up loop
FILL_UP: INC R20
		 ST Z+,R20 ;store at STARTDDS using poiter
		 DEC R24  
	     BREQ SEPERATE_DIVISION ;go SEPERATE_DIVISION to do seperate   
	     RJMP FILL_UP ; fill up of 99times
SEPERATE_DIVISION:  DEC ZL ;decreasing z pointer 
					LDI R24, 99 ; counter of seperate
					SEPERATE: LD R20, Z;load from RAM, r20 store of the rest 
							  MOV R25, R20 ;r25 is the temporary value of loaded value that are used to store in RAM of x pointer
							  DEC ZL ;decreasing z pointer and load 1 data from ram 
							  .DEF NUM = R23
							   MOV NUM, R20;the value of dividend 
							  .DEF DENOMINATOR =R21
							  .DEF QUOTIENT = R22
							   LDI QUOTIENT,0
							   LDI DENOMINATOR, 3
					           L1: INC QUOTIENT ;Subtract until zero or negative, Increasing by one QUOTIENT for each subtraction
								   SUB NUM, DENOMINATOR
								   BRCC L1
							  DEC QUOTIENT ;because of one more time adding 
							  MUL QUOTIENT,DENOMINATOR ; the rest is the value of dividend - QUOTIENT*DENOMINATOR(r0)
							  SUB R20, R0 ;store the rest in r20 
							  BRNE Y_STORE ;if the value of r20 is not 0(not divisible by 3), then go Y_STORE
							  X_STORE: ST X+, R25 ; else go X_STORE
							  JMP NEXT 
							  Y_STORE: ST Y+, R25
							  NEXT: DEC R24 
									BREQ ADD_X
									RJMP SEPERATE
ADD_X: LDI R24, 40;counter of add_x_loop
	   LDI R21,0 ; initialize the upper value of r 20 
	   ADD_X_LOOP: DEC XL
				   LD R20, X ;load the data of pointer x 
				   ADD R16, R20  ;add considering carry overflow
				   ADC R17,R21
				   DEC R24
				   BREQ ADD_Y
				   RJMP ADD_X_LOOP

ADD_Y: LDI R24, 90;counter of add_y_loop
	   LDI R21,0 ; initialize the upper value of r 20 
	   ADD_Y_LOOP: DEC YL
				   LD R20, Y ;load the data of pointer y
				   ADD R18, R20; add considering carry overflow
				   ADC R19,R21
				   DEC R24
				   BREQ END
				   RJMP ADD_Y_LOOP
 END: RJMP END
 