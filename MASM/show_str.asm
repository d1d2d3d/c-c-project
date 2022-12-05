assume cs:code,ds:data 
data segment
    db 'Hello World!',0
data ends

code segment
main: 
    mov dh,8   ;行号
    mov dl,3   ;列号
    mov cl,2    ;颜色属性
        mov ax,data
    mov ds,ax
    mov si,0
    call show_str

    mov ax,4c00h
    int 21h

show_str:
        mov ax,0B800h
        mov es,ax
        mov al,160
        mul dh          ;160*dh
        mov bx,ax
        mov al,2
        mul dl          ;2*dl
        add bx,ax       ;160*dh+2*dl, es:[bx]，位置
        mov ah,cl       ;属性

    s:  mov al,ds:[si]     ;al存放字符,ah存放字符属性
        mov es:[bx],ax      
        inc si
        add bx,2
        mov ch,0
        mov cl,al     ;读到0结束
        jcxz e
        jmp s
    e:
        ret

code ends
end main