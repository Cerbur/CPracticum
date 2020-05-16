#include <stdio.h>
#include "model.h"
#include "client.h"
#include "show.h"
#include "utils.h"
#include "operate.h"
Status client_welcome() {
    show_welcome();
    int a;
    int status = putInt(&a,"请输入你需要选择的功能:");
    while (!status || !(a>0&&a<6)) {
         putInt(&a,"你的输入有误，请重写输入:");
    }
    switch (a) {
        case 1:
            client_user_login();
            break;
        case 2:
            client_admin_login();
            break;
        case 3:
            client_registered();
            break;
        case 4:
            client_about_author();
            break;
        case 5:
            client_exit();
            break;
    }
    return OK;
}

Status client_user_login(){
    return OK;
}
Status client_admin_login(){
    return OK;
}
Status client_registered(){
    fflush(stdin);
    char username[200];
    char password[20];
    char schoolId[10];
    putString(username,"请输入你的用户名:");
    // TODO 校验username是不是重复
    putString(schoolId,"请输入你的学号:");
    putString(password,"请输入你的密码:");
    //这里需要做确认
    int status = confirmInput();
    if (!status)
    {
        return NO;
    }
    User user;
    user.username = username;
    user.schoolId = schoolId;
    user.password = password;
    user.type = 1;
    toStringUser(user);
    if (!operate_insert_userinfo(user))
    {
        return NO;
    }
    printf("恭喜你注册成功\n");
    return OK;
}
Status client_about_author(){
    return OK;
}
Status client_exit(){
    return OK;
}