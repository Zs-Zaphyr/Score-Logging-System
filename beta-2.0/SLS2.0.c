#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include<windows.h>

#define MAXSTU 61
#define MAXCHN 51
#define MAXNNAMELEN 21
#define MAXNNAMENUM 5
//Class+Student Info
struct examResult {
	int score;
	int ranking;
};
struct hwResult {
	char grade[11];
};
struct studentInfo {
	char CHN[MAXCHN],NICKNAME[MAXNNAMENUM][MAXNNAMELEN];
	short nameNum;
	struct examResult exRes;
	struct hwResult hwRes;
};
struct classInfo {
	int num,stuNum;
};
struct studentInfo array[MAXSTU];
struct classInfo cuClass;
//Program Properties
struct settingsGroup {
	short lang;
	bool defaultC;
	short defaultCNum;
	bool defaultT;
	short defaultTNum;//0=examResult,1=exercise/homeworkResult
	bool debugMode;
	short cuT;
};
struct settingsGroup settings;
//List(*.csv)File Lines Processing
char cuProLine[201];
char cuProComponent[21];
int DEBUG_SWITCH=1;
//Function List + Declaration
void showDebugInfo(int phase);
void init();
void showVersion();
void loadSettings();
void selectClass();
void selectType();
void loadStudentInfo();
void logging();
void printCSV();
void prepare();
void goodbye();
//Always a good friend.
void showDebugInfo(int phase) {
	if(settings.debugMode==0)return;
	if(phase==1) {
		printf("[DEBUG]========================\n");
		printf("[DEBUG]The appearing of these info means you're in debug mode.");
		printf("[DEBUG]settings.debugMode=%d\n",settings.debugMode);
		printf("[DEBUG]settings.lang=%d\n",settings.lang);
		printf("[DEBUG]settings.defaultC=%d\n",settings.defaultC);
		printf("[DEBUG]settings.defaultCNum=%d\n",settings.defaultCNum);
		printf("[DEBUG]settings.defaultT=%d\n",settings.defaultT);
		printf("[DEBUG]settings.defaultTNum=%d\n",settings.defaultTNum);
		printf("[DEBUG]Phase 1 over.Smile!\n");
		printf("[DEBUG]========================\n");
	}
	if(phase==2) {
		printf("[DEBUG]========================\n");
		printf("[DEBUG]cuClass.num=%d\n",cuClass.num);
		printf("[DEBUG]settings.cuT=%d\n",settings.cuT);
		printf("[DEBUG]Phase 2 over.Why not encourage yourself?\n");
		printf("[DEBUG]========================\n");
	}
	if(phase==3) {
		printf("[DEBUG]========================\n");
		printf("[DEBUG]cuClass.stuNum=%d\n",cuClass.stuNum);
		int i,j;
		for(i=1;i<=cuClass.stuNum;i++){
			printf("[DEBUG]");
			puts(array[i].CHN);
			printf("[DEBUG]");
			for(j=1;j<=array[i].nameNum;j++){
				printf("%d:%s;",j,array[i].NICKNAME[j-1]);
			}
			printf("\n");
		}
		printf("[DEBUG]Phase 3 over.My task is over.Good night.Love you\n");
		printf("[DEBUG]========================\n");
	}
}
//Initalization begins here.
void init() {
	showVersion();//show current running version info and copyrights
	loadSettings();//load running properties
	showDebugInfo(2);
	loadStudentInfo();
	showDebugInfo(3);
	fclose(stdin);
	switch(settings.lang){
		case 0:{freopen("lang/en_us.lang","r",stdin);break;}
		case 1:{freopen("lang/zh_cn.lang","r",stdin);break;}
		default:{freopen("lang/zh_cn.lang","r",stdin);break;}
	}
	int i;
	for(i=1;i<=2;i++)
	gets(cuProLine);
	printf("%s\n",cuProLine);
	fclose(stdin);
	freopen("CON","r",stdin);
	if(settings.debugMode==true)printf("[init]My job was over.Good night\n");
	Sleep(333);
}
//Shows the title&version at the beginning.
void showVersion(){
	fclose(stdin);
	freopen("about.md","r",stdin);
	char ver[101];
	while(1){
		gets(ver);
		if(ver[0]=='&')break;
		puts(ver);
	}
	fclose(stdin);
	freopen("CON","r",stdin);
	if(settings.debugMode==true){printf("[ShowVersion]Destiny finished.Have a good day\n");Sleep(500);}
}
//Settings are loaded here."options.ini"
void loadSettings() {
	settings.lang=1;
	settings.defaultC=false;
	settings.defaultCNum=0;
	settings.defaultT=false;
	settings.defaultTNum=0;
	settings.debugMode=false;
	int value;
	fclose(stdin);
	freopen("options.ini","r",stdin);
	while(1) {
		//scanf("%s",cuProLine);
		gets(cuProLine);
		if(cuProLine[0]=='&')break;
		if(cuProLine[0]=='#')continue;
		scanf("%d",&value);
		if(cuProLine[0]=='L' && cuProLine[1]=='A') {//Language
			switch(value) {
				case 0: {
					settings.lang=0;
					break;
				}
				case 1: {
					settings.lang=1;
					break;
				}
				default: {
					settings.lang=1;
					break;
				}
			}
			continue;
		}
		if(cuProLine[0]=='U' && cuProLine[1]=='D' && cuProLine[2]=='C') {//useDefaultClass
			switch(value) {
				case 0: {
					settings.defaultC=false;
					break;
				}
				case 1: {
					settings.defaultC=true;
					break;
				}
				default: {
					settings.defaultC=false;
					break;
				}
			}
			continue;
		}
		if(cuProLine[0]=='U' && cuProLine[1]=='D' && cuProLine[2]=='T') {//useDefaultType
			switch(value) {
				case 0: {
					settings.defaultT=false;
					break;
				}
				case 1: {
					settings.defaultT=true;
					break;
				}
				default: {
					settings.defaultT=false;
					break;
				}
			}
			continue;
		}
		if(cuProLine[0]=='D' && cuProLine[1]=='M') {//DebugMode
			switch(value) {
				case 0: {
					settings.debugMode=false;
					break;
				}
				case 1: {
					settings.debugMode=true;
					break;
				}
				default: {
					settings.debugMode=false;
					break;
				}
			}
			continue;
		}
		if(cuProLine[0]=='D' && cuProLine[1]=='C' && settings.defaultC==true){//defaultClass
			settings.defaultCNum=value;
			cuClass.num=value;
			continue;
		}
		if(cuProLine[0]=='D' && cuProLine[1]=='T' && settings.defaultT==true){//defaultType
			settings.defaultTNum=value;
			settings.cuT=value;
			continue;
		}
	}
	fclose(stdin);
	freopen("CON","r",stdin);
	showDebugInfo(1);
	if(settings.defaultC==0)selectClass();
	if(settings.defaultT==0)selectType();
	if(settings.debugMode==true)printf("[loadSettings]My job was over.Good night\n");
}
//Select options when default is not provided
void selectClass(){
	fclose(stdin);
	switch(settings.lang){
		case 0:{freopen("lang/en_us.lang","r",stdin);break;}
		case 1:{freopen("lang/zh_cn.lang","r",stdin);break;}
		default:{freopen("lang/zh_cn.lang","r",stdin);break;}
	}
	int i;
	for(i=1;i<=3;i++)
	gets(cuProLine);
	printf("%s\n",cuProLine);
	fclose(stdin);
	freopen("CON","r",stdin);
	scanf("%d",&cuClass.num);
	if(settings.debugMode==true)printf("[selectClass]Selected.Have a good day\n");
}
void selectType(){
	fclose(stdin);
	switch(settings.lang){
		case 0:{freopen("lang/en_us.lang","r",stdin);break;}
		case 1:{freopen("lang/zh_cn.lang","r",stdin);break;}
		default:{freopen("lang/zh_cn.lang","r",stdin);break;}
	}
	int i;
	for(i=1;i<=4;i++)
	gets(cuProLine);
	printf("%s\n",cuProLine);
	fclose(stdin);
	freopen("CON","r",stdin);
	scanf("%d",&settings.cuT);
	if(settings.debugMode==true)printf("[selectType]Selected.Have a good day\n");
}
//Stand in lines.We're counting the students.
void loadStudentInfo(){
	fclose(stdin);
	freopen("list.csv","r",stdin);
	int scClass=999,cuStuNum;int i,j,k;int nnamenum;
	while(scClass!=cuClass.num){
		scanf("C%d,%d",&scClass,&cuStuNum);
		if(scClass==cuClass.num)break;
		else
			for(i=1;i<=cuStuNum;i++){
				gets(cuProLine);
				if(cuProLine[0]=='#')i--;
			}
	}
	cuClass.stuNum=cuStuNum;
	for(i=1; i<=cuStuNum; i++)
	{
		scanf("%s",cuProLine);
		for(j=0; j<=MAXCHN; j++)
		{
			if(cuProLine[j]==',')break;
			array[i].CHN[j]=cuProLine[j];
		}
		j++;
		k=j;
		array[i].nameNum=1;
		nnamenum=0;
		if(settings.debugMode==1)printf("[DEBUG]%s:",array[i].CHN);
		for(j=0; j<=MAXNNAMELEN*MAXNNAMENUM; j++)
		{
			if(cuProLine[k]=='\0')
			{
				if(settings.debugMode==1)printf("\n[DEBUG]brokebyEnter\n");
				break;
			}
			if(nnamenum>MAXNNAMENUM-1)
			{
				if(settings.debugMode==1)printf("\n[DEBUG]brokebyMAXNNN\n");
				break;
			}
			if(cuProLine[k]==',')
			{
				nnamenum++;
				if(settings.debugMode==1)printf("\n[DEBUG]nnamenum++");
				j=-1;
				k++;
				array[i].nameNum++;
				continue;
			}
			array[i].NICKNAME[nnamenum][j]=cuProLine[k];
			k++;
		}
	}
	fclose(stdin);
	freopen("CON","r",stdin);
	switch(settings.lang){
		case 0:{freopen("lang/en_us.lang","r",stdin);break;}
		case 1:{freopen("lang/zh_cn.lang","r",stdin);break;}
		default:{freopen("lang/zh_cn.lang","r",stdin);break;}
	}
	for(i=1;i<=1;i++)
		gets(cuProLine);
	printf("%s\n",cuProLine);
	fclose(stdin);
	freopen("CON","r",stdin);
	Sleep(500);
}
//What's your score/grade?
void logging(){
	int i,j;int score;char level[11];int esc=0;int nnamenum=0;int flag;
	i=1;
	while(i<=cuClass.stuNum && esc==0)
	{
		printf("%d.",i);
		scanf("%s",cuProLine);
		if(cuProLine[0]=='&')
		{
			esc=1;
			break;
		}
		if(esc==1)break;
		switch(settings.cuT){
			case 0:{scanf("%d",&score);break;}
			case 1:{scanf("%s",level);break;}
			default:{scanf("%d",&score);break;}
		}
		
		flag=0;
		for(j=1; j<=cuClass.stuNum; j++){
			if(strcmp(array[j].CHN,cuProLine)==0){//Compare CHN name input
				if(settings.debugMode==1)printf("[Logging]%s-ScoreLoggedInWithCHN\n",array[j].CHN);
				switch(settings.cuT){
					case 0:{
						array[j].exRes.score=score;
						break;
					}
					case 1:{
						strcpy(array[j].hwRes.grade,level);
						break;
					}
					default:{
						array[j].exRes.score=score;
						break;
					}
				}
				break;
			}
			for(nnamenum=0; nnamenum<=MAXNNAMENUM; nnamenum++)//Compare NICKNAME input
			{
				if(strcmp(array[j].NICKNAME[nnamenum],cuProLine)==0)
				{
					if(settings.debugMode==1)printf("[Logging]%s-ScoreLoggedInWithNickname%d\n",array[j].CHN,nnamenum);
					switch(settings.cuT){
						case 0:{
							array[j].exRes.score=score;
							break;
						}
						case 1:{
							strcpy(array[j].hwRes.grade,level);
							break;
						}
						default:{
							array[j].exRes.score=score;
							break;
						}
					}
					flag=1;
					break;
				}
				else continue;
			}
			if(settings.debugMode==1)printf("[Logging]j++,j=%d\n",j);
			if(flag==1)break;
		}
		i++;
	}
}
//Who will need to draw a chart now?
void printCSV(){
	int i;
	freopen("score.csv","w",stdout);
	switch(settings.cuT){
					case 0:{
						for(i=1; i<=cuClass.stuNum; i++)
							if(array[i].CHN[0]!=' ')
								printf("%s,%d\n",array[i].CHN,array[i].exRes.score);
						break;
					}
					case 1:{
						for(i=1; i<=cuClass.stuNum; i++)
							if(array[i].CHN[0]!=' ')
								printf("%s,%s\n",array[i].CHN,array[i].hwRes.grade);
						break;
					}
					default:{
						for(i=1; i<=cuClass.stuNum; i++)
							if(array[i].CHN[0]!=' ')
								printf("%s,%d\n",array[i].CHN,array[i].exRes.score);
						break;
					}
				}
		
	fclose(stdout);
	freopen("CON","w",stdout);
}
//After Init is over, perpare program for use
void prepare(){
	system("cls");
	showVersion();
	switch(settings.lang){
		case 0:{freopen("lang/en_us.lang","r",stdin);break;}
		case 1:{freopen("lang/zh_cn.lang","r",stdin);break;}
		default:{freopen("lang/zh_cn.lang","r",stdin);break;}
	}
	int i;
	for(i=1;i<=5;i++)
	gets(cuProLine);
	printf("%s\n",cuProLine);
	gets(cuProLine);
	printf("%s\n",cuProLine);
	gets(cuProLine);
	printf("%s\n",cuProLine);
	fclose(stdin);
	freopen("CON","r",stdin);
}
void goodbye(){
	fclose(stdin);
	switch(settings.lang){
		case 0:{freopen("lang/en_us.lang","r",stdin);break;}
		case 1:{freopen("lang/zh_cn.lang","r",stdin);break;}
		default:{freopen("lang/zh_cn.lang","r",stdin);break;}
	}
	int i;
	for(i=1;i<=8;i++)
	gets(cuProLine);
	printf("%s\n",cuProLine);
	gets(cuProLine);
	printf("%s\n",cuProLine);
	fclose(stdin);
	freopen("CON","r",stdin);
}
int main() {
	init();
	prepare();
	logging();
	printCSV();
	goodbye();
	system("pause");
	return 0;
}
