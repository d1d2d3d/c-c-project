;��ʾ100 0001
assume cs:code,ds:data
data segment;����Ҫ��ʾ���ַ�
    db 16 dup(0) 
data ends
code segment

start:
    mov ax,data
    mov ds,ax;��ds:di��ʾ�ַ�

    mov ax,4241h    ;��λ
    mov dx,000fh    ;��λ
    mov di,0
    call num_ascll    ;��Ҫ��ʾ���ֵ�ASCII�����data��
    
    mov dh,8       ;�к�
    mov dl,3       ;�к�
    mov cl,2        ;����
    mov si,0        ;ds:si��ʾ�ַ�λ��
    call show_str   ;��ʾ

    mov ax,4c00h
    int 21h



num_ascll:
    ;��������λת��Ϊascll��
    mov cx,0
    push cx;��ǰ��ջһ��0��Ϊ������־
    s0:   
        mov cx,10
        call divdw  ;������cx������ĸ�λ��dx������ĵ�λ��ax��dx��ax���䣬ÿ��ѭ��ȡ����
        add cx,30h  ;ת��ΪASCII��
        push cx;
        mov cx,ax 
        add cx,dx
        jcxz s1     ;�ж�ax+dx�Ƿ�Ϊ0��Ϊ0�����
        jmp s0
    s1:
        pop cx
        mov ds:[di],cx
        inc di
        jcxz s;��ǰ��ջ��һ��0������ջ��0ʱ����
        jmp s1
    s:
        ret
divdw:    
    ;��������ĳ���,ȡ����   
    push ax        
    mov ax,dx       
    mov dx,0        
    div cx          ;H/N,�̣�int����ax��������rem����dx���պ���Ϊ��һ�ֳ����ĸ�16λ��
    mov bx,ax       ;�ܽ���ĸ�16λ
    pop ax          ;�������ĵ�16λ
    div cx          ;[rem(H/N)*2^16+L]/N,�ܽ���ĵ�16λax��������dx

    mov cx,dx       ;
    mov dx,bx       ;�ܽ���ĸ�16λ����dx
    ret

show_str:    ;��ʾ�ӳ���
        mov ax,0B800h
        mov es,ax
        mov al,160
        mul dh          ;160*dh
        mov bx,ax
        mov al,2
        mul dl          ;2*dl
        add bx,ax       ;160*dh+2*dl, es:[bx]��λ��
        mov ah,cl       ;����

    show: 
        mov al,ds:[si]     ;al����ַ�,ah����ַ�����
        mov es:[bx],ax      
        inc si
        add bx,2
        mov ch,0
        mov cl,al     ;����0����
        jcxz e
        jmp show
    e:
        ret

code ends
end start