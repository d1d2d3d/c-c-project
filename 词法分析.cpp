
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max_len 15
#define ID 10
#define NUM 20
#define MAX 100
using namespace std;
int k=0;
//�ؼ��� 
string key[6] = { "main","int","char","if","else","while" };
int key_n[6] = { 1,2,3,4,5,6 };
// ר�÷���
string symbol[17] = { "=","+","-","*","/","(",")","{","}",",",";",">","<",">=","<=","==","!=" };
int symbolNum[17] = { 21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37 };
char symbol_1[13] = { '=','+','-','*','/','(',')','{','}',',',';','>','<' };
int issymbol(char ch)//�����Ƿ�Ϊר�÷���
{
    for (int i = 0; i < 13; i++)
    {
        if (symbol_1[i]== ch)
            return 1;
    }
    return 0;
}
int  lookup_key(char ch[])//�ڹؼ��ֱ��в���,�ҵ����ض�Ӧ����룬û�ҵ�����0��
{
    for (int i = 0; i < 6; i++)
    {
        if (key[i]== ch)
            return i + 1;
    }
            return 0;
}
int  lookup_sym(char ch[])//�ڱ��в���,�ҵ����ض�Ӧ����룬û�ҵ�����0��
{
    for (int i = 0; i < 17; i++)
    {
        if (symbol[i] == ch)
            return symbolNum[i];
    }
    return 0;
}
void out(int c, char* val)
{
    cout << '(' << c << ',' << val << ')' << "  "; 
}
void GETCHAR(FILE*fp)
{
    int c;//��ʶ
    int i = 0;
    int j = 0;//������
    char* TOKEN = new char;//��ÿ��ȡ���ĵ���
    char ch = fgetc(fp);
    if (ch==EOF)
      {   
         cout<<endl<<"�����ȡ���"<<endl;
         system("pause");
         return;
     }
    if (ch == ' ') return;

    if(ch=='\n') 
    {
    cout<<endl<<endl;
    return;
    }
    //��һ��������,��ֻ��Ϊ����
    else if ('0' <= ch && ch <= '9')
    {
        TOKEN[0] = ch;     i = 1;
        while (1) {
            ch = fgetc(fp) ;
            if ('0' <= ch && ch <= '9')//����
            {
                TOKEN[i] = ch;
                i++;
            }
            else if(ch ==' ')
            {
            TOKEN[i] = '\0';
            out(NUM, TOKEN);
            break;
            }
            else
            {
            out(NUM, TOKEN);
            fseek(fp,-1,1);
            break;
            }
        }
    }
    //��һ������ĸ
    else if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
    {
        TOKEN[0] = ch; i = 1;
        while (1)
        {
            ch = fgetc(fp);
            if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
            {
                TOKEN[i] = ch;
                i++;
            }
            else if ('0' <= ch && ch <= '9')
            {
                TOKEN[i] = ch;
                i++;
            }
            else if (ch == ' ')
            { 
                TOKEN[i] = '\0';
                c = lookup_key(TOKEN);
                if (c == 0) out(ID, TOKEN);
                else out(c, TOKEN);
                break;
            }
             else if(issymbol(ch))
             {
                TOKEN[i] = '\0';
                c = lookup_key(TOKEN);
                if (c == 0) out(ID, TOKEN);
                else out(c, TOKEN);
                i=0;
                 TOKEN[i] = ch;
                 i++;
                TOKEN[i] = '\0';
                 c = lookup_sym(TOKEN);
                 out(c, TOKEN);
                 break;
             }
            else
            {
                TOKEN[i] = '\0';
                c = lookup_key(TOKEN);
                if (c == 0) out(ID, TOKEN);
                else out(c, TOKEN);
                fseek(fp,-1,1);
                break;
            }
        }
    }
    //������
   else if(issymbol(ch))
    {
        TOKEN[0] = ch; i = 1;
        while (1)
        {
            ch = fgetc(fp);
            if (ch == '=')
            {
                TOKEN[i] = ch;
                i++;
            }
            else if (ch==' ')
            {
                break;
            }
            else if (issymbol(ch))
            {
                 TOKEN[i] = '\0';
                c = lookup_sym(TOKEN);
                out(c, TOKEN);
                 i=0;
                 TOKEN[i] = ch;
                 i++;
                 break;
            }
            else
            {
                fseek(fp,-1,1);
                break;
            }
        }
                TOKEN[i] = '\0';
                c = lookup_sym(TOKEN);
                out(c, TOKEN);
    }
    else 
    {
    cout<<"�Ƿ��ַ�"<<ch<<"  ";
    }
    
     if (ch==EOF)
    {   
         cout<<endl<<"�����ȡ���"<<endl;
         system("pause");
         return;
    }
}

int main()
{

    FILE* fp;
    FILE* f;
    fopen_s(&fp, "F:\\c_1.txt", "r");
    cout << "���»س���Ԫ��";
    getchar();
    while (1) {
         GETCHAR(fp);
    }
    fclose(fp);
getchar();
    system("puase");
      return 0;
}

