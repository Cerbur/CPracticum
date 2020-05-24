#include "model.h"
//此头文件存放一些工具以降低耦合度
#ifndef HEADER_Utils
#define HEADER_Utils
#define Status int
#define OK 1
#define NO 0

/**
 * @param num 传入的需要赋值int类型指针
 * @param msg 输入前需要打印的信息
 * @return OK NO
 */
Status putInt(int* num,char* msg);

/**
 * @param c 传入的需要赋值char类型指针
 * @param msg 输入前需要打印的信息
 * @return OK NO
 */
Status putChar(char* c,char* msg);
/**
 * @param string 传入的需要赋值char类型指针
 * @param msg 输入前需要打印的信息
 * @return OK NO
 */
Status putString(char* string,char* msg);

/**
 * 确认函数，即输入Y/N
 */
Status confirmInput();

/**
 * 按规定格式输出user的所有数据
 * @param user实体类
 * @return OK NO
 */
Status toStringUser(User user);

/**
 * 按规定格式输出LostProperty的所有数据
 * @param user实体类
 * @return OK NO
 */
Status toStringLostProperty(LostProperty lp);

/**
 * 比较两个字符串是否相等
 */
Status equalsString(char* string1,char* string2);

/**
 * 通用功能选择器
 */
Status getChoice(int *res,int min,int max);

/**
 * 获取当前时间
 */
Status getTime(char *time_input);

LostNode * new_LostNode(void);
#endif