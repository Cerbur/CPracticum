#include "operate.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

Status operate_file_init(FILE *userinfo) {
    if ((userinfo = fopen("userinfo.txt","r"))==NULL)
    {
        userinfo = fopen("userinfo.txt","w");
        fclose(userinfo);
    }
    
}

Status operate_insert_userinfo(User user) {
    FILE *file_userinfo;
    file_userinfo = fopen("userinfo.txt","a");
    fprintf(file_userinfo,"%s %s %s %d\n",
    user.schoolId,user.password,user.username,user.type);
    fclose(file_userinfo);
    return OK;
}
Status operate_comfirm_schoolId_unique(char *schoolId) {
    FILE *file_userinfo;
    file_userinfo = fopen("userinfo.txt","r");
    while(!feof(file_userinfo)) {
        char tmpId[50];
        char tmp1[50];
        char tmp2[50];
        int tmp3;
        fscanf(file_userinfo,"%s %s %s %d\n",tmpId,tmp1,tmp2,&tmp3);
        // printf("%s\n",tmpId);
        if (equalsString(schoolId,tmpId))
        {
            return NO;
        }        
    }
    return OK;
}

Status operate_comfirm_login(char *schoolId,char *password) {
    FILE *file_userinfo;
    file_userinfo = fopen("userinfo.txt","r");
    while(!feof(file_userinfo)) {
        char schoolId_tmp[100];
        char password_tmp[200];
        char tmp1[200];
        int tmp2;
        fscanf(file_userinfo,"%s %s %s %d\n",schoolId_tmp,password_tmp,tmp1,&tmp2);
        // printf("%s\n",tmpId);
        if (equalsString(schoolId,schoolId_tmp) && equalsString(password,password_tmp))
        {
            return OK;
        }        
    }
    return NO;
}
