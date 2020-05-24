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
    int stack = 1;  //表示当前页面所在的操作层
    char session_login_schoolId[100] = "3118007450";   //一个全局指针,做用户登录态保持
    // TODO 这里写基础逻辑
    while (1)
    {
        while (stack == 0)
        {   
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
            case 4:
                client_exit();
                break;
            }
        }
        
        while (stack == 1)
        {   
            // system(clear);
            int choice;
            client_user_page(session_login_schoolId,&choice);
            switch (choice)
            {
                case 1:
                    client_get_lost_all(session_login_schoolId);
                    break;
                case 3:
                    system(clear);
                    client_post_lost_property(session_login_schoolId);
                    break;
                case 6:
                    system(clear);
                    client_user_exit(session_login_schoolId);
                    stack = 0;
                    // Sleep(1000);
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