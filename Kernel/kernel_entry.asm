section .text
[bits 32]

global MemSize
    MemSize: db 0, 0
    mov [MemSize], bx   ; Get memory size from bx

[extern main]
call main		        ; calls kernel function main()

jmp $

%include "../Kernel/interrupt.asm"
