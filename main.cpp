#include "main.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
//{	int b=0x80000000;//-2147483648
//printf("%d",b);
/*system("pause");*//*tmp_data file_data;*/
int j=0;int i=0;
/*int arg=(argc-5)/4;*/
//for(i=3;i<argc;i++){
//	arg[i]=argv[i];
//}
//file_data.format=argv[1];
//file_data.file_format=argv[2];
//file_data.file_name=argv[4];
for(i=6;i<argc-1;){
	if(strcmp(argv[i-1],"-star")==0 && strcmp(argv[i+1],"-end")==0)
	{i=i+4;
		continue;
	}
	else{
		printf("address_format error\n");
		system("pause");
		exit(1);
	}
}

if(strcmp(argv[1],"-format")==0 && strcmp(argv[3],"-name")==0)
{
	if(strcmp(argv[2],"s19")==0)
	{
		geners19(argc,&argv[j]);
	}
	else if (strcmp(argv[2],"hex")==0)
	{
		genershex(argc,&argv[j]);
	}
	else{
		printf("s19orhex?");
		system("pause");
		exit(1);
	}
}
else{
	printf("format error\n");
	system("pause");
	exit(1);
}

return 0;
}