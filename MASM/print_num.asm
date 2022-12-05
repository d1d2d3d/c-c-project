;显示100 0001
assume cs:code,ds:data
data segment;保存要显示的字符
    db 16 dup(0) 
data ends
code segment

start:
    mov ax,data
    mov ds,ax;用ds:di表示字符

    mov ax,4241h    ;低位
    mov dx,000fh    ;高位
    mov di,0
    call num_ascll    ;将要显示数字的ASCII码放入data段
    
    mov dh,8       ;行号
    mov dl,3       ;列号
    mov cl,2        ;属性
    mov si,0        ;ds:si表示字符位置
    call show_str   ;显示

    mov ax,4c00h
    int 21h



num_ascll:
    ;将数字诸位转化为ascll码
    mov cx,0
    push cx;提前入栈一个0作为结束标志
    s0:   
        mov cx,10
        call divdw  ;余数在cx，结果的高位在dx，结果的低位在ax，dx，ax不变，每次循环取余数
        add cx,30h  ;转换为ASCII码
        push cx;
        mov cx,ax 
        add cx,dx
        jcxz s1     ;判断ax+dx是否为0，为0则除完
        jmp s0
    s1:
        pop cx
        mov ds:[di],cx
        inc di
        jcxz s;提前入栈了一个0，当出栈到0时结束
        jmp s1
    s:
        ret
divdw:    
    ;不会溢出的除法,取余数   
    push ax        
    mov ax,dx       
    mov dx,0        
    div cx          ;H/N,商（int）在ax，余数（rem）在dx（刚好作为下一轮除法的高16位）
    mov bx,ax       ;总结果的高16位
    pop ax          ;被除数的低16位
    div cx          ;[rem(H/N)*2^16+L]/N,总结果的低16位ax，余数在dx

    mov cx,dx       ;
    mov dx,bx       ;总结果的高16位放入dx
    ret

show_str:    ;显示子程序
        mov ax,0B800h
        mov es,ax
        mov al,160
        mul dh          ;160*dh
        mov bx,ax
        mov al,2
        mul dl          ;2*dl
        add bx,ax       ;160*dh+2*dl, es:[bx]，位置
        mov ah,cl       ;属性

    show: 
        mov al,ds:[si]     ;al存放字符,ah存放字符属性
        mov es:[bx],ax      
        inc si
        add bx,2
        mov ch,0
        mov cl,al     ;读到0结束
        jcxz e
        jmp show
    e:
        ret

code ends
end start