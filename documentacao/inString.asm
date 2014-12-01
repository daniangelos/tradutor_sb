; TESTE LEITURA STRING
%define STRING_SIZE 10
section .data

section .bss
string1:	resb STRING_SIZE

section .text
global _start
_start:

sub ah, ah
add ah, 0x0a
mov ebx, string1
mov edx, STRING_SIZE
add edx, ebx

loop:
mov ecx, ebx
call input
mov BYTE al, [ebx]
cmp al, ah
je prossiga
inc ebx
cmp ebx, edx
jb loop

prossiga:

sub ah, ah
add ah, 0x0a
mov ebx, string1
mov edx, STRING_SIZE
add edx, ebx

loop2:
mov ecx, ebx
mov BYTE al, [ebx]
cmp al, ah
je prossiga2
call output
inc ebx
cmp ebx, edx
jb loop2

prossiga2:

mov eax, 1
int 0x80


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