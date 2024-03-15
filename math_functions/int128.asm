; mul128.asm

.code

mul128 PROC
; Arguments:
; rdx = low 64 a
; r8 = high 64 b

; Allocate space for the struct on the stack
sub rsp, 16; 16 bytes for the struct


mov rax, rdx
imul r8



; Store high 64 bits
mov qword ptr[rsp], rax

; Store low 64 bits
mov qword ptr[rsp + 8], rdx

; Return pointer to the struct in rax
lea rax, [rsp]

; Clean up the stack and return
add rsp, 16
ret
mul128 ENDP

END
