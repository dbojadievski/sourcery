; Listing generated by Microsoft (R) Optimizing Compiler Version 19.00.24215.1 

	TITLE	C:\Users\dboja\Documents\Visual Studio 2015\Projects\sourcery\Sourcery\computer.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_DATA	SEGMENT
$SG4708	DB	'c', 00H, 'o', 00H, 'm', 00H, 'p', 00H, 'u', 00H, 't', 00H
	DB	'e', 00H, 'r', 00H, '.', 00H, 'c', 00H, 00H, 00H
	ORG $+2
$SG4709	DB	'p', 00H, '_', 00H, 'c', 00H, 'o', 00H, 'm', 00H, 'p', 00H
	DB	'u', 00H, 't', 00H, 'e', 00H, 'r', 00H, 00H, 00H
	ORG $+2
$SG4710	DB	'c', 00H, 'o', 00H, 'm', 00H, 'p', 00H, 'u', 00H, 't', 00H
	DB	'e', 00H, 'r', 00H, '.', 00H, 'c', 00H, 00H, 00H
	ORG $+2
$SG4711	DB	'p', 00H, '_', 00H, 'r', 00H, 'e', 00H, 'g', 00H, '_', 00H
	DB	'f', 00H, 'i', 00H, 'l', 00H, 'e', 00H, 00H, 00H
	ORG $+2
$SG4712	DB	'c', 00H, 'o', 00H, 'm', 00H, 'p', 00H, 'u', 00H, 't', 00H
	DB	'e', 00H, 'r', 00H, '.', 00H, 'c', 00H, 00H, 00H
	ORG $+2
$SG4713	DB	'p', 00H, '_', 00H, 'm', 00H, 'e', 00H, 'm', 00H, 'o', 00H
	DB	'r', 00H, 'y', 00H, '_', 00H, 's', 00H, 't', 00H, 'i', 00H, 'c'
	DB	00H, 'k', 00H, 00H, 00H
	ORG $+2
$SG4721	DB	'c', 00H, 'o', 00H, 'm', 00H, 'p', 00H, 'u', 00H, 't', 00H
	DB	'e', 00H, 'r', 00H, '.', 00H, 'c', 00H, 00H, 00H
	ORG $+2
$SG4722	DB	'p', 00H, '_', 00H, 'c', 00H, 'o', 00H, 'm', 00H, 'p', 00H
	DB	'u', 00H, 't', 00H, 'e', 00H, 'r', 00H, 00H, 00H
_DATA	ENDS
PUBLIC	_computer_initialize
PUBLIC	_computer_free
EXTRN	__wassert:PROC
EXTRN	_memory_stick_free:PROC
EXTRN	_free:PROC
; Function compile flags: /Odtp
_TEXT	SEGMENT
_p_computer$ = 8					; size = 4
_computer_free PROC
; File c:\users\dboja\documents\visual studio 2015\projects\sourcery\sourcery\computer.c
; Line 20
	push	ebp
	mov	ebp, esp
; Line 21
	cmp	DWORD PTR _p_computer$[ebp], 0
	jne	SHORT $LN3@computer_f
	push	21					; 00000015H
	push	OFFSET $SG4721
	push	OFFSET $SG4722
	call	__wassert
	add	esp, 12					; 0000000cH
$LN3@computer_f:
; Line 22
	mov	ecx, DWORD PTR _p_computer$[ebp]
	mov	edx, DWORD PTR [ecx]
	push	edx
	call	_free
	add	esp, 4
; Line 23
	mov	eax, DWORD PTR _p_computer$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	push	ecx
	call	_memory_stick_free
	add	esp, 4
; Line 24
	pop	ebp
	ret	0
_computer_free ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
_TEXT	SEGMENT
_p_computer$ = 8					; size = 4
_p_reg_file$ = 12					; size = 4
_p_memory_stick$ = 16					; size = 4
_computer_initialize PROC
; File c:\users\dboja\documents\visual studio 2015\projects\sourcery\sourcery\computer.c
; Line 9
	push	ebp
	mov	ebp, esp
; Line 10
	cmp	DWORD PTR _p_computer$[ebp], 0
	jne	SHORT $LN3@computer_i
	push	10					; 0000000aH
	push	OFFSET $SG4708
	push	OFFSET $SG4709
	call	__wassert
	add	esp, 12					; 0000000cH
$LN3@computer_i:
; Line 11
	cmp	DWORD PTR _p_reg_file$[ebp], 0
	jne	SHORT $LN4@computer_i
	push	11					; 0000000bH
	push	OFFSET $SG4710
	push	OFFSET $SG4711
	call	__wassert
	add	esp, 12					; 0000000cH
$LN4@computer_i:
; Line 12
	cmp	DWORD PTR _p_memory_stick$[ebp], 0
	jne	SHORT $LN5@computer_i
	push	12					; 0000000cH
	push	OFFSET $SG4712
	push	OFFSET $SG4713
	call	__wassert
	add	esp, 12					; 0000000cH
$LN5@computer_i:
; Line 14
	mov	eax, DWORD PTR _p_computer$[ebp]
	mov	ecx, DWORD PTR _p_reg_file$[ebp]
	mov	DWORD PTR [eax], ecx
; Line 15
	mov	edx, DWORD PTR _p_computer$[ebp]
	mov	eax, DWORD PTR _p_memory_stick$[ebp]
	mov	DWORD PTR [edx+4], eax
; Line 16
	pop	ebp
	ret	0
_computer_initialize ENDP
_TEXT	ENDS
END
