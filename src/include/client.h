#ifndef HEADER_Client
#define HEADER_Client
#define Status int
#define OK 1
#define NO 0

/**
 * 欢迎页面的客户端
 */
Status client_welcome(int *a);
/**
 * 用户登录页面的客户端
 * @param schoolId学号也作为登录状态的凭证
 * @return 1代表正常登录 -1跳转到登录页面 0返回上一层 -2代表密码错误
 */
Status client_user_login(char **session_login_Id);
/**
 * 注册页面的客户端
 * @param schoolId学号也作为登录状态的凭证
 */
Status client_registered(char **session_login_Id);
/**
 * 关于作业页面的客户端
 */
Status client_about_author();
/**
 * 退出系统的客户端
 */
Status client_exit();

Status client_user_page(char *session_login_Id,int *choice);
#endif