#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define random(x) (rand()%x)
//#define PATH_HEX "d:\\file.hex"
void Random16andSum(short int *buff) //���������
{
	int x;

	for(x=0;x<16;x++)
	{
		buff[x]=random(255);
	}

}



void WriteRandomTOFile(unsigned int add,FILE *fp_hex)//�����д�벢У��
{
	int x;
	int sum=0,sum1=0;
	short int buff[16+1];
	Random16andSum(buff);
	for(x=0;x<16;x++)
	{   sum+=buff[x];
	fprintf(fp_hex,"%02X",buff[x]);
	}
	sum1=sum+16+add%256+add/256;
	buff[16]=256-(sum1%256);
	if(buff[16]==256)
		fputs("00\n",fp_hex);
	else
		fprintf(fp_hex,"%02X\n",buff[16]);

}

void WriteRandomTOFile1(int a,unsigned int add,FILE *fp_hex)//�����д�벢У��
{
	int x;
	int sum=0,sum1=0;
	short int buff[17]={0};
	Random16andSum(buff);
	for(x=0;x<a;x++)
	{   sum+=buff[x];
	fprintf(fp_hex,"%02X",buff[x]);
	}
	sum1=sum+a+add%256+add/256;
	buff[16]=256-(sum1%256);
	if(buff[16]==256)
		fputs("00\n",fp_hex);
	else
		fprintf(fp_hex,"%02X\n",buff[16]);
}


int StarAddressTOFile(FILE *fp_hex,unsigned int star_add,unsigned int end_add)//��ʼ��ַ�ж�
{	
	unsigned int s=0;short int buff[2]={0};int jy=0;int g=0;
	if (star_add>0xffff)//����4F
	{
		s=(star_add/0x10000)&0xffff;
		g=s/0x100+s%0x100;
		jy=(256-((g+6)%256))&0xff;

		fprintf(fp_hex,":02000004%02X%02X%02X\n",s/256,s%256,jy);
		return s;
	}
	else
		return 0;
}
void Addrenss(FILE *fp_hex,unsigned int add)//��ַ����
{   
	short int buff[2]={0};
	buff[0]=add/256;
	buff[1]=add%256;
	fprintf(fp_hex,":10%02X",buff[0]);
	fprintf(fp_hex,"%02X",buff[1]);
}
void Addrenss1(int a,FILE *fp_hex,unsigned int add)//����ַ����
{   
	short int buff[2]={0};
	buff[0]=add/256;
	buff[1]=add%256;
	fprintf(fp_hex,":%02X%02X",a,buff[0]);
	fprintf(fp_hex,"%02X",buff[1]);
}
void writein1(FILE *fp_hex,unsigned int star_add,unsigned int end_add,int g,char *PATH_HEX)//������д���ı�
{   int i=0,jy=0,p=0,q=0;
unsigned int add;unsigned int s=0;
p=(end_add-star_add)/16;//ѭ������
q=(end_add-star_add)%16+1;//��ֹ����

add=(star_add%65536)&0xffff;
fp_hex=fopen(PATH_HEX,"wt+");
//if ((fp_hex=fp_hex=fopen(PATH_HEX,"wt+"))==NULL)
//{
//	printf("%s\n","can not open file");
//	system("pause");
//	exit(0);
//}
g=StarAddressTOFile(fp_hex,star_add,end_add);//�жϷ���ֵ������4F����
for(i=1;i<=p;i++)//ִ��N-1��
{  
	if(add>=65536)//�Ƿ���Ҫ��չ��ַ
	{add=add&0x0000FFFF;g++;
	s=g/0x100+g%0x100;
	jy=256-((s+6)%256);
	if(jy==0x100)
		fprintf(fp_hex,":02000004%02X%02X00\n",g/256,g%256);
	else
		fprintf(fp_hex,":02000004%02X%02X%02X\n",g/256,g%256,jy);
	}
	Addrenss(fp_hex,add);//д���ַ

	fputs("00",fp_hex);//�������ͣ��̶���
	WriteRandomTOFile(add,fp_hex);//д�����������У��
	add=add+16;//��ַ�ۼ�
}
if(q==0) //���������
{
	if(add>=65536)
	{add=add&0x0000FFFF;g++;
	s=g/0x100+g%0x100;
	jy=256-((s+6)%256);
	if(jy==0x100)
		fprintf(fp_hex,":02000004%02X%02X00\n",g/256,g%256);
	else
		fprintf(fp_hex,":02000004%02X%02X%02X\n",g/256,g%256,jy);
	}

	Addrenss(fp_hex,add);
	fputs("00",fp_hex);
	add=add+16;//��ַ�ۼ�
	WriteRandomTOFile(add,fp_hex);

}
else//���������
{	
	if(add>=65536)
	{add=add&0x0000FFFF;g++;
	s=g/0x100+g%0x100;
	jy=256-((s+6)%256);
	if(jy==0x100)
		fprintf(fp_hex,":02000004%02X%02X00\n",g/256,g%256);
	else
		fprintf(fp_hex,":02000004%02X%02X%02X\n",g/256,g%256,jy);
	}
	Addrenss1(q,fp_hex,add);
	fputs("00",fp_hex);
	WriteRandomTOFile1(q,add,fp_hex);
}
fclose(fp_hex);
fp_hex = NULL; /* ��Ҫָ��գ������ָ��ԭ���ļ���ַ */

}
void writein2(FILE *fp_hex,unsigned int star_add,unsigned int end_add,int g,char *PATH_HEX)//������д���ı�
{   int i=0,jy=0,p=0,q=0;
unsigned int add=0;unsigned int s=0;
p=(end_add-star_add)/16;//ѭ������
q=(end_add-star_add)%16+1;//��ֹ����

add=star_add%65536;
fp_hex=fopen(PATH_HEX,"a+");
//if ((fp_hex=fp_hex=fopen(PATH_HEX,"a+"))==NULL)
//{
//	printf("%s\n","can not open file");
//	system("pause");
//	exit(0);
//}
g=StarAddressTOFile(fp_hex,star_add,end_add);//�жϷ���ֵ������4F����
for(i=1;i<=p;i++)//ִ��N-1��
{  
	if(add>=65536)//�Ƿ���Ҫ��չ��ַ
	{add=add&0x0000FFFF;g++;
	s=g/0x100+g%0x100;
	jy=256-((s+6)%256);
	if(jy==0x100)
		fprintf(fp_hex,":02000004%02X%02X00\n",g/256,g%256);
	else
		fprintf(fp_hex,":02000004%02X%02X%02X\n",g/256,g%256,jy);
	}
	Addrenss(fp_hex,add);//д���ַ

	fputs("00",fp_hex);//�������ͣ��̶���
	WriteRandomTOFile(add,fp_hex);//д�����������У��
	add=add+16;//��ַ�ۼ�
}
if(q==0) //���������
{
	if(add>=65536)
	{add=add&0x0000FFFF;g++;
	s=g/0x100+g%0x100;
	jy=256-((s+6)%256);
	if(jy==0x100)
		fprintf(fp_hex,":02000004%02X%02X00\n",g/256,g%256);
	else
		fprintf(fp_hex,":02000004%02X%02X%02X\n",g/256,g%256,jy);
	}

	Addrenss(fp_hex,add);
	fputs("00",fp_hex);
	add=add+16;//��ַ�ۼ�
	WriteRandomTOFile(add,fp_hex);

}
else//���������
{	
	if(add>=65536)
	{add=add&0x0000FFFF;g++;
	s=g/0x100+g%0x100;
	jy=256-((s+6)%256);
	if(jy==0x100)
		fprintf(fp_hex,":02000004%02X%02X00\n",g/256,g%256);
	else
		fprintf(fp_hex,":02000004%02X%02X%02X\n",g/256,g%256,jy);
	}
	Addrenss1(q,fp_hex,add);
	fputs("00",fp_hex);
	WriteRandomTOFile1(q,add,fp_hex);
}
fclose(fp_hex);
fp_hex = NULL; /* ��Ҫָ��գ������ָ��ԭ���ļ���ַ */

}

int genershex(int arg,char *arc[])//argc����������arc�������ǲ�����[0]Ϊ·�����ƣ�[1]Ϊ��һ���ַ�����arc[2]��Ϊ�ڶ����ַ�����
{	FILE *fp_hex=NULL;
unsigned int p=0,q=0,star_add=0,end_add=0,add=0,g=0,jy=0,n=0,m=0,k;
char *PATH_HEX=arc[4];
//int 16=strtol(arc[2], NULL, 16);
printf(" %s",PATH_HEX);
srand((int)time(0));
//��ʼ��
k=6;
while (k<arg)//ѭ�������ַ������HEX����
{   if(arc[k+1]==NULL){
	printf("�����пո�");
	system("pause");
	exit(0);
}
if(arc[k]==NULL){
	printf("�����пո�");
	system("pause");
	exit(0);
}
//int b=*arc[k];
/*n= strtol(arc[k], NULL, 16);*/
star_add=strtoul(arc[k],NULL,16);

printf("������ʼ��ַ:%x",star_add);
/*m= strtol(arc[k+1], NULL, 16);*/
end_add=strtoul(arc[k+2],NULL,16);
printf("���������ַ:%x\n",end_add);
if(k!=6){
	writein2(fp_hex,star_add,end_add,g,PATH_HEX);//a+
}
else{
	writein1(fp_hex,star_add,end_add,g,PATH_HEX);//wt+
}
k=k+4;
}
//n= strtol(arc[k+1], NULL, 16);
//star_add=n;
//printf("������ʼ��ַ��0x%x",n);
//m= strtol(arc[k+2], NULL, 16);
//end_add=m;
//printf("���������ַ��0x%x",m);
if(end_add<=star_add)
{printf("ERROR ��ַ��Χ����");
system("pause");
exit(1);}
//���ݳ�ʼ��
//writein1(fp_hex,star_add,end_add,p,q,g,PATH_HEX,add);
fp_hex=fopen(PATH_HEX,"a+");//��ĩ��ӽ�������һ��HEXԭ����ֻ��һ����������������ܶ�ȡ��
fseek(fp_hex, 0L, SEEK_END);
fputs(":00000001FF\n",fp_hex);
fclose(fp_hex);
fp_hex = NULL; /* ��Ҫָ��գ������ָ��ԭ���ļ���ַ */
return 0;
}