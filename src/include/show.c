#include "show.h"
#include "client.h"
#include <stdio.h>
char *version = "0.0.1beta";
void show_welcome() {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   * - *  校园失物招领系统 * - *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [1]       用户登录             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [2]       注册账户             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [3]       关于作者             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [0]       退出系统             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
// 是┍┐┓┎┑┖└┗┚┙┃▎│
}

void show_login() {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   * - *  校园失物招领系统 * - *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃      --       登录       --      ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃          输入学号与密码          ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}

void show_register() {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   * - *  校园失物招领系统 * - *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃      --       注册       --      ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}

void show_page_user(char* schoolId,int flag) {
    char* user = "用户:";
    char* admin = "管理员:";
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃  * -校园失物招领系统用户页面- *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃\t%s\t%s         ┃\n",flag==2?admin:user,schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [1]       查看失物墙           ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [2]       查看寻物墙           ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [3]       找失主               ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [4]       找东西               ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [5]       个人中心             ┃\n");
    printf("\t\t┃                                  ┃\n");
    if (client_user_remind_look(schoolId) == 1) {
        printf("\t\t┃   [6]       主动提醒[有]         ┃\n");
        printf("\t\t┃                                  ┃\n");
    } else {
        printf("\t\t┃   [6]       主动提醒[无]         ┃\n");
        printf("\t\t┃                                  ┃\n");
    }
    if (flag == 2) {
    printf("\t\t┃   [7]       管理员中心           ┃\n");
    printf("\t\t┃                                  ┃\n");   
    }
    printf("\t\t┃   [0]       退出登录             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}

void show_post_lost_property(char* schoolId) {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   * - *  校园失物招领系统 * - *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃\t账号:\t%s         ┃\n",schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃      --     寻找失主       --    ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}
void show_post_find_property(char *schoolId) {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   * - *  校园失物招领系统 * - *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃\t账号:\t%s         ┃\n",schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃      --     寻找失物       --    ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}

//打印查看失物页面框
void show_get_lost_property(char* schoolId) {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃  * - 校园失物招领系统失物墙 - *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃\t账号:\t%s         ┃\n",schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [1]       进入关键词搜索       ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [2]       展示所有已发布信息   ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [0]       返回上级菜单         ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}
void show_get_find_wall(char* schoolId) {
     printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃  * - 校园失物招领系统寻物墙 - *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃\t账号:\t%s         ┃\n",schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [1]       进入关键词搜索       ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [2]       展示所有已发布信息   ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [0]       返回上级菜单         ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}

void show_user_homepage(char* schoolId) {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃  * -校园失物招领系统用户页面- *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃\t账号:\t%s         ┃\n",schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [1]   删除失物墙的内容         ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [2]   删除寻物墙的内容         ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [3]       修改密码             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [4]       领取的失物           ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [0]       返回上级菜单         ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}

void show_user_update_password(char* schoolId) {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   * - *  校园失物招领系统 * - *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃\t账号:\t%s         ┃\n",schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃      --     修改密码       --    ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}
void show_user_show_mylost(char* schoolId) {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   * - *  校园失物招领系统 * - *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃\t账号:\t%s         ┃\n",schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃      --    领取的失物      --    ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}

void show_admin_homepage(char* schoolId) {
    printf("\n");
    printf("\t\t┍==================================┑\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃  * -校园失物招领系统用户页面- *  ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃\t管理员:\t%s         ┃\n",schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [1]   管理失物墙               ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [2]   管理寻物墙               ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [3]   查看认领关系             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [4]   重置用户密码             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [0]       返回上级菜单         ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}