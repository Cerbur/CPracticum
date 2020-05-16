#include "utils.h"
#include "model.h"
#include <stdio.h>
#include <stdlib.h>
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
    printf("User { \n");
    printf("username : %s\n", user.username);
    printf("password : %s\n", user.password);
    printf("schoolId : %s\n", user.schoolId);
    printf("type: %d }\n" ,user.type);
}
