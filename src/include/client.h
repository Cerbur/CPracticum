#ifndef HEADER_Client
#define HEADER_Client
#define Status int
#define OK 1
#define NO 0

Status client_file_init();
/**
 * 欢迎页面的客户端
 */
Status client_welcome(int *a);
/**
 * 用户登录页面的客户端
 * @param schoolId学号也作为登录状态的凭证
 * @return 1代表正常登录 -1跳转到登录页面 0返回上一层 -2代表密码错误
 */
Status client_user_login(char *session_login_Id);
Status client_user_exit(char *session_login_Id);
/**
 * 注册页面的客户端
 * @param schoolId学号也作为登录状态的凭证
 */
Status client_registered(char *session_login_Id);
/**
 * 关于作者页面的客户端
 */
Status client_about_author();
/**
 * 退出系统的客户端
 */
Status client_exit();
/**
 * 用户客户端
 */
Status client_user_page(char *session_login_Id,int *choice);
Status client_lost_wall(char* schoolId,int *choice);
Status client_find_wall(char* schoolId,int *choice);

Status client_post_lost_property(char *session_login_Id);
/**
 * 发布寻物
 */
Status client_post_find_property(char* session_login_Id);
/**
 * 获取所有失物 
 */
Status client_get_lost_all(char* schoolId);
/**
 * 获取所有寻物 
 */
Status client_get_find_all(char* schoolId);
Status client_search_find_all(char* schoolId);
/**
 * 关键词搜索
 */
Status client_search_lost_all(char* schoolId);
Status client_user_delete_lost_information(char *schoolId);
Status client_user_delete_find_information(char *schoolId);
Status client_user_homepage(char* schoolId,int *choice);
Status client_user_update_password(char *schoolId);
Status client_user_show_lost(char *schoolId);
Status client_admin_homepage(char* schoolId,int *choice);
Status client_admin_lost_wall(char* schoolId);
Status client_admin_find_wall(char* schoolId);
Status client_admin_receive_wall(char* schoolId);
Status client_admin_reset_password(char* schoolId);
Status client_user_remind_look(char* schoolId);
Status client_user_remind_detail(char* schoolId);
#endif