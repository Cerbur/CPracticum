// #include <windows.h>
#include "./include/client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define clear "clear"
// #define clear "cls"
/**
 * 登录态规范 0->未登录 1已登录
 */
int main(int argc, char const *argv[])
{
    client_file_init();
    int stack = 0;  //表示当前页面所在的操作层
    char session_login_schoolId[100];// = "3118007450";   //一个全局指针,做用户登录态保持
    // TODO 这里写基础逻辑
    while (1) {
        //stack = 0 为未登录,引导用户登录注册
        while (stack == 0) {   
            system(clear);
            int choice;
            int status;
            client_welcome(&choice);
            system(clear);
            switch (choice) {
            case 1:
                //登录
                status = -2;
                while (status == -2) {
                    //登录模块 by 张远程 这里做了个特殊处理,选择注册会跳到case2
                    status = client_user_login(session_login_schoolId);
                }
                //这里为0就返回上层
                if (status == 0) {
                    break;
                }
                //登录成功
                if (status == 1) {
                    stack = 1;
                    printf("学号:%s登录成功,正在跳转",session_login_schoolId);
                    printf("...");
                    break;
                }
            case 2:
                //用户注册模块by 张远程
                status = client_registered(session_login_schoolId);
                if (status) {
                    stack = 1;
                }
                break;
            case 3:
                //关于作者
                client_about_author();
                break;
            case 0:
                //退出系统
                client_exit();
                break;
            }
        }
        // 用户功能选择界面
        while (stack == 1) {   
            system(clear);
            int choice;
            //展示用户页面 这里做了个处理,对用户是否存在管理员权限来设置choice的范围,普通用户无法输入7
            client_user_page(session_login_schoolId,&choice);
            system(clear);
            switch (choice)
            {
                case 0:
                    //返回上层
                    client_user_exit(session_login_schoolId);
                    stack = 0;
                    break;
                case 1:
                    //跳转到失物墙模块
                    stack = 2;
                    break;
                case 2:
                    //跳转到寻物墙模块
                    stack = 3;
                    break;
                case 3:
                    //发布信息到失物墙 by 冯浩轩
                    client_post_lost_property(session_login_schoolId);
                    break;
                case 4:
                    //发布信息到寻物墙 by 冯浩轩
                    client_post_find_property(session_login_schoolId);
                    system(clear);
                    break;
                case 5:
                    //跳转到个人中心页面
                    stack = 4;
                    break;
                case 6:
                    //主动提醒模块 by 张远程
                    client_user_remind_detail(session_login_schoolId);
                    break;
                case 7:
                    //跳转到管理员页面
                    stack = 5;
                    break;
            }
        }
        //失物墙页面
        while (stack == 2) {
            system(clear);
            int choice;
            //页面层选择功能
            client_lost_wall(session_login_schoolId,&choice);
            switch (choice) {
            case 1:
                //失物关键词搜索并领取模块 by 莫振锋
                client_search_lost_all(session_login_schoolId);
                break;
            case 2:
                //失物查看所有并领取模块 by 莫振锋
                client_get_lost_all(session_login_schoolId);
                break;
            case 0:
                //退出返回上层
                stack = 1;
                break;
            }
        }
        //寻物墙页面
        while (stack == 3) {
            system(clear);
            int choice;
            //页面层选择功能
            client_find_wall(session_login_schoolId,&choice);
            switch (choice) {
            case 1:
                //寻物关键词搜索模块 by 莫振锋
                client_search_find_all(session_login_schoolId);
                break;
            case 2:
                //寻物查看所有模块 by 莫振锋
                client_get_find_all(session_login_schoolId);
                break;
            case 0:
                //退出返回上层
                stack = 1;
                break;
            }
        }
        //个人中心页面
        while (stack == 4) {
            system(clear);
            int choice;
            //页面层选择功能
            client_user_homepage(session_login_schoolId,&choice);
            switch (choice) {
            case 1:
                //用户删除发布的失物墙内容 by 张龙旺
                client_user_delete_lost_information(session_login_schoolId);
                break;
            case 2:
                //用户删除发布的寻物墙内容 by 张龙旺
                client_user_delete_find_information(session_login_schoolId);
                break;
            case 3:
                //用户修改自己的密码 by 张子聪
                client_user_update_password(session_login_schoolId);
                break;
            case 4:
                //用户查看自己领取的失物墙领取关系内容 by 张子聪
                client_user_show_lost(session_login_schoolId);
                break;
            case 0:
                //退出
                stack = 1;
                break;
            }
        }
        //管理员页面
        while (stack == 5) {
            system(clear);
            int choice;
            //页面层选择功能
            client_admin_homepage(session_login_schoolId,&choice);
            switch (choice) {
                case 0:
                    //退出
                    stack = 1;
                    break;
                case 1:
                    //管理员限制发布的失物墙内容的展示 by 张龙旺
                    client_admin_lost_wall(session_login_schoolId);
                    break;
                case 2:
                    //管理员限制发布的寻物墙内容的展示 by 张龙旺
                    client_admin_find_wall(session_login_schoolId);
                    break;
                case 3:
                    //管理员查看所有领取的失物墙领取关系内容 by 张子聪
                    client_admin_receive_wall(session_login_schoolId);
                    break;
                case 4:
                    //管理员重置用户的密码 by 张子聪
                    client_admin_reset_password(session_login_schoolId);
                    break;
            }
        }
    }
    return 0;
}
/**
 *
 * ━━━━━━神兽出没━━━━━━
 * 　　　┏┓　　　┏┓
 * 　　┏┛┻━━━┛┻┓
 * 　　┃　　　　　　　┃
 * 　　┃　　　━　　　┃
 * 　　┃　┳┛　┗┳　 ┃
 * 　　┃　　　　　　　┃
 * 　　┃　　　┻　　　┃
 * 　　┃　　　　　    ┃
 * 　　┗━┓　　　┏━┛Code is far away from bug with the animal protecting
 * 　　　　┃　　　┃    神兽保佑,代码无bug
 * 　　　　┃　　　┃
 * 　　　　┃　　　┗━━━┓
 * 　　　　┃　　　　　　　┣┓
 * 　　　　┃　　　　　　　┏┛
 * 　　　　┗┓┓┏━┳┓┏┛
 * 　　　　　┃┫┫　┃┫┫
 * 　　　　　┗┻┛　┗┻┛
 *
 * ━━━━━━感觉萌萌哒━━━━━━
 */