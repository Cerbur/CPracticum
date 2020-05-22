#include "operate.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

Status operate_file_init() {
    FILE *userinfo;
    if ((userinfo = fopen("userinfo.txt","r"))==NULL)
    {
        userinfo = fopen("userinfo.txt","w");
        fclose(userinfo);
    }

    FILE *lostinfo;
    if ((lostinfo = fopen("lostinfo.txt","r"))==NULL)
    {
        lostinfo = fopen("lostinfo.txt","w");
        fclose(lostinfo);
    }
    return OK;   
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

Status operate_get_user_grade(char *schoolId) {
    FILE *file_userinfo;
    file_userinfo = fopen("userinfo.txt","r");
    while(!feof(file_userinfo)) {
        char tmpId[50];
        char tmp1[50];
        char tmp2[50];
        int grade;
        fscanf(file_userinfo,"%s %s %s %d\n",tmpId,tmp1,tmp2,&grade);
        // printf("%s\n",tmpId);
        if (equalsString(schoolId,tmpId)) {
            return grade;
        }        
    }
    return NO;
}

Status operate_get_username_by_schoolId(char *username,char *schoolId) {
    FILE *file_userinfo;
    file_userinfo = fopen("userinfo.txt","r");
    while(!feof(file_userinfo)) {
        char tmpId[100];
        char tmp1[200];
        char username_tmp[200];
        int tmp3;
        fscanf(file_userinfo,"%s %s %s %d\n",tmpId,tmp1,username_tmp,&tmp3);
        // printf("%s\n",tmpId);
        if (equalsString(schoolId,tmpId)) {
            strcpy(username,username_tmp);
            break;
        }        
    }
    return OK;
}

Status operate_get_lostinfo_maxlid(int *lid) {
    FILE *flie_lostinfo;
    flie_lostinfo = fopen("lostinfo.txt","r");
    int tmp1 = 0;
    while(!feof(flie_lostinfo)) {
        int tmp2;
        char tmp3[100],tmp4[100],tmp5[100],tmp6[100],tmp7[100],tmp8[100];
        fscanf(flie_lostinfo,"%d %s %s %s %s %s %s %d\n",&tmp1,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8,&tmp2);
    }
    printf("%d",tmp1);
    *lid = ++tmp1;
    return OK;
}


Status operate_insert_lostinfo(LostProperty lp){
    lp.status = 0;
    FILE *lostinfo;
    lostinfo = fopen("lostinfo.txt","a");
    fprintf(lostinfo,"%d %s %s %s %s %s %s %d\n",
    lp.lid,lp.name,lp.description,lp.contact_details,
    lp.submit_user_schoolId,lp.submit_user,lp.submit_time,lp.status);
    fclose(lostinfo);
    return OK;
}