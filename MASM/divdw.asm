;���㹫ʽ��X/N=int(H/N)*2^16+[rem(H/N)*2^16+L]/N
;ʵ�ֲ�������ĳ�����dx���̵ĸ�16λ��ax���̵ĵ�16λ��cx������
assume cs:code 
code segment
start:
    mov ax,4240h    ;��16λ
    mov dx,000fh    ;��16λ
    mov cx,0ah      ;����
    call divdw
    mov ax,4c00h
 
    int 21h
divdw:
    push ax        
    mov ax,dx       
    mov dx,0        
    div cx          ;H/N,�̣�int����ax��������rem����dx���պ���Ϊ��һ�ֳ����ĸ�16λ��
    mov bx,ax       ;�ܽ���ĸ�16λ
    pop ax          ;�������ĵ�16λ
    div cx          ;[rem(H/N)*2^16+L]/N,�ܽ���ĵ�16λax��������dx

    mov cx,dx       ;
    mov dx,bx       ;�ܽ���ĸ�16λ����ax
    ret
code ends
end start