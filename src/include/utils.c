#include "utils.h"
#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
Status putInt(int* num,char* msg) {

    printf("%s",msg);
    fflush(stdin);
    int status = scanf("%d", num);
    while (getchar() != '\n');
    fflush(stdin);
    if (!status)
    {
        return NO;
    }
    return OK;

}
Status putChar(char* c,char* msg) {
    printf("%s",msg);
    fflush(stdin);
    int status = scanf("%c", c);
    while (getchar() != '\n');
    fflush(stdin);
    if (!status)
    {
        return NO;
    }
    return OK;
}
Status putString(char* string,char* msg){
    printf("%s",msg);
    fflush(stdin);
    int status = scanf("%s", string);
    while (getchar() != '\n');
    if (!status)
    {
        return NO;
    }
    fflush(stdin);
    return OK;
}
Status confirmInput() {
    char confirm;
    putChar(&confirm,"你确认你的输入吗? Y[是]/N[否] :");
    if (confirm == 'Y'|| confirm == 'y')
    {
        return OK;
    }
    return NO;
}

Status toStringUser(User user) {
    printf("\n");
    printf("学号 : %s\n", user.schoolId);
    printf("密码 : %s\n", user.password);
    printf("姓名 : %s\n", user.username);
    printf("账户身份 : "); 
    printf(user.type==1?"普通用户\n":"管理员\n");
    printf("\n");
}

Status toStringLostProperty(LostProperty lp){
    printf("\n");
    if (equalsString(lp.name,"校园卡")) {
        printf("失物的名词:校园卡-%s\n",lp.description);
    } else {
        printf("失物的名称 : %s\n", lp.name);
        printf("失物的描述 : %s\n", lp.description);
    }
    printf("联系方式 : %s\n", lp.contact_details);
    printf("你的用户名 : %s\n", lp.submit_user);
    printf("你的学号 : %s\n", lp.submit_user_schoolId);
    printf("提交时间 : %s\n", lp.submit_time);
    printf("\n");
}

Status equalsString(char* string1,char* string2){
    if (strcmp(string1,string2) == 0)
    {
        return OK;
    }
    return NO;
}

Status getChoice(int *res,int min,int max) {
    int status = putInt(res,"请输入你需要选择的功能:");
    while (!status || !(*res>=min&&*res<=max)) {
        status = putInt(res,"你的输入有误，请重写输入:");
    }
    return OK;
}

Status getTime(char *time_input) {
    time_t now;
    struct tm * target_time;
    time(&now);
    target_time = localtime(&now);

    char time_str[64] = {0};
    char year[5];
    char month[3];
    char day[3];
    char hour[3];
    char min[3];
    sprintf(year,"%d",1900 + target_time->tm_year);
    sprintf(month,"%d",target_time->tm_mon);
    sprintf(day,"%d",target_time->tm_mday);
    sprintf(hour,"%d",target_time->tm_hour);
    sprintf(min,"%d",target_time->tm_min);

    // itoa(1900 + target_time->tm_year,year,10);
    // itoa(target_time->tm_mon,month,10);
    // itoa(target_time->tm_mday,day,10);
    // itoa(target_time->tm_hour,hour,10);
    // itoa(target_time->tm_min,min,10);

    strcat(time_str,year);
    strcat(time_str,"-");
    strcat(time_str,month);
    strcat(time_str,"-");
    strcat(time_str,day);
    strcat(time_str,"-");
    strcat(time_str,hour);
    strcat(time_str,":");
    strcat(time_str,min);

    strcpy(time_input,time_str);
    return OK;
}

char* itoa(int num,char* str,int radix)
{
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//索引表
    unsigned unum;//存放要转换的整数的绝对值,转换的整数可能是负数
    int i=0,j,k;//i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。
 
    //获取要转换的整数的绝对值
    if(radix==10&&num<0)//要转换成十进制数并且是负数
    {
        unum=(unsigned)-num;//将num的绝对值赋给unum
        str[i++]='-';//在字符串最前面设置为'-'号，并且索引加1
    }
    else unum=(unsigned)num;//若是num为正，直接赋值给unum
 
    //转换部分，注意转换后是逆序的
    do
    {
        str[i++]=index[unum%(unsigned)radix];//取unum的最后一位，并设置为str对应位，指示索引加1
        unum/=radix;//unum去掉最后一位
 
    }while(unum);//直至unum为0退出循环
 
    str[i]='\0';//在字符串最后添加'\0'字符，c语言字符串以'\0'结束。
 
    //将顺序调整过来
    if(str[0]=='-') k=1;//如果是负数，符号不用调整，从符号后面开始调整
    else k=0;//不是负数，全部都要调整
 
    char temp;//临时变量，交换两个值时用到
    for(j=k;j<=(i-1)/2;j++)//头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
    {
        temp=str[j];//头部赋值给临时变量
        str[j]=str[i-1+k-j];//尾部赋值给头部
        str[i-1+k-j]=temp;//将临时变量的值(其实就是之前的头部值)赋给尾部
    }
 
    return str;//返回转换后的字符串
 
}