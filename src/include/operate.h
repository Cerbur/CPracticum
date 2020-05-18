#include "model.h"
#ifndef HEADER_Operate
#define HEADER_Operate
#define Status int
#define OK 1
#define NO 0
Status operate_file_init();

/**
 * 往userinfo中插入一条user信息
 * @param 完整的User结构体
 * @return OK
 */
Status operate_insert_userinfo(User user);

/**
 * 检查schoolId是否重复
 * @param schoolId
 * @return 1表示无重复，0代表重复
 */
Status operate_comfirm_schoolId_unique(char *schoolId);

/**
 * 校验账号密码是否正确
 */
Status operate_comfirm_login(char *schoolId,char *password);

/**
 * 通过学号获取用户的权限等级 user->1 admin->2
 */
Status operate_get_user_grade(char *schoolId);

/**
 * 通过学号获取用户的username
 */ 
Status operate_get_username_by_schoolId(char *username,char *schoolId);

/**
 * 插入一条失物信息
 */
Status operate_insert_lostinfo(LostProperty lp);

#endif