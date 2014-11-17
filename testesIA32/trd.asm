section .data
lol: dw 10

section .bss
n1: resw 1
n2: resw 1
n3: resw 4

section .text
global _start
_start:

add eax, [n1]	
sub eax, [n2]
mov eax, [n3+1]
mov ecx, 8
add ecx, 0x30
mov [n1], ecx
call output
mov eax, 1
mov ebx, 0
int 0x80

output:
pusha
mov eax, 4
mov ebx, 1 
mov ecx, n1 
mov edx, 1
int 0x80
popa
ret
