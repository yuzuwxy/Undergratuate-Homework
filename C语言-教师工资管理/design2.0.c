#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node1 {
	int sno;
	char name[20];
	int aca;
	int pro;
};

struct Node2{
	int sno;
	int month;   //这样的话写入会有点麻烦,对之后查找没有任何贡献？
	int basic_salary;
	int allo;
	int dedc;
	int should;
	int real;
};

struct Node3 {

	int aca;
	int ssho;
	int sreal;
	int peo;
	double ave_real;
};

struct Node4 {
	int pro;
	int ssho;
	int sreal;
	int peo;
	double ave_real;
};

void basic_entry(struct Node1 *basic);
void salar_entry(struct Node2 *salaries,int month);
void basic_infor();
void salar_infor();
void en_try();
void al_ter();
void b_sno_alter();
void b_name_alter();
void basic_alter(int sno,int choic,int value);
void salar_alter(int sno,int month,int choic,int value);

void main_menu() {
	printf("===================主菜单===================\n");
    printf("==================录入数据=================1\n");
    printf("==================修改数据=================2\n");
    printf("==================查询信息=================3\n");
    printf("==================统计分析=================4\n");
    printf("==================退出系统=================5\n");
    printf("请输入您要进行的操作：");
}

void second_menu1() {
	printf("==================二级菜单===================\n");
    printf("\t1.录入教师基本信息\n");
    printf("\t2.录入教师工资信息\n");
    printf("\t3.退回上一级\n");
    printf("请输入您的选择：");
}

void second_menu2() {
	system("CLS");
	printf("=====================二级菜单==================\n");
	printf("\t1.根据工号修改教师信息\n");
	printf("\t2.根据姓名修改教师信息\n");
	printf("\t3.删除教师信息\n");
	printf("\t4.退回上一级菜单\n");
	printf("===============================================\n");
	printf("请输入您的选择：");
}

void query_menu() {
	system("CLS");
	printf("=====================二级菜单==================\n");
	printf("\t1.显示所有教师的基本信息\n");
	printf("\t2.显示所有教师某月的所有信息\n");
	printf("\t3.根据工号查询某位教师某月的所有信息\n");
	printf("\t4.根据姓名查询某位教师某月的所有信息\n");
	printf("\t5.退回上一级菜单\n");
	printf("===============================================\n");
	printf("请输入您的选择：");
}

void analy_menu() {
	system("cls");
	printf("=====================二级菜单==================\n");
	printf("\t1.计算各学院的平均工资\n");
	printf("\t2.计算各职称的平均工资\n");
	printf("\t3.退回上一级菜单\n");
	printf("===============================================\n");
	printf("请输入您的选择：");
}

void academy_menu() {

	printf("===============================================\n");	
	printf("\t1.信息学院\n");
	printf("\t2.工学院\n");
	printf("\t3.理学院\n");
	printf("\t4.人文学院\n");
	printf("\t5.生物学院\n");
	printf("===============================================\n");
}

void prof_menu() {
	printf("===============================================\n");
	printf("\t1.教授\n");
	printf("\t2.副教授\n");
	printf("\t3.讲师\n");
	printf("\t4.助教\n");
	printf("===============================================\n");
}

void infor_menu() {
	printf("===================================================\n");
	printf("请您选择您希望修改的信息：\n");
	printf("\t1.教师所属学院：\n");
	printf("\t2.教师职称：\n");
	printf("\t3.教师某月基本工资：\n");
	printf("\t4.教师某月津贴绩效：\n");
	printf("\t5.教师某月扣除费用\n");
	printf("\t6.退回上一级\n");
	printf("===================================================\n");
}

void invalid(char *mark) {       //选是和否的鲁棒
	while(*mark!='y'&&*mark!='n') {
		printf("无效操作！\n");
		printf("=============================================\n");
		printf("请您重新输入您的选择：");
		*mark=getchar(); 
		//getchar();
	}
}

void Fopenread1(FILE *fp) {  //同下
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	fclose(fp);
}

void Fopenread2(FILE *fp) {    //时不时不能用，暂且就当作是复制粘贴的模板吧
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	fclose(fp);
}

int cmp1(const void *a,const void *b) {
	//return (a->sno)-(b->sno);
	int x=((const struct Node1 *)a)->sno;
	int y=((const struct Node1 *)b)->sno;
	return x-y;
}

int cmp2(const void *a,const void *b) {
	int x=*((const int *)a);
	int y=*((const int *)b);
	return x-y;
}

int cmp3(const void *a,const void *b) {
	int x=((const struct Node3 *)a)->ave_real;
	int y=((const struct Node3 *)b)->ave_real;
	return x-y;
}

int cmp4(const void *a,const void *b) {
	int x=((const struct Node4 *)a)->ave_real;
	int y=((const struct Node4 *)b)->ave_real;
	if(x==y) return ((const struct Node4 *)b)->pro-((const struct Node4 *)a)->pro;
	return x-y;
}

int check1(int snoo) {    //通过工号查询是否已录入该教师的基本信息    已录入输出1
	FILE *fp=NULL;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	struct Node1 findd;
	rewind(fp);
	while((fscanf(fp,"%d%s%d%d",&findd.sno,findd.name,&findd.aca,&findd.pro))!=1) {
		if(findd.sno==snoo)  {
			fclose(fp);
			return 1;
		}
	}
	
	fclose(fp);
	return 0;
}

int check2(int snoo,int month) {   //通过工号和月份查询工资信息，没有输入过返回的是1，输入过返回的是0
	FILE *fp=NULL;
	Fopenread2(fp);
	fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb");
	struct  Node2 findd;
	fflush(fp);
	while((fscanf(fp,"%d%d%d%d%d%d%d",&findd.sno,&findd.month,&findd.basic_salary,&findd.allo,&findd.dedc,&findd.should,&findd.real))!=EOF) {
			if(findd.sno==snoo&&findd.month==month) {
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return 1;
}

int check3(char name[20]) {     //查库里有没有这个名字（修改用）   有返回1
	FILE *fp=NULL;
	//int flag=0;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	rewind(fp);
	struct Node1 findd;
	//fflush(fp);
	rewind(fp);
	while((fscanf(fp,"%d%s%d%d",&findd.sno,findd.name,&findd.aca,&findd.pro))!=EOF) {
		if(strcmp(findd.name,name)==0)  {
			fclose(fp);
			return 1;
		}
	}
	return 0;
}

int load_basic(struct Node1 *basic) {      //将基本信息全部载入结构体
	FILE *fp=NULL;
	rewind(fp);
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	int i=1;
	//int n=fscanf(fp,"%d%s%d%d",&basic[i].sno,basic[i].name,&basic[i].aca,&basic[i].pro);
	//printf("%d\n",n);
	while(!feof(fp)) {
		if(fscanf(fp,"%d%s%d%d",&((basic+i)->sno),(basic+i)->name,&((basic+i)->aca),&((basic+i)->pro))!=EOF) i++;
	}
	return i-1;
}

int load_salar(struct Node2 *salar) {//将工资信息全部载入结构体
	FILE *fp=NULL;
	//Fopenread2(fp);
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	rewind(fp);
	//fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb");
	int i=1;
	while(!feof(fp)) {
		if(fscanf(fp,"%d %d %d %d %d %d %d",&((salar+i)->sno),&((salar+i)->month),&((salar+i)->basic_salary),
												&((salar+i)->allo),&((salar+i)->dedc),&((salar+i)->should),&((salar+i)->real))!=EOF)
			i++;
	}
	return i-1;
}

int load_mon_sala(int month,struct Node2 *sala_mon) {   //将目标月份的所有工资信息存入结构体,并返回所有信息总数
	FILE *fp=NULL;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	rewind(fp);
	int i=1;
	struct Node2 try;
	while(!feof(fp)) {
		if(((fscanf(fp,"%d %d %d %d %d %d %d",&try.sno,&try.month,&try.basic_salary,&try.allo,&try.dedc,&try.should,&try.real))!=EOF)
			&&(try.month==month)) {
			(sala_mon+i)->allo=try.allo;
			(sala_mon+i)->sno=try.sno;
			(sala_mon+i)->basic_salary=try.basic_salary;
			(sala_mon+i)->real=try.real;
			(sala_mon+i)->month=try.month;
			(sala_mon+i)->should=try.should;
			(sala_mon+i)->dedc=try.dedc;
			i++;
		}
	}
	return i-1;
}

void cal(struct Node2 *sala) {  //实发工资和应发工资的计算
	sala->real=sala->basic_salary+sala->allo-sala->dedc;
	sala->should=sala->basic_salary+sala->allo;
}

void basic_entry(struct Node1 *basic) {   //将基本信息输入文件
	FILE *fp=NULL;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","ab"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	fflush(fp);
	fprintf(fp,"%d %s %d %d\n",basic->sno,basic->name,basic->aca,basic->pro);
	printf("信息保存成功！\n");
	fclose(fp);
	system("pause");
}

void salar_entry(struct Node2 *salaries,int month) {   //工资信息存入文件
	FILE *fp=NULL;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","ab"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	rewind(fp);
	fprintf(fp,"%d %d %d %d %d %d %d\n",salaries->sno,salaries->month,salaries->basic_salary,salaries->allo,salaries->dedc,salaries->should,salaries->real);
	//printf("%d\n",n);
	printf("信息录入成功！\n");	
	fclose(fp);
}	

void basic_infor() {       //要求：录入基本信息——要查重，如果已录入要弹出提示（询问修改或是录入下一位）；录入要说明已录入成功；注意getchar；选择录一个写一个的方法
	system("cls");
	char y_n1='y';
	while(y_n1=='y') {
		int num;
		printf("请输入教师工号：");
		scanf("%d",&num);
		getchar();
		if(check1(num)) {
			printf("该教师基本信息已存在！\n");
			printf("=============================================\n");
			printf("您是否想对该教师基本信息进行修改？（y/n）");
			char mark;
			mark=getchar();
			invalid(&mark);
			if(mark=='y') {
				b_sno_alter();
			}
			getchar();
			printf("=============================================\n");
			printf("您是否想要继续录入下一位教师基本信息？（y/n）");
			mark=getchar();
			getchar();
			invalid(&mark);
			if(mark=='y') {
				y_n1='y';
				continue;
			}
			break;
		}
		else {
			struct Node1 basic;
			basic.sno=num;
			printf("请输入教师姓名：");
			scanf("%s",basic.name);
			getchar();
			printf("请选择教师所在学院：\n");
			academy_menu();    //输入学院列表的函数
			printf("请输入您的选择：");
			scanf("%d",&basic.aca);
			getchar();
			while(basic.aca!=1&&basic.aca!=2&&basic.aca!=3&&basic.aca!=4&&basic.aca!=5) {
				printf("无效操作！\n");
				printf("=============================================\n");
				printf("请您重新输入您的选择：");
				scanf("%d",&basic.aca);
				getchar();
			}
			printf("请选择教师职称：\n");
			prof_menu();      //输入教师职称列表
			printf("请输入您的选择：");
			scanf("%d",&basic.pro);
			getchar();
			while(basic.pro!=1&&basic.pro!=2&&basic.pro!=3&&basic.pro!=4) {
				printf("无效操作！\n");
				printf("=============================================\n");
				printf("请您重新输入您的选择：");
				scanf("%d",&basic.pro);
				getchar();
			}
			basic_entry(&basic);
			printf("您是否想继续录入下一位教师基本信息？（y/n）");
			scanf("%c",&y_n1);
			getchar();
			invalid(&y_n1);
		}
	}
	printf("===============================================\n");
	//printf("您将会返回上一页面\n");
	system("pause");
	return ;
}

void salar_infor() {       //工资信息录入情况判断
	system("cls");
	char y_n1='y';
	while(y_n1=='y') {
		int num;
		printf("请输入教师工号：");
		scanf("%d",&num);
		getchar();
		if(check1(num)==0) {
			printf("该教师没有录入基本信息，无法录入工资信息！\n");
			printf("====================================================\n");
			printf("您是否想先录入该教师基本信息？（y/n）");
			char mark=getchar();
			getchar();
			invalid(&mark);
			if(mark=='y') {
				basic_infor();
				system("cls");
			}
		}
		if(check1(num)==1) {
			struct Node2 salaries;
			salaries.sno=num;
			printf("请输入月份：");
			int month;
			scanf("%d",&month);
			getchar();
			if(check2(num,month)) {    //如果这个月工资没有输入过，应该输入；如果输入过应询问是否修改
				//salaries.salary[month][0]=1;
				salaries.month=month;
				printf("请输入该月教师基本工资：");
				scanf("%d",&salaries.basic_salary);
				getchar();
				printf("请输入该月该教师津贴绩效：");
				scanf("%d",&salaries.allo);
				getchar();
				printf("请输入该月该教师扣除费用：");
				scanf("%d",&salaries.dedc);
				getchar();
				cal(&salaries);      //计算应得工资和实际工资
				salar_entry(&salaries,month);    //录入
			}
			else {
				printf("该月该教师工资已录入！\n");
				printf("====================================================\n");
				printf("您是否想要修改该月该教师工资信息？（y/n）");
				char mark=getchar();
				invalid(&mark);
				getchar();
				if(mark=='y') {
					system("cls");
					b_sno_alter();
				}
			}
		}
		printf("您是否继续录入教师工资信息？（y/n）");
		char mark=getchar();
		getchar();
		invalid(&mark);
		if(mark=='y') {
			printf("====================================================\n");
			continue;
		}
		break;
	}
	//nprintf("您将返回上一级菜单\n");
	system("pause");
}

void acaandpro_alter(int num,int choic) {
	if(choic==1||choic==2) {
		printf("请输入修改后的值：\n");
		int value;
		if(choic==1) {
			academy_menu();
			scanf("%d",&value);
			getchar();
			while(value!=1&&value!=2&&value!=3&&value!=4&&value!=5) {
			printf("无效操作！\n");
			printf("=============================================\n");
			printf("请您重新输入您的选择：");
			scanf("%d",&value);
			getchar();
			}
		}
		if(choic==2) {
			prof_menu();
			scanf("%d",&value);
			getchar();
			while(value!=1&&value!=2&&value!=3&&value!=4) {
				printf("无效操作！\n");
				printf("=============================================\n");
				printf("请您重新输入您的选择：");
				scanf("%d",&value);
				getchar();
			}
		}
		basic_alter(num,choic,value);
	}
}

void varysala_alter(int sno,int choic) {
	if(choic==3||choic==4||choic==5) {      //修改工资
		printf("请输入待修改工资信息的月份：");    //要询问月份
		int month;
		scanf("%d",&month);
		getchar();
		if(check2(sno,month)) {          //如果没有录入就没法改
		printf("该教师该月工资信息未录入！\n");
		printf("===================================================\n");
		printf("您是否希望先录入该教师该月的工资信息?（y/n）");
		char mark=getchar();
		getchar();
		invalid(&mark);
		if(mark=='y') salar_infor();
		}
		else {
			int value;
			printf("请输入修改后的值：");
			scanf("%d",&value);
			getchar();
			salar_alter(sno,month,choic,value);		
		}
	}
}

void basic_alter(int sno,int choic,int value) {     //具体修改基本信息
	struct Node1 basic[2000];    //结构体数组传参youyilv
	int bastot=load_basic(basic);
	//printf("%d\n",bastot);
	FILE *fp=NULL;
	rewind(fp);
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","wb"))==NULL) {
		printf("错误！无法正常修改！\a\n");
		return;
	}
	for(int i=1;i<=bastot;i++) {
		if(basic[i].sno==sno) {
			if(choic==1) basic[i].aca=value;
			if(choic==2) basic[i].pro=value;
		}
		//if(basic[i].sno!=-1)
		fprintf(fp,"%d %s %d %d\n",basic[i].sno,basic[i].name,basic[i].aca,basic[i].pro);
	}	
	printf("信息修改成功！\n");
	system("pause");
	system("cls");
	fclose(fp);
}

void salar_alter(int sno,int month,int choic,int value) {     //具体修改工资信息
	struct Node2 salar[2000];
	int salatot=load_salar(salar);
	FILE *fp=NULL;
	rewind(fp);
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","wb"))==NULL) {
		printf("错误！无法正常修改！\a\n");
		return;
	}
	for(int i=1;i<=salatot;i++) {
		if(salar[i].sno==sno&&salar[i].month==month) {
			if(choic==3) salar[i].basic_salary=value;
			if(choic==4) salar[i].allo=value;
			if(choic==5) salar[i].dedc=value;
			cal(&salar[i]);
		}
		//if(salar[i].sno!=-1)
		fprintf(fp,"%d %d %d %d %d %d %d\n",salar[i].sno,salar[i].month,salar[i].basic_salary,salar[i].allo,salar[i].dedc,salar[i].should,salar[i].real);
		//printf("信息修改成功！\n");
	}
	printf("信息修改成功！\n");
	system("pause");
	system("cls");

	fclose(fp);
}

void belong_aca(int num) {//输出存储的序号对应的意义
	printf("\t教师所属学院：");
	if(num==1) printf("信息学院\n");
	if(num==2) printf("工学院\n");
	if(num==3) printf("理学院\n");
	if(num==4) printf("人文学院\n");
	if(num==5) printf("生物学院\n");
}

void belong_pro(int num) {    //输出职称序号对应的意义
	printf("\t教师职称：");
	if(num==1) printf("教授\n");
	if(num==2) printf("副教授\n");
	if(num==3) printf("讲师\n");
	if(num==4) printf("助教\n");
}

void print_basic(struct Node1 *basic) {//输出基本信息
	printf("===================================================\n");
	printf("\t教师基本信息\n");
	printf("\t教师工号：%d\n",basic->sno);
	printf("\t教师姓名：%s\n",basic->name);
	belong_aca(basic->aca);
	belong_pro(basic->pro);
	printf("===================================================\n");
}

void print_sala(struct Node2 *sala) {//输出工资信息
	//printf("===================================================\n");
	printf("\t月份：%d\n",sala->month);
	printf("\t教师基本工资：%d\n",sala->basic_salary);
	printf("\t教师绩效津贴：%d\n",sala->allo);
	printf("\t教师本月扣除费用：%d\n",sala->dedc);
	printf("\t教师本月应发工资：%d\n",sala->should);
	printf("\t教师本月实发工资：%d\n",sala->real);
	printf("===================================================\n");
}

void b_sno_print(int sno)  {     //通过工号查找信息时要输出该工号对应教师所有信息    
	FILE *fp_basic=NULL,*fp_sala=NULL;
	if((fp_basic=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	struct Node1 findd_baisc;
	//fflush(fp);
	rewind(fp_basic);
	while((fscanf(fp_basic,"%d%s%d%d",&findd_baisc.sno,findd_baisc.name,&findd_baisc.aca,&findd_baisc.pro))!=EOF) {
		if(findd_baisc.sno==sno)  {
			print_basic(&findd_baisc);
			break;
		}
	}
	fclose(fp_basic);

	if((fp_sala=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	struct Node2 findd_sala;
	rewind(fp_sala);
	int flag=0;
	printf("\t教师工资信息\n");
	//printf("===================================================\n");
	while((fscanf(fp_sala,"%d%d%d%d%d%d%d",&findd_sala.sno,&findd_sala.month,&findd_sala.basic_salary,&findd_sala.allo,&findd_sala.dedc,&findd_sala.should,&findd_sala.real))!=EOF) {
		if(findd_sala.sno==sno)  {
			flag=1;
			print_sala(&findd_sala);
		}
	}
	if(flag==0) {
		printf("该教师工资信息未建立\n");
		printf("===================================================\n");
	}
	fclose(fp_sala);
}

void b_name_print(char name[20]) { //通过姓名输出同名教师的所有信息
	FILE *fp_basic=NULL;
	if((fp_basic=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	struct Node1 findd_baisc;
	rewind(fp_basic);
	while((fscanf(fp_basic,"%d%s%d%d",&findd_baisc.sno,findd_baisc.name,&findd_baisc.aca,&findd_baisc.pro))!=EOF) {
		if(strcmp(findd_baisc.name,name)==0)  {
			b_sno_print(findd_baisc.sno);
		}
	}
	fclose(fp_basic);
}

void basic_dele(struct Node1 *basic,int tot) {   //需要删除的信息做过标记后将全部信息写入
	FILE *fp=NULL;
	rewind(fp);
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","wb"))==NULL) {
		printf("错误！无法正常删除信息\a\n");
		return;
	}

	rewind(fp);
	for(int i=1;i<=tot;i++) {
		if(((basic+i)->sno)!=-1){
			fprintf(fp,"%d %s %d %d\n",((basic+i)->sno),(basic+i)->name,((basic+i)->aca),((basic+i)->pro));
		}
	}
	fclose(fp);
}

void salar_dele(struct Node2 *salar,int tot) {
	FILE *fp=NULL;
	rewind(fp);
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","wb"))==NULL) {
		printf("错误！无法正常删除信息\a\n");
		return;
	}
	rewind(fp);
	for(int i=1;i<=tot;i++) 
		if(((salar+i)->sno)!=-1)
			fprintf(fp,"%d %d %d %d %d %d %d\n",((salar+i)->sno),((salar+i)->month),((salar+i)->basic_salary),
												((salar+i)->allo),((salar+i)->dedc),((salar+i)->should),((salar+i)->real));
	fclose(fp);
}

void real_dele(int num) {    //执行删除操作
	struct Node1 basic[2000];
	struct Node2 salar[2000];
	int bastot=load_basic(basic);
	int salatot=load_salar(salar);
	for(int i=1;i<=bastot;i++) {
		if(basic[i].sno==num) basic[i].sno=-1;
	}
	basic_dele(basic,bastot);
	for(int i=1;i<=salatot;i++) {
		if(salar[i].sno==num) salar[i].sno=-1;
	}
	salar_dele(salar,salatot);
	printf("删除成功！\n");
	system("pause");
}

void dele() {
	char y_n1='y';
	while(y_n1=='y') {
		printf("请输入需要删除信息的教师工号：");
		int num;
		scanf("%d",&num);
		if(!check1(num)) {
			printf("该教师信息未建立！无法删除！请重新操作\n");
			printf("===================================================\n");
			continue;
		}
		getchar();
		printf("您确定删除该工号教师所有信息？（y/n)");
		char flag=getchar();
		invalid(&flag);
		getchar();
		printf("再次确认：（y/n）");
		flag=getchar();
		invalid(&flag);
		getchar();
		if(flag=='y')  real_dele(num);
		else printf("删除失败\n");
		printf("===================================================\n");
		printf("是否继续删除教师信息？（y/n）");
		y_n1=getchar();
		getchar();
	}
}		

void b_name_alter() {   //基于姓名（判断有没有（后输入工号和月份）修改信息——输入姓名后要输出所有同名教师的信息，然后输入工号和月份（选择修改哪月的工资信息），判断有没有，有就改，没有就不改
//同样采用全部载入后再修改判断
	char y_n1='y';
	while(y_n1=='y') {
		system("CLS");
		char name[20];
		printf("请输入待修改教师姓名：");
		scanf("%s",name);
		getchar();
		int flag1=check3(name);        //可以在这个函数里顺便给出输出基本信息和工资信息（如果没有就算了——工资录入发现没有基本信息就会转到基本信息去了
		if(flag1==0) {       //库里没有这个老师
			printf("该教师基本信息未建立，无法修改！\n");
			printf("====================================================\n");
			printf("您是否希望先录入该教师的基本信息？（y/n）");
			char mark=getchar();
			invalid(&mark);
			if(mark=='y') basic_infor();
		}
		char y_n2='y';
		while(y_n2=='y') {
			if(flag1==1) {   //库里有这个老师，要全部输出同名的基本信息和工资信息再修改（已经在check3里输出了）
			b_name_print(name);
			printf("请输出待修改教师的工号：");
			int sno;
			scanf("%d",&sno);   //工号可能不存在，也就是基本信息不存在
			getchar();
			int flag2=check1(sno);
			if(flag2==0) {    //教师信息未录入
				printf("该教师信息未录入！");
				printf("====================================================\n");
				printf("您是否希望先录入该教师的基本信息？（y/n）");
				char mark=getchar();
				getchar();
				invalid(&mark);
				if(mark=='y') basic_infor();
			}
			char y_n3='y';   //是否想修改该名教师的其他信息
			while(y_n3=='y') {//该教师基本信息已经录入，该询问希望修改哪一项
				if(flag2==1) {    
				infor_menu();
				int choic;
				scanf("%d",&choic);
				getchar();
				while(choic!=1&&choic!=2&&choic!=3&&choic!=4&&choic!=5&&choic!=6) {
					printf("无效操作\a\n");
					printf("===================================================\n");
					printf("请您重新输入您的选择：");
					scanf("%d",&choic);
					//printf("%d",choic);	
					getchar();
				}
				acaandpro_alter(sno,choic);     //修改职称和学院
				varysala_alter(sno,choic);
				if(choic==6) break;
				}
				printf("您是否想要修改该教师其他信息？（y/n）");
				scanf("%c",&y_n3);
				getchar();
				invalid(&y_n3);
			}
			}
			printf("您是否想要继续修改该姓名其他老师的信息？（y/n）");
			scanf("%c",&y_n2);
			getchar();
			invalid(&y_n2);
		}
		printf("您是否想要继续基于姓名修改教师信息？（y/n）");
		y_n1=getchar();
		getchar();
		invalid(&y_n1);
	}
	system("pause");
}

void b_sno_alter() {//基于工号修改信息
	char y_n1='y';
	while(y_n1=='y') {
		system("cls");
		int num;
		printf("请输入待修改教师工号：");
		scanf("%d",&num);
		getchar();
		int flag1=check1(num);    //查询基本信息是否存在
		if(flag1==0) {
			printf("该教师基本信息尚未建立！");
			printf("===================================================\n");
			printf("您是否希望首先录入该教师的基本信息？（y/n）");
			char mark=getchar();
			getchar();
			invalid(&mark);
			if(mark=='y')
				basic_infor();
		}
		else {
			b_sno_print(num);     //输入工号后要输出该教师的所有信息
			char y_n2='y';
			while(y_n2=='y') {   //是否希望继续修改该教师的其他信息？
				infor_menu();
				int choic;
				scanf("%d",&choic);
				getchar();
				while(choic!=1&&choic!=2&&choic!=3&&choic!=4&&choic!=5&&choic!=6) {
					printf("无效操作\a\n");
					printf("===================================================\n");
					printf("请您重新输入您的选择：");
					scanf("%d",&choic);
					//printf("%d",choic);	
					getchar();
				}
				acaandpro_alter(num,choic);   //改基本信息
				varysala_alter(num,choic);			//改工资信息
				printf("===================================================\n");
				printf("是否修改该教师的其他信息？（y/n）");
				y_n2=getchar();
				//printf("%d\n",y_n2);
				getchar();
				invalid(&y_n2);
			}
		}
		printf("===================================================\n");
		printf("您是否继续基于工号修改教师信息？（y/n）");
		y_n1=getchar();
		getchar();
		invalid(&y_n1);
	}
	//printf("您将返回上一级菜单\n");
	system("pause");
}

void al_ter() {    //更改，选择需要更改的信息（需要讨论没有工资信息的情况）	
	char y_n1='y';
	while(y_n1=='y') {
		system("CLS");
		second_menu2();
		int choic;
		scanf("%d",&choic);
		getchar();
		while(choic!=1&&choic!=2&&choic!=3&&choic!=4) {
			printf("无效操作\a\n");
			printf("===================================================\n");
			printf("请您重新输入您的选择：\n");
			scanf("%d",&choic);
			getchar();
		}
		if(choic==1) {
			b_sno_alter();
		}
		if(choic==2) {
			b_name_alter();
		}
		if(choic==3) {
			dele();
		}
		if(choic==4) break;
		printf("===================================================\n");
		printf("继续进行数据修改吗？（y/n）");
		y_n1=getchar();
		getchar();
		invalid(&y_n1);
	}
	//printf("您将返回上一级菜单\n");
	system("pause");
}

void en_try() {    //x选择录入工资信息或录入基本信息
	char y_n1='y';
	while(y_n1=='y') {
		system("cls");
		int n;
		second_menu1();    //选择录入基本信息或工资信息的菜单
		scanf("%d",&n);
		getchar();
		while(n!=3&&n!=1&&n!=2) {
			printf("无效操作\a\n");
			printf("===================================================\n");
			printf("请您重新输入您的选择：");
			scanf("%d",&n);
			getchar();
		}
		if(n==1) {   
			basic_infor();
		}
		if(n==2) {
			salar_infor();
		}
		if(n==3) {	
			break;
		}
		printf("您是否继续录入信息？（y/n）");
		//getchar();
		y_n1=getchar();
		getchar();
		invalid(&y_n1);
	}
	printf("您将返回上一级菜单\n");
	system("pause");
}

void b_sno_all(int sno,int month) {//根据工号找到目标
	FILE *fp=NULL;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	rewind(fp);
	struct Node1 try1;
	while(!feof(fp)) {
		if(((fscanf(fp,"%d %s %d %d",&try1.sno,try1.name,&try1.aca,&try1.pro))!=EOF)&&(try1.sno==sno))
			print_basic(&try1);
	}
	fclose(fp);
	
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	rewind(fp);
	struct Node2 try2;
	while(!feof(fp)){		
		if(((fscanf(fp,"%d %d %d %d %d %d %d",&try2.sno,&try2.month,&try2.basic_salary,&try2.allo,&try2.dedc,
			&try2.should,&try2.real))!=EOF)&&(try2.month==month)&&(try2.sno==sno))
			print_sala(&try2);
	}
	fclose(fp);
}

int found_sno(char name[20],int *snoo) {   //找到同名教师的工号，返回个数
	FILE *fp=NULL;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	rewind(fp);
	struct Node1 try1;
	int i=1;
	while(!feof(fp)) {
		if(((fscanf(fp,"%d%s%d%d",&try1.sno,try1.name,&try1.aca,&try1.pro))!=EOF)&&(strcmp(try1.name,name))==0)
			*(snoo+i)=try1.sno,i++;
	}
	fclose(fp);
	return i-1;
}

void disp_name_all() {    //根据姓名查询某月的基本信息和工资信息
	char y_n1='y';
	while(y_n1=='y') {
		char name[20];
		printf("请输入您想要查询的教师的姓名：");
		scanf("%s",name);
		getchar();
		int flag=1;
		if(check3(name)!=1) {    //库里没
			printf("该教师信息未录入\n");
			flag=0;
		}
		if(flag==1) {
			printf("请输入您想要查找的工资信息的月份(1-12)：");
			int month;
			scanf("%d",&month);
			getchar();
			int snoo[200];    //找到所有同名的教师他们的学号，然后排序，输出每一个学号每个月的
			int tot=found_sno(name,snoo); 
			qsort(snoo+1,tot,sizeof(int),cmp2);
			for(int i=1;i<=tot;i++) {
				b_sno_all(snoo[i],month);
				if(check2(snoo[i],month)==1) {
					printf("该教师未录入工资信息！\n");
					printf("===================================================\n");
				}
			}
		}
		printf("是否继续根据姓名查询信息？（y/n）");
		y_n1=getchar();
		invalid(&y_n1);
		getchar();
	}
}

void disp_sno_all() {     //通过工号找到所有的信息
	char y_n1='y';
	while(y_n1=='y') {
		int num;
		printf("请输入所查询教师的工号：");
		scanf("%d",&num);
		getchar();
		int flag=1;
		printf("请输入查询的工资信息的月份(1-12)：");
		int month;
		scanf("%d",&month);
		getchar();
		if(check2(num,month)==1) {
			printf("===================================================\n");
			printf("您所查询的教师未录入信息！\n");
			flag=0;
		}
		if(flag==1) {
			b_sno_all(num,month);
		}
		printf("是否继续根据工号查询信息？（y/n）");
		y_n1=getchar();
		invalid(&y_n1);
		getchar();
	}
	system("pause");
}

void disp_mon_sala() {  //以工号为序，显示某月所有教师的工资信息
	int y_n1='y';
	while(y_n1=='y') {
		system("CLS");
		printf("请输入查询的月份(1-12)：");
		int month;
		scanf("%d",&month);
		getchar();
		struct Node2 salar_mon[2000];
		int mon_tot=load_mon_sala(month,salar_mon);
		qsort(salar_mon+1,mon_tot,sizeof(struct Node2),cmp1);
		if(mon_tot==0) {
			printf("未录入该月工资信息！\n");
			printf("===================================================\n");
		}
		else {
			for(int i=1;i<=mon_tot;i++) {
			printf("\t教师工号：%d\n",salar_mon[i].sno);
			print_sala(&salar_mon[i]);
		}
		}
		printf("是否继续查询其他月份教师的工资信息？(y/n)");
		y_n1=getchar();
		getchar();
	}
	system("pause");
}

void disp_bas_infor() {   //显示所有基本信息
	struct Node1 basic[2000];
	int tot=load_basic(basic);
	printf("%d\n",tot);
	qsort(basic+1,tot,sizeof(struct Node1),cmp1);
	for(int i=1;i<=tot;i++) {
		print_basic(&basic[i]);
	}
}

int foundd_aca(int sno) {  
	FILE *fp=NULL;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	struct Node1 try1;
	rewind(fp);
	int ans;
	while(!feof(fp)) {
		if(((fscanf(fp,"%d %s %d %d",&try1.sno,try1.name,&try1.aca,&try1.pro))!=EOF)&&(try1.sno==sno)) {
			ans=try1.aca;
			break;
		}
	}
	fclose(fp);
	return ans;
}

int foundd_pro(int sno) {  
	FILE *fp=NULL;
	//FILE *fp=NULL;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\basic_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	struct Node1 try1;
	rewind(fp);
	int ans;
	while(!feof(fp)) {
		if(((fscanf(fp,"%d %s %d %d",&try1.sno,try1.name,&try1.aca,&try1.pro))!=EOF)&&(try1.sno==sno)) {
			ans=try1.pro;
			break;
		}
	}
	fclose(fp);
	return ans;
}

void analy_aca(int month) {   //计算各个学院的平均应发工资和实发工资
	FILE *fp=NULL;
	//printf("%d\n",month);
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	struct Node3 sum[10];
	for(int i=1;i<=5;i++) {
		sum[i].aca=i;
		sum[i].peo=0;
		sum[i].sreal=0;
		sum[i].ssho=0;
	}
	//printf("%d\n",month);
	rewind(fp);
	fflush(fp);
	struct Node2 try2;
	fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb");
	while(!feof(fp)){		
		if(((fscanf(fp,"%d%d%d%d%d%d%d",&try2.sno,&try2.month,&try2.basic_salary,&try2.allo,&try2.dedc,
			&try2.should,&try2.real))!=1)&&(try2.month==month)){
				int aca=foundd_aca(try2.sno);
				sum[aca].ssho+=try2.should;
				sum[aca].sreal+=try2.real;
				sum[aca].peo++;
			}
	}
	for(int i=1;i<=5;i++) {
		if(sum[i].peo!=0)
			sum[i].ave_real=(double)(sum[i].sreal/sum[i].peo);
	}
	qsort(sum+1,5,sizeof(struct Node3),cmp3);
	for(int i=1;i<=5;i++) {
		if(sum[i].aca==1&&sum[i].peo!=0) {
			printf("\t信息学院\n");
			printf("应得工资：%.3lf\n",(double)(sum[i].ssho/sum[i].peo));
			printf("实际工资：%.3lf\n",(double)(sum[i].sreal/sum[i].peo));
		}
		if(sum[i].aca==2&&sum[i].peo!=0) {
			printf("\t工学院\n");
			printf("应得工资：%.3lf\n",(double)(sum[i].ssho/sum[i].peo));
			printf("实际工资：%.3lf\n",(double)(sum[i].sreal/sum[i].peo));
		}
		if(sum[i].aca==3&&sum[i].peo!=0) {
			printf("\t理学院\n");
			printf("应得工资：%.3lf\n",(double)(sum[i].ssho/sum[i].peo));
			printf("实际工资：%.3lf\n",(double)(sum[i].sreal/sum[i].peo));
		}
		if(sum[i].aca==4&&sum[i].peo!=0) {
			printf("\t人文学院\n");
			printf("应得工资：%.3lf\n",(double)(sum[i].ssho/sum[i].peo));
			printf("实际工资：%.3lf\n",(double)(sum[i].sreal/sum[i].peo));
		}
		if(sum[i].aca==5&&sum[i].peo!=0) {
			printf("\t生物学院\n");
			//printf("%d\n",sum[i].peo);	
			printf("应得工资：%.3lf\n",(double)(sum[i].ssho/sum[i].peo));
			printf("实际工资：%.3lf\n",(double)(sum[i].sreal/sum[i].peo));
		}
	}
	for(int i=1;i<=5;i++) {
		if(sum[i].peo==0) {
			if(sum[i].aca==1) printf("\t信息学院\n");
			if(sum[i].aca==2) printf("\t工学院\n");
			if(sum[i].aca==3) printf("\t理学院\n");
			if(sum[i].aca==4) printf("\t人文学院\n");
			if(sum[i].aca==5) printf("\t生物学院\n");
			printf("很抱歉，暂无该学院平均工资信息！\n");
		}
	}
	system("pause");
}

void analy_pro(int month) {   //计算各个学院的平均应发工资和实发工资
	FILE *fp=NULL;
	if((fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb"))==NULL){
		printf("文件打开错误!\a\n");
		printf("将退出系统！\n");
		system("pause");
		exit(0);
	}
	struct Node4 sum[10];
	for(int i=1;i<=4;i++) {
		sum[i].pro=i;
		sum[i].peo=0;
		sum[i].sreal=0;
		sum[i].ssho=0;
	}
	rewind(fp);
	fflush(fp);
	struct Node2 try2;
	fp=fopen("C:\\Users\\yuzu\\Desktop\\salar_information.dat","rb");
	while(!feof(fp)){		
		if(((fscanf(fp,"%d%d%d%d%d%d%d",&try2.sno,&try2.month,&try2.basic_salary,&try2.allo,&try2.dedc,
			&try2.should,&try2.real))!=EOF)&&(try2.month==month)){
				int pro=foundd_pro(try2.sno);
				sum[pro].ssho+=try2.should;
				sum[pro].sreal+=try2.real;
				sum[pro].peo++;
			}
	}
	for(int i=1;i<=4;i++) {
		if(sum[i].peo!=0)
			sum[i].ave_real=(sum[i].sreal/sum[i].peo);
	}
	qsort(sum+1,4,sizeof(struct Node4),cmp4);
	for(int i=1;i<=4;i++) {
		if(sum[i].pro==1&&sum[i].peo!=0) {
			printf("\t教授\n");
			printf("应得工资：%.3lf\n",(double)(sum[i].ssho/sum[i].peo));
			printf("实际工资：%.3lf\n",(double)(sum[i].sreal/sum[i].peo));
		}
		if(sum[i].pro==2&&sum[i].peo!=0) {
			printf("\t副教授\n");
			printf("应得工资：%.3lf\n",(double)(sum[i].ssho/sum[i].peo));
			printf("实际工资：%.3lf\n",(double)(sum[i].sreal/sum[i].peo));
		}
		if(sum[i].pro==3&&sum[i].peo!=0) {
			printf("\t讲师\n");
			printf("应得工资：%.3lf\n",(double)(sum[i].ssho/sum[i].peo));
			printf("实际工资：%.3lf\n",(double)(sum[i].sreal/sum[i].peo));
		}
		if(sum[i].pro==4&&sum[i].peo!=0) {
			printf("\t助教\n");
			printf("应得工资：%.3lf\n",(double)(sum[i].ssho/sum[i].peo));
			printf("实际工资：%.3lf\n",(double)(sum[i].sreal/sum[i].peo));
		}
	}
	for(int i=1;i<=4;i++) {
		if(sum[i].peo==0) {
			if(sum[i].pro==1) printf("\t教授\n");
			if(sum[i].pro==2) printf("\t副教授\n");
			if(sum[i].pro==3) printf("\t讲师\n");
			if(sum[i].pro==4) printf("\t助教\n");
			printf("很抱歉，暂无该职称平均工资信息！\n");
		}
	}
	system("pause");
}

void inforanaly() {	
	char y_n1='y';
	while(y_n1=='y') {
		system("CLS");
		analy_menu();
		int choic;
		scanf("%d",&choic);		
		getchar();
		while(choic<1||choic>3) {
			printf("无效操作！\a\n");
			printf("===================================================\n");
			printf("请重新输入您的选择：");
			scanf("%d",&choic);
			getchar();
		}
		if(choic==1) {
			int month;
			printf("请输入月份（1-12）：");
			scanf("%d",&month);
			getchar();
			//printf("%d\n",month);
			analy_aca(month);
			printf("将返回二级菜单\n");
			system("pause");
		}
		if(choic==2) {
			int month;
			printf("请输入月份（1-12）：");
			scanf("%d",&month);
			getchar();
			analy_pro(month);
			printf("将返回二级菜单\n");
			system("pause");
		}
		if(choic==3) {
			break;
		}
		printf("您是否继续进行数据的统计分析？（y/n）");
		y_n1=getchar();
		getchar();
		invalid(&y_n1);
	}
}

void query() {
	char y_n1='y';
	while(y_n1=='y') {
		system("cls");
		int n;
		query_menu();
		scanf("%d",&n);
		getchar();
		while(n>6||n<1) {
			printf("无效操作！\a\n");
			printf("===================================================\n");
			printf("请重新输入您的选择：");
			scanf("%d",&n);
			getchar();
		}
		if(n==1) {
			disp_bas_infor();   //以工号为序（升序）   显示所有基本信息
			printf("将返回二级菜单\n");
			system("pause");
		}
		if(n==2) {	
			disp_mon_sala();   //以工号升序，显示某月教师所有工资信息
			printf("将返回二级菜单\n");
			system("pause");
		}
		if(n==3) {
			disp_sno_all();      //根据工号查询某一月的基本信息和工资信息
			printf("将返回二级菜单\n");
			system("pause");
		}
		if(n==4) {
			disp_name_all();      //根据姓名查询基本信息和工资信息（若有同名，按从小到大排列）
		}
		if(n==5) {
			break;
		}
	}
}
		
int ex() {
	printf("===================================================\n");
	printf("您确定要退出吗？（y/n）");
	char mark=getchar();
	invalid(&mark);
	if(mark=='y') return 1;
	else return 0;
}

int main() {		//主函数，主菜单的选项
	int n;
	system("cls");
	main_menu();
	while(1){      
		scanf("%d",&n);
		getchar();
		if(n<1||n>5) {
			printf("无效操作！\n");
			printf("请重新输入您的选择：");
			continue;
		}
		if(n==5){
			if(ex()) break;
			else  {
				system("cls");
				main_menu();
				continue;
		}
		if(n==1)	{en_try(); system("cls");main_menu(); continue;}
		if(n==2)	{al_ter(); system("cls");main_menu(); continue;}
		if(n==3)	{query(); system("CLS"); main_menu(); continue;}
		if(n==4)	{inforanaly(); system("CLS");main_menu();continue;}	
		}	
	}
}