#include "operate.h"
#include <stdio.h>
Status operate_file_init(FILE *userinfo) {
    if ((userinfo = fopen("userinfo.txt","r"))==NULL)
    {
        userinfo = fopen("userinfo.txt","w");
        fclose(userinfo);
    }
    
}

Status operate_insert_userinfo(User user) {
    FILE *file_userinfo;
    operate_file_init(file_userinfo);
    file_userinfo = fopen("userinfo.txt","a");
    fprintf(file_userinfo,"%s %s %s %d\n",
    user.username,user.schoolId,user.password,user.type);
    fclose(file_userinfo);
    return OK;
}