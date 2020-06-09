#include "utils.h"
#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
Status putInt(int* num,char* msg) {

    printf("%s",msg);
    fflush(stdin);
    int status = scanf("%d", num);
    while (getchar() != '\n');
    fflush(stdin);
    if (!status)
    {
        return NO;
    }
    return OK;

}
Status putChar(char* c,char* msg) {
    printf("%s",msg);
    fflush(stdin);
    int status = scanf("%c", c);
    while (getchar() != '\n');
    fflush(stdin);
    if (!status)
    {
        return NO;
    }
    return OK;
}
Status putString(char* string,char* msg){
    printf("%s",msg);
    fflush(stdin);
    int status = scanf("%s", string);
    while (getchar() != '\n');
    if (!status)
    {
        return NO;
    }
    fflush(stdin);
    return OK;
}
Status confirmInput() {
    char confirm;
    putChar(&confirm,"你确认你的输入吗? Y[是]/N[否] :");
    if (confirm == 'Y'|| confirm == 'y')
    {
        return OK;
    }
    return NO;
}

Status toStringUser(User user) {
    printf("\n");
    printf("学号 : %s\n", user.schoolId);
    printf("密码 : %s\n", user.password);
    printf("姓名 : %s\n", user.username);
    printf("账户身份 : "); 
    printf(user.type==1?"普通用户\n":"管理员\n");
    printf("\n");
}


Status toStringLostProperty(LostProperty lp){
    printf("\n");
    if (equalsString(lp.name,"校园卡")) {
        printf("失物的名词:校园卡-%s\n",lp.description);
    } else {
        printf("失物的名称 : %s\n", lp.name);
        printf("失物的描述 : %s\n", lp.description);
    }
    printf("联系方式 : %s\n", lp.contact_details);
    printf("你的用户名 : %s\n", lp.submit_user);
    printf("你的学号 : %s\n", lp.submit_user_schoolId);
    printf("提交时间 : %s\n", lp.submit_time);
    printf("\n");
}

void toStringFindProperty(FindProperty fp) {
    printf("\n");
    if (equalsString(fp.name,"校园卡")) {
        printf("失物的名词:校园卡-%s\n",fp.description);
    } else {
        printf("失物的名称 : %s\n", fp.name);
        printf("失物的描述 : %s\n", fp.description);
    }
    printf("联系方式 : %s\n", fp.contact_details);
    printf("你的用户名 : %s\n", fp.submit_user);
    printf("你的学号 : %s\n", fp.submit_user_schoolId);
    printf("提交时间 : %s\n", fp.submit_time);
    printf("\n");
}

Status equalsString(char* string1,char* string2){
    if (strcmp(string1,string2) == 0)
    {
        return OK;
    }
    return NO;
}

Status getChoice(int *res,int min,int max) {
    int status = putInt(res,"请输入你需要选择的功能:");
    while (!status || !(*res>=min&&*res<=max)) {
        status = putInt(res,"你的输入有误，请重写输入:");
    }
    return OK;
}

Status getTime(char *time_input) {
    time_t now;
    struct tm * target_time;
    time(&now);
    target_time = localtime(&now);

    char time_str[64] = {0};
    char year[5];
    char month[3];
    char day[3];
    char hour[3];
    char min[3];
    sprintf(year,"%d",1900 + target_time->tm_year);
    sprintf(month,"%d",target_time->tm_mon+1);
    sprintf(day,"%d",target_time->tm_mday);
    sprintf(hour,"%d",target_time->tm_hour);
    sprintf(min,"%d",target_time->tm_min);

    // itoa(1900 + target_time->tm_year,year,10);
    // itoa(target_time->tm_mon,month,10);
    // itoa(target_time->tm_mday,day,10);
    // itoa(target_time->tm_hour,hour,10);
    // itoa(target_time->tm_min,min,10);

    strcat(time_str,year);
    strcat(time_str,"-");
    strcat(time_str,month);
    strcat(time_str,"-");
    strcat(time_str,day);
    strcat(time_str,"-");
    strcat(time_str,hour);
    strcat(time_str,":");
    strcat(time_str,min);

    strcpy(time_input,time_str);
    return OK;
}

LostNode *new_LostNode(void){
    LostNode *p =  (LostNode*)malloc(sizeof(LostNode));
    p->next = NULL;
    p->lp.name = (char*)malloc(sizeof(char)*200);
    p->lp.description = (char*)malloc(sizeof(char)*200);
    p->lp.contact_details = (char*)malloc(sizeof(char)*200);
    p->lp.submit_user_schoolId = (char*)malloc(sizeof(char)*200);
    p->lp.submit_user = (char*)malloc(sizeof(char)*200);
    p->lp.submit_time = (char*)malloc(sizeof(char)*200);
    return p;
}

FindNode *new_FindNode(void){
    FindNode *p =  (FindNode*)malloc(sizeof(FindNode));
    p->next = NULL;
    p->fp.name = (char*)malloc(sizeof(char)*200);
    p->fp.description = (char*)malloc(sizeof(char)*200);
    p->fp.contact_details = (char*)malloc(sizeof(char)*200);
    p->fp.submit_user_schoolId = (char*)malloc(sizeof(char)*200);
    p->fp.submit_user = (char*)malloc(sizeof(char)*200);
    p->fp.submit_time = (char*)malloc(sizeof(char)*200);
    return p;
}

UserNode *new_UserNode(void) {
    UserNode *p =  (UserNode*)malloc(sizeof(UserNode));
    p->next = NULL;
    p->user.username = (char*)malloc(sizeof(char)*200);
    p->user.password = (char*)malloc(sizeof(char)*200);
    p->user.schoolId = (char*)malloc(sizeof(char)*200);
    return p;
}

ReceiveNode *new_ReceiveNode(void) {
    ReceiveNode *p =  (ReceiveNode*)malloc(sizeof(ReceiveNode));
    p->next = NULL;
    p->r.receive_time = (char*)malloc(sizeof(char)*200);
    p->r.receive_user_schoolId = (char*)malloc(sizeof(char)*200);
    return p;
}

Status freeReceiveNode(ReceiveNode *head) {
    ReceiveNode *p = head,*q;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q->r.receive_time);
        free(q->r.receive_user_schoolId);
        free(q);
        q = NULL;
    }
}

//NEXT数组 
void Next(char*T,int *next){
    int i=1;
    next[1]=0;
    int j=0;
    while (i<strlen(T)) {
        if (j==0||T[i-1]==T[j-1]) {
            i++;
            j++;
            next[i]=j;
        }else{
            j=next[j];
        }
    }
}

//kmp算法  找到返回第一个字符的位置，匹配不到则返回-1 
int KMP(char*S,char*T){
    int next[10];
    Next(T,next);//根据模式串T,初始化next数组
    int i=1;
    int j=1;
    while (i<=strlen(S)&&j<=strlen(T)) {
        //j==0:代表模式串的第一个字符就和当前测试的字符不相等；S[i-1]==T[j-1],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
        if (j==0 || S[i-1]==T[j-1]) {
            i++;
            j++;
        }
        else{
            j=next[j];//如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
        }
    }
    if (j>strlen(T)) {//如果条件为真，说明匹配成功
        return i-(int)strlen(T);
    }
    return -1;
}


Status freeFindNode(FindNode *head) {
    FindNode *p = head,*q;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q->fp.name);
        free(q->fp.description);
        free(q->fp.contact_details);
        free(q->fp.submit_user_schoolId);
        free(q->fp.submit_user);
        free(q->fp.submit_time);
        free(q);
        q = NULL;
    }
}

Status freeLostNode(LostNode *head) {
    LostNode *p = head,*q;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q->lp.name);
        free(q->lp.description);
        free(q->lp.contact_details);
        free(q->lp.submit_user_schoolId);
        free(q->lp.submit_user);
        free(q->lp.submit_time);
        free(q);
        q = NULL;
    }
}

Status freeUserNode(UserNode *head) {
    UserNode *p = head,*q;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q->user.schoolId);
        free(q->user.password);
        free(q->user.username);
        free(q);
        q = NULL;
    }
}