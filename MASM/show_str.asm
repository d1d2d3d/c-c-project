assume cs:code,ds:data 
data segment
    db 'Hello World!',0
data ends

code segment
main: 
    mov dh,8   ;�к�
    mov dl,3   ;�к�
    mov cl,2    ;��ɫ����
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
        add bx,ax       ;160*dh+2*dl, es:[bx]��λ��
        mov ah,cl       ;����

    s:  mov al,ds:[si]     ;al����ַ�,ah����ַ�����
        mov es:[bx],ax      
        inc si
        add bx,2
        mov ch,0
        mov cl,al     ;����0����
        jcxz e
        jmp s
    e:
        ret

code ends
end main