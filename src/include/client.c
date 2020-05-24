#include <stdio.h>
#include "model.h"
#include "client.h"
#include "show.h"
#include "utils.h"
#include "operate.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

Status client_file_init() {
    operate_file_init();
    return OK;
}

Status client_welcome(int *a) {
    show_welcome();
    getChoice(a,1,5);
    return OK;
}

Status client_user_login(char *session_login_Id){
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
        //字符串赋值不能用等于
        strcpy(session_login_Id,schoolId);
        return OK;
    }
    printf("密码错误");
    return -2;
}

Status client_user_exit(char *session_login_Id) {
    strcpy(session_login_Id,"");
    printf("退出成功");
    return OK;
}


Status client_registered(char *session_login_Id){
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
     while (strlen(password) < 6 ) {
        putString(password,"密码至少有6位请重新输入:");
     }
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
    //字符串赋值不能用等于
    strcpy(session_login_Id,schoolId);
    return OK;
}

Status client_about_author(){
    return OK;
}

Status client_exit(){
    return OK;
}

Status client_user_page(char *session_login_Id,int *choice) {
    //TODO 获取这个人的权限等级    
    show_page_user(session_login_Id,operate_get_user_grade(session_login_Id));
    getChoice(choice,1,6);
    return OK;
}

Status client_post_lost_property(char *session_login_Id) {
    static char *card_name = "校园卡";

    show_post_lost_property(session_login_Id);
    char name[200]; //失物的名称 如果是校园卡/一卡通输入1 不是校园卡输入名称
    char description[1000]; //失物的描述
    char contact_details[200]; //联系方式
    char submit_user_schoolId[100]; //提交者的schoolId
    char submit_user[100]; //提交者的id
    char submit_time[64];  //提交时间
    putString(name,"请输入你要提交的失物名称,如果是校园卡请输入1,返回上层输入0:");
    while (strlen(name) < 3) {
        if (equalsString(name,"0")) {
            return NO;
        }
        if (equalsString(name,"1")) {
            break;
        }
        putString(name,"请输入的名称太短请重新输入,如果是校园卡请输入1,返回上层输入0:");
    }
    if (equalsString(name,"1")) {
        strcpy(name,card_name);
        putString(description,"请输入校园卡的学号:");
    } else {
        putString(description,"请输入失物的描述:");
    }
    putString(contact_details,"请输入你的联系方式:");
    operate_get_username_by_schoolId(submit_user,session_login_Id);
    getTime(submit_time);
    int lid;
    operate_get_lostinfo_maxlid(&lid);
    LostProperty lp;
    lp.lid = lid;
    lp.name = name;
    lp.description = description;
    lp.contact_details = contact_details;
    lp.submit_user_schoolId = session_login_Id;
    lp.submit_user = submit_user;
    lp.submit_time = submit_time;
    toStringLostProperty(lp);
    //这里进行确认
    int status = confirmInput();
    if (!status)
    {
        return NO;
    }
    if (!operate_insert_lostinfo(lp)) {
        return NO;
    }
    printf("你成功提交了信息到失物墙");
    // printf("client_post_lost_property: name-%s\n",name);
    // printf("client_post_lost_property:%s\n",submit_time);
    return OK;
}

Status client_get_lost_all() {
    //创建一个用来存所有lostinfo的链表头
    LostNode *head = new_LostNode();
    //传入链表头，获得完整信息
    operate_get_lostinfo_all(head);

    //这是链表的遍历方式
    LostNode *p = head;
    while (p != NULL) {
        
        //修改信息，各位仅需要再这里做if判断即可
        strcpy(p->lp.name,"校园卡");
        
        p = p->next;
    }

    //这也是链表的遍历方式
    p = head;
    while (p != NULL) {
        //输出修改后的结果
        printf("%3d %s %s\n",p->lp.lid,p->lp.name,p->lp.description);
        // strcpy(p->lp.name,"一卡通");
        p = p->next;
    }

    //将修改后的结果插入到lostinfo中
    operate_update_lostinfo_all(head);
    free(head);
    head = NULL;
    printf("%p",head);
}