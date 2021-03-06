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
 * @return 1表示不存在，0代表存在
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
Status operate_update_userinfo_user_password(char *schoolId,char *password);
Status operate_remove_receiveinfo_by_type_id(int type,int id);
Status operate_get_receiveinfo_all(ReceiveNode *head);
/**
 * 获取lostinfo表中的lid最大值
 */
Status operate_get_lostinfo_maxlid(int *lid);
/**
 * 插入一条失物信息
 */
Status operate_insert_lostinfo(LostProperty lp);
/**
 * 获取findinfo表中的fid最大值
 */
Status operate_get_lostinfo_maxfid(int *fid);
/**
 * 插入一条寻物信息
 */
Status operate_insert_findinfo(FindProperty fp);
Status operate_get_lostinfo_all(LostNode *head);
Status operate_get_findinfo_all(FindNode *head);
Status operate_update_lostinfo_all(LostNode *head);
Status operate_update_lostinfo_byId_status_to_1(int lid);
Status operate_update_lostinfo_byId_status_to_2(int lid);
Status operate_update_findinfo_byId_status_to_2(int lid);
Status operate_insert_receiverinfo_lost(char *login_schoolId,int lid);
Status operate_update_findinfo_all(FindNode *head);
#endif