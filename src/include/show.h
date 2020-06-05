/**
 * 定义一些用于展示的printf的函数
 */
#ifndef HEADER_Show
#define HEADER_Show
void show_welcome();
void show_login();
void show_register();
void show_page_user(char* schoolId,int flag);
void show_post_lost_property(char* schoolId);
void show_post_find_property(char *schoolId);
void show_get_lost_property(char* schoolId);
#endif