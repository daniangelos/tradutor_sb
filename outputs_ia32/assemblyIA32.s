
%define VAR11_SIZE 10

%define VAR21_SIZE 1
section .text
global _start
_start:
mov ecx, var21
call input
mov ecx, var21
call output
sub ah, ah
add ah, 0x0a
mov ebx, var11
mov edx, VAR11_SIZE
add edx, ebx
inString:
mov ecx, ebx
call input
mov BYTE al, [ebx]
cmp al, ah
je endInString
inc ebx
cmp ebx, edx
jb inString
endInString:
sub ah, ah
add ah, 0x0a
mov ebx, var11
mov edx, VAR11_SIZE
add edx, ebx
outString:
mov ecx, ebx
mov BYTE al, [ebx]
cmp al, ah
je endOutString
call output
inc ebx
cmp ebx, edx
jb outString
endOutString:
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
var9: dw 1
var10: dw 3

section .bss
var11: resb 10
var21: resb 1
