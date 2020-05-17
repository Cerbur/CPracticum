#include "utils.h"
#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    putChar(&confirm,"你确认你的输入吗? Y/N :");
    if (confirm == 'Y'|| confirm == 'y')
    {
        return OK;
    }
    return NO;
}

Status toStringUser(User user) {
    printf("学号 : %s\n", user.schoolId);
    printf("密码 : %s\n", user.password);
    printf("姓名 : %s\n", user.username);
    printf("账户身份 : "); 
    printf(user.type==1?"普通用户\n":"管理员\n");
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