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
    getChoice(a,0,3);
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
    exit(0);
    return OK;
}

Status client_user_page(char *session_login_Id,int *choice) {
    //TODO 获取这个人的权限等级    
    int user_grade = operate_get_user_grade(session_login_Id);
    show_page_user(session_login_Id,user_grade);
    int max = 5;
    int min = 0;
    if (user_grade == 2) {
        max = 6;
    }

    getChoice(choice,min,max);
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

Status client_post_find_property(char* session_login_Id) {
    static char *card_name = "校园卡";

    show_post_find_property(session_login_Id);
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
    int fid;
    operate_get_lostinfo_maxfid(&fid);
    FindProperty fp;
    fp.fid = fid;
    fp.name = name;
    fp.description = description;
    fp.contact_details = contact_details;
    fp.submit_user_schoolId = session_login_Id;
    fp.submit_user = submit_user;
    fp.submit_time = submit_time;
    toStringFindProperty(fp);
    //这里进行确认
    int status = confirmInput();
    if (!status)
    {
        return NO;
    }
    if (!operate_insert_findinfo(fp)) {
        return NO;
    }
    printf("你成功提交了信息到寻物墙");
    return OK;
}

Status client_lost_wall(char* schoolId,int *choice) {
    //打印框框
    show_get_lost_property(schoolId);
    //选择
    getChoice(choice,0,2);
}

Status client_search_lost_all(char* schoolId) {
    //创建一个用来存所有lostinfo的链表头
    LostNode *head = new_LostNode();
    //传入链表头，获得完整信息,现在这个head有着所有的完整信息
    operate_get_lostinfo_all(head);
    //输入关键字
    char keyword[200];
	int status=putString(keyword,"请输入关键词,输入0返回上层：");
    if (equalsString(keyword,"0")) {
        freeLostNode(head);
        return NO;
    }

    //这也是链表的遍历方式
    int flag = 1;   //用于确认总共有多少输出数据
    LostNode *p = head;
    printf("序号 \t\t物品 \t\t描述\n");
    printf("=====================================\n");
    while (p != NULL) {
        //输出所有结果
        //第一个确定状态为未查询，第二个条件确定在名字和描述中存在关键字
        if (p->lp.status == 0 &&
         (KMP(p->lp.name,keyword) != -1 || 
         KMP(p->lp.description,keyword) != -1)) {
            //符合要求打印数据,同时flag++
            printf("%3d \t\t%s \t\t%s\n",flag++,p->lp.name,p->lp.description);
        }
        p = p->next;
    }
    //因为最后一次符合后flag会比真实的数据多1所有-1
    flag--;
    //如果没有对应的数据
    if (flag == 0)
    {
        printf("未找到相关数据回车,返回上层\n");
        //释放head链表的内存防止内存溢出
        freeLostNode(head);
        //让用户打一个回车
        getchar();
        return NO;
    }
    //用户选择需要领取的物品序号
    int choice;
    status = putInt(&choice,"输入对应数字进行领取或输入0退出:");
    while (!status || !(choice>=0&&choice<=flag)) {
        status = putInt(&choice,"你的输入有误，请重写输入:");
    }
    if (choice == 0)
    {
        //释放head链表的内存防止内存溢出
        freeLostNode(head);
        return NO;
    }
    //用户确认时候领取
    printf("你要领取序号%d,",choice);
    status = confirmInput();
    if (!status)
    {
        freeLostNode(head);
        return NO;
    }
    status = 0; //用来与选择做比较
    p = head;
    while (p != NULL) {
        if (p->lp.status == 0 && 
        (KMP(p->lp.name,keyword) != -1 || 
        KMP(p->lp.description,keyword) != -1)) {
            status++;
        }
        if (status == choice) {
            break;
        }
        
        p = p->next;
    }
    //输出所有结果
    printf("失物:%s 失物描述:%s 发布者:%s 发布者联系方式:%s\n",p->lp.name,p->lp.description,p->lp.submit_user,p->lp.contact_details);
    //更新领取状态
    operate_update_lostinfo_byId_status_to_1(p->lp.lid);
    //插入到被领取关系表中
    operate_insert_receiverinfo_lost(schoolId,p->lp.lid);
    printf("输入回车返回上层\n");
    getchar(); //用来暂停的
    return OK;
}
Status client_get_lost_all(char* schoolId) {
    //创建一个用来存所有lostinfo的链表头
    LostNode *head = new_LostNode();
    //传入链表头，获得完整信息
    operate_get_lostinfo_all(head);
    printf("序号 \t\t物品 \t\t描述\n");
    printf("=====================================\n");
    //这也是链表的遍历方式
    int flag = 1;
    LostNode *p = head;
    while (p != NULL) {
        //输出所有结果
        if (p->lp.status == 0)
        {
            printf("%3d \t\t%s \t\t%s\n",flag++,p->lp.name,p->lp.description);
        }
        p = p->next;
    }
    flag--;
    //如果没有对应的数据
    if (flag == 0)
    {
        printf("未找到相关数据回车,返回上层\n");
        freeLostNode(head);
        getchar();
        return NO;
    }
    int choice;
    int status = putInt(&choice,"输入对应数字进行领取或输入0退出:");
    while (!status || !(choice>=0&&choice<=flag)) {
        status = putInt(&choice,"你的输入有误，请重写输入:");
    }
    if (choice == 0)
    {
        freeLostNode(head);
        return NO;
    }
    printf("你要领取序号%d,",choice);
    status = confirmInput();
    if (!status)
    {
        freeLostNode(head);
        return NO;
    }
    status = 0;
    p = head;
    while (p != NULL) {
        if (p->lp.status == 0) {
            status++;
        }
        if (status == choice) {
            break;
        }
        p = p->next;
    }
    //输出所有结果
    printf("失物:%s 失物描述:%s 发布者:%s 发布者联系方式:%s\n",p->lp.name,p->lp.description,p->lp.submit_user,p->lp.contact_details);
    operate_update_lostinfo_byId_status_to_1(p->lp.lid);
    operate_insert_receiverinfo_lost(schoolId,p->lp.lid);
    printf("输入回车返回上层\n");
    getchar(); //用来暂停的
    return OK;
}

Status client_user_delete_lost_information(char *schoolId) {
    //创建一个用来存所有lostinfo的链表头
    LostNode *head = new_LostNode();
    //传入链表头，获得完整信息
    operate_get_lostinfo_all(head);
    printf("序号 \t\t物品 \t\t描述 \t\t状态\n");
    printf("=====================================\n");
    //这也是链表的遍历方式
    int flag = 1;
    LostNode *p = head;
    while (p != NULL) {
        //输出所有结果
        if (equalsString(schoolId,p->lp.submit_user_schoolId)) {
            printf("%3d \t\t%s \t\t%s \t\t",flag++,p->lp.name,p->lp.description);
            if (p->lp.status == 0) {
                printf("未领取");
            } else if (p->lp.status == 1) {
                printf("被领取");
            } else {
                printf("管理员不予显示，请修改");
            }
            printf("\n");
        }
        p = p->next;
    }
    flag--;
    //如果没有对应的数据
    if (flag == 0)
    {
        printf("未找到相关数据回车,返回上层\n");
        freeLostNode(head);
        getchar();
        return NO;
    } else
    {
        printf("共%d条信息\n",flag);
    }
    
    int choice;
    int status = putInt(&choice,"输入对应数字进行删除或输入0退出:");
    while (!status || !(choice>=0&&choice<=flag)) {
        status = putInt(&choice,"你的输入有误，请重写输入:");
    }
    if (choice == 0)
    {
        freeLostNode(head);
        return NO;
    }
    printf("你要删除序号%d,",choice);
    status = confirmInput();
    if (!status)
    {
        freeLostNode(head);
        return NO;
    }
    status = 0;
    p = head;
    LostNode *q = head;
    while (p != NULL) {
        if (equalsString(schoolId,p->lp.submit_user_schoolId)) {
            status++;
        }
        if (status == choice) {
            break;
        }
        q = p;  //记录下p的前一个节点
        p = p->next;
    }
    if (q != p)
    {
        q->next = p->next; //删除节点p
        p->next = NULL; //将p->next制空
    } else {
        p = head;
        head = head->next;
        p->next = NULL;
    }
    operate_remove_receiveinfo_by_type_id(1,p->lp.lid);
    freeLostNode(p);    //释放节点p;
    operate_update_lostinfo_all(head);
    printf("删除成功\n");
    printf("输入回车返回上层\n");
    getchar(); //用来暂停的
    return OK;
}


Status client_user_delete_find_information(char *schoolId) {
    //创建一个用来存所有lostinfo的链表头
    FindNode *head = new_FindNode();
    //传入链表头，获得完整信息
    operate_get_findinfo_all(head);
    printf("序号 \t\t物品 \t\t描述 \t\t状态\n");
    printf("=====================================\n");
    //这也是链表的遍历方式
    int flag = 1;
    FindNode *p = head;
    while (p != NULL) {
        //输出所有结果
        if (equalsString(schoolId,p->fp.submit_user_schoolId)) {
            printf("%3d \t\t%s \t\t%s \t\t",flag++,p->fp.name,p->fp.description);
            if (p->fp.status == 0) {
                printf("未领取");
            } else if (p->fp.status == 1) {
                printf("被领取");
            } else {
                printf("管理员不予显示，请修改");
            }
            printf("\n");
        }
        p = p->next;
    }
    flag--;
    //如果没有对应的数据
    if (flag == 0)
    {
        printf("未找到相关数据回车,返回上层\n");
        freeFindNode(head);
        getchar();
        return NO;
    } else
    {
        printf("共%d条信息\n",flag);
    }
    
    int choice;
    int status = putInt(&choice,"输入对应数字进行删除或输入0退出:");
    while (!status || !(choice>=0&&choice<=flag)) {
        status = putInt(&choice,"你的输入有误，请重写输入:");
    }
    if (choice == 0)
    {
        freeFindNode(head);
        return NO;
    }
    printf("你要删除序号%d,",choice);
    status = confirmInput();
    if (!status)
    {
        freeFindNode(head);
        return NO;
    }
    status = 0;
    p = head;
    FindNode *q = head;
    while (p != NULL) {
        if (equalsString(schoolId,p->fp.submit_user_schoolId)) {
            status++;
        }
        if (status == choice) {
            break;
        }
        q = p;  //记录下p的前一个节点
        p = p->next;
    }
    if (q != p)
    {
        q->next = p->next; //删除节点p
        p->next = NULL; //将p->next制空
    } else {
        p = head;
        head = head->next;
        p->next = NULL;
    }
    operate_remove_receiveinfo_by_type_id(2,p->fp.fid);
    freeFindNode(p);    //释放节点p;
    operate_update_findinfo_all(head);
    printf("删除成功\n");
    printf("输入回车返回上层\n");
    getchar(); //用来暂停的
    return OK;
}

Status client_user_homepage(char* schoolId,int *choice) {
    //打印框框
    show_user_homepage(schoolId);
    //选择
    getChoice(choice,0,3);
    return OK;
}

Status client_user_update_password(char *schoolId) {
    show_user_update_password(schoolId);
    char password_old[200];
    putString(password_old,"请输入你的密码,输入0返回上级:");
    while (1) {
        if (equalsString(password_old,"0")) {
            return NO;
        }
        if (strlen(password_old) < 6)
        {
            putString(password_old,"密码至少有6位请重新输入,输入0返回上级:");
            continue;
        }
        
        if (operate_comfirm_login(schoolId,password_old) == OK) {
            break;
        } else {
            putString(password_old,"密码错误请重新输入,输入0返回上级:");
            continue;
        }
        
    }
    char password_new[200];
    putString(password_new,"请输入你的新密码:");
    while (strlen(password_new) < 6 ) {
        putString(password_new,"密码至少有6位请重新输入:");
    }
    if (operate_update_userinfo_user_password(schoolId,password_new)){
        printf("修改成功\n");
    } else {
        printf("修改失败出现异常\n");
        return NO;
    }
    printf("输入回车返回上层");
    getchar();
    return OK;
}

