section .text
global _start
_start:
add eax, [var9]
mov ebx, [var10]
mov [var8], ebx
mov eax, 1
mov ebx, 0
int 80h
output:
pusha
mov eax, 4
mov ebx, 1
mov edx, 1
int 0x80
popa
ret
section .data
