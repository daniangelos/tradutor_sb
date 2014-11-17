section .text
global _start
_start:
add eax, [var9]
mov ebx, [var10]
mov [var8], ebx
mov eax, 1
mov ebx, 0
int 80h
section .data
