//此头文件存放一些结构体
#ifndef HEADER_Model
#define HEADER_Model
#define String char*
/**
 * 失物的实体类
 * Cerbur
 */
typedef struct LostProperty
{
    String name; //失物的名称 如果是校园卡/一卡通输入1 不是校园卡输入名称
    String description; //失物的描述
    String contact_details; //联系方式
    String submit_user_schoolId; //提交者的schoolId
    String submit_user; //提交者的username
    String submit_time; //提交的时间
    int status; //状态 1-已经找回，0未领取
} LostProperty;
/**
 * 失物实体类的单向链表
 */
typedef struct LostNode
{
    LostProperty lp;
    struct LostNode* next;
} LostNode;

/**
 * 用户信息的实体
 */
typedef struct User
{
    String username; //username
    String password; //密码
    String schoolId;
    int type; //用户类型 1-普通用户 2-管理员
}User;

#endif