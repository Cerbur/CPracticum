#include "./include/client.h"
#include <stdio.h>
/**
 * 登录态规范 0->未登录 1已登录
 */
char *session_login_schoolId = "3118007450";   //一个全局指针,做用户登录态保持
int stack = 1;  //表示当前页面所在的操作层
int main(int argc, char const *argv[])
{
    // TODO 这里写基础逻辑
    while (1)
    {
        switch (stack)
        {
            int choice;
            int status;
            case 0:
                client_welcome(&choice);
                switch (choice) {
                case 1:
                    status = -2;
                    while (status == -2) {
                        status = client_user_login(&session_login_schoolId);
                    }
                    if (status == 0) {
                        break;
                    }
                    if (status == 1) {
                        stack = 1;
                        printf("学号:%s登录成功",session_login_schoolId);
                        break;
                    }
                case 2:
                    status = client_registered(&session_login_schoolId);
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
                break;
            case 1:
                stack = 0;
                client_user_page(session_login_schoolId,&choice);
                // printf("登录成功");
                break;
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