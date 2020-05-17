#include <stdio.h>
#include "model.h"
#include "client.h"
#include "show.h"
#include "utils.h"
#include "operate.h"
#include <string.h>
Status client_welcome(int *a) {
    show_welcome();
    getChoice(a,1,5);
    return OK;
}

Status client_user_login(char **session_login_Id){
    show_login();
    char schoolId[100];
    char password[200];
    putString(schoolId,"请输入你的学号或输入0退出:");
    // 0 -> 存在 即当 学号 > 6 和 学号 已经注册时退出登录
    while (strlen(schoolId) < 6 || operate_comfirm_schoolId_unique(schoolId)) {
        if (equalsString(schoolId, "0")) {
            return NO;
        }
        if (equalsString(schoolId, "1")) {
            return -1;
        }
        
        if (strlen(schoolId) < 6) {    
            putString(schoolId,"学号至少6位,请重新输入,输入0回退到上一菜单:"); 
            continue;
        }
        putString(schoolId,"此学号未注册,请重新输入,输入1进入注册页面,输入0回退到上一菜单:");
    }
    putString(password,"请输入你的密码:");
    if (operate_comfirm_login(schoolId,password)) {
        *session_login_Id = schoolId;
        return OK;
    }
    printf("密码错误");
    return -2;
}

Status client_registered(char **session_login_Id){
    show_register();
    int type = 2;
    char username[200];
    char password[200];
    char schoolId[100];
    char adminPwd[100];
    // TODO 校验schoolId是不是重复,规定学号至少6位
    putString(schoolId,"请输入你的学号或输入0退出:");
    while (strlen(schoolId) < 6 || !operate_comfirm_schoolId_unique(schoolId)) {
        if (equalsString(schoolId, "0")) {
            return NO;
        }
        if (strlen(schoolId) < 6) {    
            putString(schoolId,"学号至少6位,请重新输入,输入0回退到上一菜单:"); 
            continue;
        }
        putString(schoolId,"此学号已注册,请重新输入,输入0回退到上一菜单:");
    }
    
    putString(username,"请输入你的姓名:");
    putString(password,"请输入你的密码:");
    
    //确认是否注册为管理员
    putString(adminPwd,"是否注册为管理员,是请输入密码否请输入0:");
    //管理员登录密码为10086
    while (!equalsString(adminPwd, "10086")) {
        if (equalsString(adminPwd, "0")) {
            type = 1;
            break;
        }
        putString(adminPwd,"管理员密码有误,请重新输入,放弃注册成管理员请输入0:");
    }
    // 生成结构体
    User user;
    user.username = username;
    user.schoolId = schoolId;
    user.password = password;
    user.type = type;
    //输出user对象的内容
    toStringUser(user);
    
    //这里进行确认
    int status = confirmInput();
    if (!status)
    {
        return NO;
    }
    if (!operate_insert_userinfo(user))
    {
        return NO;
    }
    printf("恭喜你注册成功\n");
    *session_login_Id = schoolId;
    return OK;
}

Status client_about_author(){
    return OK;
}

Status client_exit(){
    return OK;
}

Status client_user_page(char *session_login_Id,int *choice) {
    show_page_user(session_login_Id,1);
    getChoice(choice,1,6);
    return OK;
}