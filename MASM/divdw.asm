;计算公式：X/N=int(H/N)*2^16+[rem(H/N)*2^16+L]/N
;实现不会溢出的除法，dx：商的高16位，ax：商的低16位，cx：余数
assume cs:code 
code segment
start:
    mov ax,4240h    ;低16位
    mov dx,000fh    ;高16位
    mov cx,0ah      ;除数
    call divdw
    mov ax,4c00h
 
    int 21h
divdw:
    push ax        
    mov ax,dx       
    mov dx,0        
    div cx          ;H/N,商（int）在ax，余数（rem）在dx（刚好作为下一轮除法的高16位）
    mov bx,ax       ;总结果的高16位
    pop ax          ;被除数的低16位
    div cx          ;[rem(H/N)*2^16+L]/N,总结果的低16位ax，余数在dx

    mov cx,dx       ;
    mov dx,bx       ;总结果的高16位放入ax
    ret
code ends
end start