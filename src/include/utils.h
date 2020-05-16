#include "model.h"
//此头文件存放一些工具以降低耦合度
#ifndef HEADER_Utils
#define HEADER_Utils
#define Status int
#define OK 1
#define NO 0
/**
 * num -> 传入的int类型指针
 * msg -> 输入前的提示字符串
 * return -> 返回码
 */
Status putInt(int* num,char* msg);
Status putChar(char* c,char* msg);
Status putString(char* string,char* msg);
Status confirmInput();









Status toStringUser(User user);
#endif