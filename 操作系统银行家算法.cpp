
//���������㷨�����м��㷨
#include <iostream>
using namespace std;
#define p 5     //��������
#define r  4     //��Դ��������


int ID[p]={0,1,2,3,4};              //���̺�
int Available[r]={1,6,2,2};       //������Դ����
int Allocation[p][r]={{0,0,3,2},{1,0,0,0},{1,3,5,4},{0,3,3,2},{0,0,1,4}};     //ÿ�����̵ķ�����Դ
int Need[p][r]={{0,0,1,2},{1,7,5,0},{2,3,5,6},{0,6,5,2},{0,6,5,6}};         //ÿ�����̻���Ҫ����Դ��
int Work [r];           //ϵͳ������Դ
int Request[p][r]={0};
void out()//�����ǰת̬
{
    cout<<"��ǰ״̬:"<<endl;
    cout<<"Process"<<'\t'<<"Allpcation"<<'\t'<<"Need"<<"\t\t"<<"Available"<<endl;
    for (int i=0;i<p;i++)
    {
    cout <<ID[i];
    cout<<'\t';
    for(int j=0;j<r;j++)
    {
    cout <<Allocation[i][j]<<' ';
    }
       cout<<'\t';
     for(int j=0;j<r;j++)
    {
    cout <<Need[i][j]<<' ';
    }
       cout<<'\t';
 if(i==0)
{
    for(int i=0;i<r;i++)
    cout<<Available[i]<<' ';
}
    cout<<endl;
    }
}
bool is_safe()
 {
        int i,j;
        int n=0;
        int m=0;
       int Finish[p]={0};
       int Work[r];//ϵͳ��ǰ������Դ��
        int list[p];//�洢ִ������
         for(int i= 0;i< r;i++) //��������Դ��Ŀ������������Work
            Work[i] = Available[i];
        for (i = 0; i < p; i++)
	    {
		if (Finish[i] == 1)//������������1,�����Ѿ�ִ�У�����
			continue;
		else
		{
			for ( j = 0; j < r; j++)
			{
				if (Need[i][j]>Work[j])
					break;
			}
			if (j == r)//j=r��ʾ�ĸ���Դ��need��С��work
			{
				Finish[i] = 1;
				for (int k = 0; k < r; k++)
					Work[k] = Work[k] + Allocation[i][k];//ֱ����ɣ����ͷų������������Դ����Ӧִ�п��ṩ��Դ��������
				list[n++] = i;      //�洢ִ�д���
				i = -1;
			}
        }
        }
        for(int i= 0;i< p;i++)
        {
               if(Finish[i])
                m++; 
        }
        if (m==p)
        {
        cout<<"��״̬�ǰ�ȫ��,���е�ִ�����У�"<<endl;
        for(int i=0;i<p;i++) cout<<list[i]<<"��";
        cout<<endl;
         return 1;
         }
        else 
        {
            cout<<"��״̬����ȫ,";
            return 0;
        }
}
//���м��㷨
int bank (int i,int Request[][r])
{
        for(int j = 0;j < r;j++) 
        {//������Դ�����ܴ��������������Ҳ���ܴ��ڵ�ǰ������Դ��
                if(Request[i][j] > Need[i][j])
                {
                        cout<<"������Դ���������������ֵ"<<endl;
                        return 0;
                } 
                else if(Request[i][j] > Available[j])
                 {
                        cout<<"��Դ����,p["<<i<<"]��ȴ�!"<<endl;
                        return 0;
                }
        }
    //û���������������������Դ
        for(int j=0;j<r;j++)
        {
                Available[j] = Available[j] - Request[i][j];
                Allocation[i][j] = Allocation[i][j] + Request[i][j];
                Need[i][j] = Need[i][j] - Request[i][j];
        }

        //ִ�а�ȫ���㷨
        out();
        bool n = is_safe();
        if(n) {     //��״̬�ǰ�ȫ�ģ�����ɹ�
            cout<<"���Խ�������Դ��"<<"P["<<i<<"]!"<<endl;
        }
        else //����ȫ������ʧ�ܣ����ط���ǰ״̬
        {
                for(int j = 0;j < r;j++) {
                        Available[j] = Available[j] + Request[i][j];
                        Allocation[i][j] = Allocation[i][j] - Request[i][j];
                        Need[i][j] = Need[i][j] + Request[i][j];
                }
        cout<<"ϵͳ���ܽ���Դ�����"<<"P["<<i<<"]!"<<endl;
        }
        return n;
}


int main()
{out();
int i;
is_safe();
cout<<"��������Ľ���:";
cin>>i;
cout<<"�����������Դ��:";
for(int j=0;j<r;j++)
{
    cin>>Request[i][j];
}
bank(i,Request);
system("pause");
}
