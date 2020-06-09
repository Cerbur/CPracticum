// #include <windows.h>
#include "./include/client.h"
#include "./include/operate.h"
#include "./include/utils.h"
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
        while (stack == 0) {   
            system(clear);
            int choice;
            int status;
            client_welcome(&choice);
            switch (choice) {
            case 1:
                status = -2;
                while (status == -2) {
                    system(clear);
                    status = client_user_login(session_login_schoolId);
                }
                if (status == 0) {
                    system(clear);
                    break;
                }
                if (status == 1) {
                    stack = 1;
                    printf("学号:%s登录成功,正在跳转",session_login_schoolId);
                    printf("...");
                    system(clear);
                    break;
                }
            case 2:
                system(clear);
                status = client_registered(session_login_schoolId);
                if (status) {
                    stack = 1;
                }
                break;
            case 3:
                client_about_author();
                break;
            case 0:
                client_exit();
                break;
            }
        }
        while (stack == 1) {   
            // system(clear);
            int choice;
            client_user_page(session_login_schoolId,&choice);
            switch (choice)
            {
                case 0:
                    system(clear);
                    client_user_exit(session_login_schoolId);
                    stack = 0;
                    break;
                case 1:
                    stack = 2;
                    break;
                case 2:
                    stack = 3;
                    break;
                case 3:
                    system(clear);
                    client_post_lost_property(session_login_schoolId);
                    break;
                case 4:
                    client_post_find_property(session_login_schoolId);
                    system(clear);
                    break;
                case 5:
                    stack = 4;
                    break;
                case 6:
                    client_user_remind_detail(session_login_schoolId);
                    break;
                case 7:
                    stack = 5;
                    break;
            }
        }
        while (stack == 2) {
            int choice;
            //页面层选择功能
            client_lost_wall(session_login_schoolId,&choice);
            switch (choice) {
            case 1:
                //关键词搜索
                client_search_find_all(session_login_schoolId);
                break;
            case 2:
                //查看所有
                client_get_find_all(session_login_schoolId);
                break;
            case 0:
                //退出
                stack = 1;
                break;
            }
        }
        while (stack == 3) {
            int choice;
            //页面层选择功能
            client_find_wall(session_login_schoolId,&choice);
            switch (choice) {
            case 1:
                //关键词搜索
                client_search_find_all(session_login_schoolId);
                break;
            case 2:
                //查看所有
                client_get_find_all(session_login_schoolId);
                break;
            case 0:
                //退出
                stack = 1;
                break;
            }
        }
        while (stack == 4) {
            int choice;
            //页面层选择功能
            client_user_homepage(session_login_schoolId,&choice);
            switch (choice) {
            case 1:
                client_user_delete_lost_information(session_login_schoolId);
                break;
            case 2:
                client_user_delete_find_information(session_login_schoolId);
                break;
                //管理员功能可以看operate_update_lostinfo_byId_status_to_1(int lid);这个函数，具体我就不写了，和上面一样
            case 3:
                client_user_update_password(session_login_schoolId);
                break;
            case 4:
                client_user_show_lost(session_login_schoolId);
                break;
            case 0:
                //退出
                stack = 1;
                break;
            }
        }
        while (stack == 5) {
            int choice;
            //页面层选择功能
            client_admin_homepage(session_login_schoolId,&choice);
            switch (choice) {
                case 0:
                    //退出
                    stack = 1;
                    break;
                case 1:
                    client_admin_lost_wall(session_login_schoolId);
                    break;
                case 2:
                    client_admin_find_wall(session_login_schoolId);
                    break;
                case 3:
                    client_admin_receive_wall(session_login_schoolId);
                    break;
                case 4:
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