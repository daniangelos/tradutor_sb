section .text
global _start
_start:
add eax, [var11]
mov ebx, [var12]
mov [var10], ebx
mov ecx, var12
call input
sub byte [ecx], 0x30
mov ecx, var12
add byte [ecx], 0x30
call output
mov eax, 1
mov ebx, 0
int 80h

input:
pusha
mov eax, 3
mov ebx, 0
mov edx, 1
int 0x80
popa
ret
output:
pusha
mov eax, 4
mov ebx, 1
mov edx, 1
int 0x80
popa
ret

section .data
var10: dw 1
var11: dw 3

section .bss
var12: resw 1
