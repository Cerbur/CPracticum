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