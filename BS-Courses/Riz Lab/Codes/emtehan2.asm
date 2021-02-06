;Hossein Rahmatizadeh
;88521139
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.386

.MODEL FLAT
ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

GetStdHandle PROTO NEAR32 stdcall,nStdHandle:DWORD

ReadFile PROTO NEAR32 stdcall,hFile:DWORD, lpBuffer:NEAR32, nNumberOfCharsToRead:DWORD,
lpNumberOfBytesRead:NEAR32, lpOverlapped:NEAR32

WriteFile PROTO NEAR32 stdcall,hFile:DWORD, lpBuffer:NEAR32, nNumberOfCharsToWrite:DWORD,
lpNumberOfBytesWritten:NEAR32, lpOverlapped:NEAR32

CreateFileA PROTO NEAR32 stdcall,lpFileName:NEAR32, access:DWORD, shareMode:DWORD,
lpSecurity:NEAR32, creation:DWORD, attributes:DWORD, copyHandle:DWORD

CloseHandle PROTO NEAR32 stdcall,fHandle:DWORD



std_output		EQU		-11
STD_INPUT		EQU		-10
GENERIC_READ	EQU		80000000h
OPEN_EXITING	EQU		3
cr		EQU		0dh
Lf		EQU		0ah
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.STACK	4096

.DATA

	crLf		BYTE	0Ah,0Dh
	myBuffer	BYTE	16 DUP(?)
	myoutput	BYTE	"what is your file name? "
	existprogram BYTE	"m[ore] or q[uit]?"
	NameOfFile	BYTE 16 DUP(?)
	Answer		BYTE 5 DUP(?)
	read		DWORD ?
	read1		DWORD ?
	alarm		BYTE  ?
	out_std		DWORD ?
	in_std		DWORD ?
	HedearFile	DWORD ?
	written		DWORD ?
	itsline		DWORD 20
	string		BYTE 48 DUP(?)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.code
_start:
	INVOKE  GetStdHandle,STD_output
	mov		out_std,eax
	INVOKE  GetStdHandle,std_input
	mov		in_std,eax
	INVOKE	WriteFile,out_std,NEAR32 PTR myoutput,sizeof myoutput,NEAR32 PTR written,0
	INVOKE	ReadFile,in_std,NEAR32 PTR NameOfFile,sizeof NameOfFile,NEAR32 PTR read,0
	mov		ecx,read
	mov		BYTE ptr [NameOfFile+ecx-2],0
	INVOKE  CreateFileA,NEAR32 PTR NameOfFile,generic_read,0,0,open_exiting,0,0
	mov		HedearFile,eax
begining:
	dec		itsline
	INVOKE	ReadFile,HedearFile,NEAR32 PTR myBuffer,16,NEAR32 PTR read,0
	mov		ecx,16
	mov		edx,0
	mov		esi,0
LoopLabel1:
	mov		al,myBuffer[esi]
	shr		al,4
	mov		ah,myBuffer[esi]
	and		ah,01111b
	cmp		al,0
	jl		myPosition1
	cmp		al,9
	jg		myPosition1
	or		al,30h
	mov		string[edx],al
	jmp		myPosition2
myPosition1:
	add		al,'a'- 10
	mov		string[edx],al
myPosition2:
	inc		edx
	cmp		ah,0
	jl		myPosition3
	cmp		ah,9
	jg		myPosition3
	or		ah,30h
	mov		string[edx],ah
	jmp		myPosition4
myPosition3:
	add		ah,'a'- 10
	mov		string[edx],ah
myPosition4:
	inc		edx
	mov		string[edx],' '
	inc		edx
	inc		esi
	loop	LoopLabel1
	INVOKE	WriteFile,out_std,near32 PTR  string,48,NEAR32 PTR written,0
	mov		ebx,0
WhileLabel:
	cmp		myBuffer[ebx],0
	jl		myPosition5
	cmp		myBuffer[ebx],1fh
	jg		myPosition5
	mov		alarm,'.'
	inc		ebx
	INVOKE	WriteFile,out_std,near32 PTR  alarm,1,NEAR32 PTR written,0
	jmp		myPosition6
myPosition5:
	push	ebx
	mov		bl,myBuffer[ebx]
	mov		alarm,bl
	pop		ebx
	inc		ebx
	INVOKE	WriteFile,out_std,near32 PTR  alarm,1,NEAR32 PTR written,0
myPosition6:
	cmp		ebx,16
	jl		WhileLabel
	INVOKE	WriteFile,out_std,near32 PTR  crlf,2,NEAR32 PTR written,0
	cmp		itsline, 0
	je		QuestionLabel
	cmp		read,16
	jnl		begining
QuestionLabel:
	INVOKE	WriteFile, out_std, NEAR32 PTR existprogram, sizeof existprogram, NEAR32 PTR written, 0
	INVOKE	ReadFile, in_std, NEAR32 PTR Answer, sizeof Answer, NEAR32 PTR read1, 0
	cmp		Answer, "m"
	jne		myendprogram
	mov		itsline, 20
	jmp		begining
myendprogram:
	INVOKE	ExitProcess, 0
		public _start
end 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;