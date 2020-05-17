#include "show.h"
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
    printf("\t\t┃   [3]       修改密码             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [4]       关于作者             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [5]       退出系统             ┃\n");
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
    printf("\t\t┃\t%s\t%s         ┃\n",flag==1?admin:user,schoolId);
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [1]       查看失物墙           ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [2]       查看寻物墙           ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [3]       发布失物             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [4]       发布寻物             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [5]       修改密码             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃   [6]       退出登录             ┃\n");
    printf("\t\t┃                                  ┃\n");
    printf("\t\t┃         version %s        ┃\n",version);
    printf("\t\t┖==================================┙\n");
    printf("\n");
}
