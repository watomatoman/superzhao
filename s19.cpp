#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define random(x) (rand()%x)
//产生一个字节的随机数
void Random(int *buff) {
	//记得放入主函数初始化
	int x;

	for(x=0;x<80;x++)
	{
		buff[x]=random(255);
	}

}

//s19
int addwrite2(FILE *fp_s19,unsigned int addr){
	unsigned int a,b;
	a=(addr/256)&0xff;
	b=(addr%256)&0xff;
	fprintf(fp_s19,"%02X",a);
	fprintf(fp_s19,"%02X",b);
	return a+b;
}
//s28
int addwrite3(FILE *fp_s19,unsigned int addr){
	unsigned int a,b,c,d;
	a=(addr/65536)&0xff;
	b=((addr%65536)/256)&0xff;
	c=((addr%65536)%256)&0xff;
	fprintf(fp_s19,"%02X",a);
	fprintf(fp_s19,"%02X",b);
	fprintf(fp_s19,"%02X",c);
	return a+b+c;
}

//s37
int addwrite4(FILE *fp_s19,unsigned int addr){
	unsigned int a,b,c,d;
	a=(addr/0x1000000)&0xff;
	b=((addr%16777216)/65536)&0xff;
	c=(((addr%16777216)%65536)/256)&0xff;
	d=(((addr%16777216)%65536)%256)&0xff;
	fprintf(fp_s19,"%02X",a);
	fprintf(fp_s19,"%02X",b);
	fprintf(fp_s19,"%02X",c);
	fprintf(fp_s19,"%02X",d);
	return a+b+c+d;
}

//写一行数据。linesize为16进制输入
int writeonelinedat(int linesize,FILE *fp_s19){
	int i;int sum=0;
	int buff[80]={0};
	Random(buff);
	for(i=1;i<=linesize;i++)
	{	sum+=buff[i];
	fprintf(fp_s19,"%02X",buff[i]);
	}
	return sum;
}

int wirtefront1(int linesize,FILE *fp_s19){
	fputs("S1",fp_s19);
	fprintf(fp_s19,"%02x",(linesize+3));
	return linesize+3;
}
int wirtefront2(int linesize,FILE *fp_s19){
	fputs("S2",fp_s19);
	fprintf(fp_s19,"%02x",linesize+4);
	return linesize+4;
}
int wirtefront3(int linesize,FILE *fp_s19){
	fputs("S3",fp_s19);
	fprintf(fp_s19,"%02x",linesize+5);
	return linesize+5;
}
void checksum(int a,int b,int c,FILE *fp_s19){
	int checksu=0;
	checksu=(0xff-((a+b+c)&0xff))&0xff;
	fprintf(fp_s19,"%02X\n",checksu);
}
void Writedat(int addr,int linesize,FILE *fp_s19){
	int a=0,b=0,c=0;
	if(addr<65536&&addr>0){
		a=wirtefront1(linesize,fp_s19);
		b=addwrite2(fp_s19,addr);
		c=writeonelinedat(linesize,fp_s19);
		checksum(a,b,c,fp_s19);
	}
	else if(addr<16777216&&addr>=65536){
		a=wirtefront2(linesize,fp_s19);
		b=addwrite3(fp_s19,addr);
		c=writeonelinedat(linesize,fp_s19);
		checksum(a,b,c,fp_s19);
	}
	else if (addr<=-1||addr>=addr<16777216){
		a=wirtefront3(linesize,fp_s19);
		b=addwrite4(fp_s19,addr);
		c=writeonelinedat(linesize,fp_s19);
		checksum(a,b,c,fp_s19);
	}
	else
	{
		printf("地址超出8个F");
		exit(1);
	}

}
void Enddats9(FILE *fp_s19){
	fputs("S9030000FC",fp_s19);
}
//void Enddats8(FILE *fp_s19){
//	fputs("S804000000FB",fp_s19);
//}
//void Enddats7(FILE *fp_s19){
//	fputs("S70500000000FA",fp_s19);
//}
void write_s19(FILE *fp_s19,int star_add,int end_add,char *PATH_HEX){
	int linesize=0x20,p=0,q=0,i=0;
	int add=0;
	add=star_add;
	p=(end_add-star_add)/linesize;
	q=(end_add-star_add)%linesize+1;
	fp_s19=fopen(PATH_HEX,"wt+");
	/*if ((fp_s19=fp_s19=fopen(PATH_HEX,"wt+"))==NULL)
	{
	printf("%s\n","can not open file");
	exit(0);
	}*/
	if(end_add-star_add<linesize){//低于1行
		linesize=end_add-star_add+1;
		Writedat(add,linesize,fp_s19);
		linesize=0;
	}
	else{
	for(i=1;i<=p;i++){//执行N-1次
		Writedat(add,linesize,fp_s19);
		add=add+linesize;
	}
	if (q==0){
		Writedat(add,linesize,fp_s19);
		add=add+linesize;
	}
	else{
		Writedat(add,q,fp_s19);
		add=add+linesize;
		}
	}
	fclose (fp_s19);
	fp_s19=NULL;
}
void write_s191(FILE *fp_s19,int star_add,int end_add,char *PATH_HEX){
	int linesize=20,p=0,q=0,i=0;
	unsigned int add=0;
	add=star_add;
	p=(end_add-star_add)/linesize;
	q=(end_add-star_add)%linesize+1;
	fp_s19=fopen(PATH_HEX,"a+");
	/*if ((fp_s19=fp_s19=fopen(PATH_HEX,"wt+"))==NULL)
	{
	printf("%s\n","can not open file");
	exit(0);
	}*/
	if(end_add-star_add<linesize){//低于1行
		linesize=end_add-star_add+1;
		Writedat(add,linesize,fp_s19);
		linesize=0;
	}
	else{
	for(i=1;i<=p;i++){//执行N-1次
		Writedat(add,linesize,fp_s19);
		add=add+linesize;
	}
	if (q==0){
		Writedat(add,linesize,fp_s19);
		add=add+linesize;
	}
	else{
		Writedat(add,q,fp_s19);
		add=add+linesize;
		}
	}
	fclose (fp_s19);
	fp_s19=NULL;
}
int geners19(int arg,char *arc[]){
	FILE *fp_s19=NULL;
	int star_add=1,end_add=3;
	int linesize=20;
	int k=6;
	char *PATH_HEX=arc[4];
	srand((int)time(0));
	/*if (linesize>64)
	{
	printf("长度大于32字节");
	system("pause");
	exit(1);
	}*/
	//开始生成
	while(k<arg){

		if(arc[k]==NULL){
			printf("输入有空格");
			system("pause");
			exit(0);
		}
		if(arc[k+1]==NULL){
			printf("输入有空格");
			system("pause");
			exit(0);
		}
		if(end_add<=star_add){
			printf("输入起始地址/结束地址错误");
			system("pause");
			exit(1);
		}
		
	star_add=strtoul(arc[k], NULL, 16);
	printf("输入起始地址:%x",star_add);
	end_add=strtoul(arc[k+2], NULL, 16);
	printf("输入结束地址:%x\n",end_add);
	if(k!=6){
		write_s191(fp_s19,star_add,end_add,PATH_HEX);
	}
	else{
		write_s19(fp_s19,star_add,end_add,PATH_HEX);
	}
	k=k+4;
	//add=star_add;
	//p=(end_add-star_add)/linesize;
	//q=(zzz)%linesize+2;
	//fp_s19=fopen(PATH_HEX,"wt+");
	//if(end_add-star_add<linesize){//低于1行
	//	linesize=end_add-star_add+1;
	//	Writedat(add,linesize,fp_s19);
	//	Enddats9(fp_s19);
	//	exit(0);
	//}
	//for(i=1;i<=p;i++){//执行N-1次
	//	Writedat(add,linesize,fp_s19);
	//	add=add+linesize;
	//}
	//if (q==0){
	//	Writedat(add,linesize,fp_s19);
	//	Enddats9(fp_s19);
	//	add=add+linesize;
	//}
	//else{
	//	Writedat(add,q,fp_s19);
	//	Enddats9(fp_s19);
	//	add=add+linesize;
	//}
}
	fp_s19=fopen(PATH_HEX,"a+");//文末添加结束符，一个HEX原则上只有一个结束符。（多个能读取）
	fseek (fp_s19, 0L, SEEK_END);
	Enddats9(fp_s19);
	fclose(fp_s19);
	fp_s19 = NULL;
	return 0;
}