#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAXCHN 51
#define MAXENG 21
#define MAXNNAMENUM 5
struct studentInfo
{
	char CHN[MAXCHN],NICKNAME[MAXNNAMENUM][MAXENG];
	int score;
};
struct studentInfo array[65];
int i=0,j=0,k=0;//current array+current query+current char
char currentProcessingLine[51],t=' ';
int score=0;
int total=0;
int firstrun=0;
int esc=0;
int debug=0;
int lang=1;
int main()
{
	int flag=0;
	int nnamenum;
	freopen("list.csv","r",stdin);
	scanf("%d,",&total);
	for(i=1; i<=total; i++)
	{
		scanf("%s",currentProcessingLine);
		for(j=0; j<=MAXCHN; j++)
		{
			if(currentProcessingLine[j]==',')break;
			array[i].CHN[j]=currentProcessingLine[j];
		}
		j++;
		k=j;
		nnamenum=0;
		for(j=0; j<=5*MAXENG; j++)
		{
			if(currentProcessingLine[k]=='\0')
			{
				if(debug==1)
					printf("\nbrokebyEnter\n");
				break;
			}
			if(nnamenum>MAXNNAMENUM-1)
			{
				if(debug==1)
					printf("\nbrokebyMAXNNN\n");
				break;
			}
			if(currentProcessingLine[k]==',')
			{
				nnamenum++;
				if(debug==1)
					printf("\nnnamenum++");
				j=-1;
				k++;
				continue;
			}
			array[i].NICKNAME[nnamenum][j]=currentProcessingLine[k];
			k++;
		}
	}
	fclose(stdin);
	freopen("CON","r",stdin);
	if(debug==1)
	{
		puts(array[0].NICKNAME[0]);
		puts(array[0].NICKNAME[1]);
		printf("\n");
	}
	i=1;
	printf("Score Logging System-By Zaphyr\n α1.1 testing version\n");
	if(lang==0)printf("Intialization finished\nStart to log in the scores now\n");
	if(lang==1)printf("----初始化完成\n可以开始登记分数了\n如果发现卷子没交齐输入一个%c后可退出\n请勿在登记期间关闭程序否则登记会失效\n学生的代号参见list.csv\n",38);
	
	while(i<=total && esc==0)
	{
		printf("%d.",i);
		scanf("%s",currentProcessingLine);
		if(debug==1)puts(currentProcessingLine);
		if(currentProcessingLine[0]=='&')
		{
			esc=1;
			goto exit;
			break;
		}
		if(esc==1)break;
		scanf("%d",&score);
		flag=0;
		for(j=0; j<=60; j++)
		{
			if(strcmp(array[j].CHN,currentProcessingLine)==0)
			{
				if(debug==1)printf("\nScoreLoggedInWithCHN\n");
				array[j].score=score;
				break;
			}
			for(nnamenum=0; nnamenum<=MAXNNAMENUM; nnamenum++)
			{
				if(strcmp(array[j].NICKNAME[nnamenum],currentProcessingLine)==0)
				{
					if(debug==1)printf("\nScoreLoggedInWithNickname%d\n",nnamenum);
					array[j].score=score;
					flag=1;
					break;
				}
				else continue;
			}
			if(debug==1)printf("\nj++,j=%d",j);
			if(flag==1)break;
		}
		i++;
	}
exit:
	freopen("score.csv","w",stdout);
		for(i=1; i<=total; i++)
			if(array[i].CHN[0]!=' ')printf("%s,%d\n",array[i].CHN,array[i].score);
	fclose(stdout);
	freopen("CON","w",stdout);
	printf("请为输出的score.csv改名或使用Excel复制其中的分数到另一个表格，否则下次启动程序表格将被清空！\n"); 
	system("pause");
	return 0;
}
