; Emad Aghajani 		88521344
; Hosein Rahmatizade 	88521139
; Abolfazl Ravaghi		88522056

.INCLUDE "m1280def.inc"

.DSEG
.ORG SRAM_START	   ; Safe Area of Data Memory for Variables (After Registers)


.CSEG

			.ORG 0X00
			RJMP START
	
			.ORG OC0Aaddr			; for CTC Intrupt
			RJMP TC0_OC0A_ISR


			.ORG 0X80		; Safe Area of Code Segment
START:
		ldi r16 ,high(ramend)
		out sph , r16
		ldi r16 ,low(ramend)
		out spl , r16
		ser r16

		SEI  


		LDI R16,0x05
		OUT TCCR0B,R16
		LDI R16,0x02
		OUT TCCR0A,R16
		STS TIMSK0,R16

		LDI R16,54
		OUT OCR0A,R16



		LDI R16,0xFF
		OUT DDRF ,R16	; F : LED Select 	** OUT

		LDI R16,0xFF
		STS DDRK ,R16	; K : LED			** STS

		LDI R17, 0x10	; R17 => Select
		OUT	PORTF,R17

	;	LDI R16,0xFF
	;	STS	PORTK,R16

		LDI R27, 0		; Sec Counter
		LDI R20,0x03	; TIME STRING
		LDI R21,0x05	; TIME STRING
		LDI R22,0x00	; TIME STRING
		LDI R23,0x00	; TIME STRING




MainLoop:
			
		
		

		CPI R17,0x10
		BRNE NEXT1
		MOV R16,R23
		RJMP SHOW
NEXT1:
		CPI R17,0x20
		BRNE NEXT2
		MOV R16,R22
		RJMP SHOW
NEXT2:
		CPI R17,0x40
		BRNE NEXT3
		MOV R16,R21
		RJMP SHOW
NEXT3:
		MOV R16,R20

SHOW:
		Call Convert	// Convert R16 into R16
		STS	PORTK,R16
		RJMP MainLoop
 


INCREASETIME:
		INC R20
		CPI R20,10
		BRNE DONE
		CLR R20
		INC R21
		CPI R21,6
		BRNE DONE
		CLR R21
		INC R22
		CPI R22,10
		BRNE DONE
		CLR R22
		INC R23
		CPI R23,6
		BRNE DONE
		CLR R23

DONE:
	RET
		

Table:		.DB		0xEB,0x88,0xB3,0xBA,0xD8,0x7A,0x7B,0xA8,0xFB,0xFA


Convert:
		LDI ZL,LOW(Table*2)		;2 is because of: Flash width is 2Bytes		; Z = R30 + R31 
		LDI ZH,HIGH(Table*2)
		ADD ZL,R16
		CLR R16
		ADC ZH,R16
		LPM R16,Z
		RET


TC0_OC0A_ISR:

	ROL R17
	CPI R17,0x00
	BRNE XXX
	LDI R17,0x10
XXX:
	OUT	PORTF,R17	
	INC R27
	CPI R27,200
	BRNE INEXIT
	CLR R27

	CALL INCREASETIME	; 1Sec Past

INEXIT: 
	RETI




				

