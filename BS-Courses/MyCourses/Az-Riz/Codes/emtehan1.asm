;hossein rahmatizadeh 
;88521139

.386
.MODEL FLAT
.LIST

ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

INCLUDE io.h            

cr      EQU     0dh    
Lf      EQU     0ah    

.STACK  4096           

.DATA                  

prompt1 			BYTE	"number of coins 100 rial ",0
prompt2				BYTE	"number of coins 250 rial ",0
prompt3 			BYTE	"number of coins 500 rial ",0
prompt4 			BYTE	"number of coins 1000 rial ",0

value				BYTE 20 DUP(?)

NumberOfCoins		DWORD 0
sumofwhole			DWORD 0

prompt5				BYTE	"There are "
valueNumberOfCoins	BYTE 16 DUP(?)
prompt6				BYTE " coins worth "
costStringz			BYTE 16 DUP(?)
prompt7				BYTE " rials",cr,Lf,0

.CODE
	
_start:
	mov	ecx,0
	output prompt1
	input value,16
	atod value
	add ecx,eax
	mov ebx,100
	mul	ebx
	mov	NumberOfCoins,eax
	output prompt2
	input value,16
	atod value
	add ecx,eax
	mov ebx,250
	mul ebx
	add NumberOfCoins,eax
	output prompt3
	input value,16
	atod value
	add ecx,eax
	mov ebx,500
	mul ebx
	add NumberOfCoins,eax

	output prompt4
	input value,16
	atod value
	add ecx,eax
	mov ebx,1000
	mul ebx
	add NumberOfCoins,eax



	dtoa	valueNumberOfCoins,ecx
	dtoa	costStringz,NumberOfCoins
	
	output	prompt5
	output	prompt6
	output	prompt7

	INVOKE  ExitProcess, 0  

PUBLIC _start 



END                           