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

#endif