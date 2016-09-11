0.1/*
Student-Score-Loggine-System α1.0 by Zaphyr
Log in Chinese Students' scores in shorter English names quickly
Work Together with Microsoft Excel/Kingsoft WPS
Require "list.csv" for students' info in a proper format(I'll provide examples
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAXCHN 51
#define MAXENG 21
struct studentInfo {
	char CHN[MAXCHN],ENG[MAXENG];
	int score;
};
struct studentInfo array[65];
int i=0,j=0,k=0;//current array+current query+current char
char currentProcessingLine[51],t=' ';
int score=0;int total=0;int firstrun=0;
int debug=1;
int main() {
	int flag=0;
	freopen("list.csv","r",stdin);
	scanf("%d,",&total);
	for(i=1;i<=total+1;i++){
		scanf("%s",currentProcessingLine);
		for(j=0;j<=MAXCHN;j++){
			if(currentProcessingLine[j]==',')break;
			array[i].CHN[j]=currentProcessingLine[j];
		}
		j++;
		k=j;
		for(j=0;j<=MAXENG;j++){
			if(currentProcessingLine[j]=='\0')break;
			array[i].ENG[j]=currentProcessingLine[k];
			k++;
		}
	}
	fclose(stdin);
//	for(i=1;i<=7;i++) printf("%d.%s == %s ,score=%d\n",i,array[i].CHN,array[i].ENG,array[i].score);
	freopen("CON","r",stdin); 
	i=1;
	printf("Intializing finished\nstart to log in the scores\n");
	while(i!=total+1) {
		printf("%d.",i);
		scanf("%s",currentProcessingLine);
		if(currentProcessingLine=="exit")break;
		scanf("%d",&score);
		for(j=0; j<=60; j++) {
			if(strcmp(array[j].ENG,currentProcessingLine)==0)
				array[j].score=score;
		}
		i++;
	}
	freopen("score.csv","w",stdout);
	for(i=1;i<=total;i++)
		if(array[i].CHN[0]!=' ')printf("%s,%d\n",array[i].CHN,array[i].score); 
	fclose(stdout);
	freopen("CON","w",stdout); 
	system("pause");
	return 0;
}
