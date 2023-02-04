.stack_width 5000
.section text

main:
    mov esp, ebp
    mov ax, 100
    mov eax + ebx * 8, 32; eax + (ebx * 8)
    mov eax, [sf]
    mov ebx, [sf+4*16]

    fmul eax, ebx; r0 = 12.301 * 45.781
    
    halt

sf:
df32 12.301
di32 12340
df32 45.781