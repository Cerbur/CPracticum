#include "operate.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
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
    FILE *findinfo;
    if ((findinfo = fopen("findinfo.txt","r"))==NULL)
    {
        findinfo = fopen("findinfo.txt","w");
        fclose(findinfo);
    }
    FILE *receiveinfo;
    if ((receiveinfo = fopen("receiveinfo.txt","r"))==NULL)
    {
        receiveinfo = fopen("receiveinfo.txt","w");
        fclose(receiveinfo);
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
            fclose(file_userinfo);
            return NO;
        }        
    }
    fclose(file_userinfo);
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
            fclose(file_userinfo);
            return OK;
        }        
    }
    fclose(file_userinfo);
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
            fclose(file_userinfo);
            return grade;
        }        
    }
    fclose(file_userinfo);
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
    fclose(file_userinfo);
    return OK;
}

Status operate_update_userinfo_user_password(char *schoolId,char *password) {
    UserNode *head,*p;
    head = new_UserNode();
    p = head;
    FILE *file_userinfo;
    file_userinfo = fopen("userinfo.txt","r");
    while(1) {
        fscanf(file_userinfo,"%s %s %s %d\n",p->user.schoolId
        ,p->user.password,p->user.username,&p->user.type);
        if (!feof(file_userinfo)) {
            p->next = new_UserNode();
            p = p->next;
        } else {
            break;
        }
        
    }
    fclose(file_userinfo);
    file_userinfo = fopen("userinfo.txt","w");
    fclose(file_userinfo);
    file_userinfo = fopen("userinfo.txt","a");
    p = head;
    while (p != NULL) {
        if (equalsString(p->user.schoolId,schoolId)){
            free(p->user.password);
            p->user.password = password;
        }
        fprintf(file_userinfo,"%s %s %s %d\n",p->user.schoolId
        ,p->user.password,p->user.username,p->user.type);
        p = p->next;
    }
    fclose(file_userinfo);
    return OK;
}

Status operate_remove_receiveinfo_by_type_id(int type,int id) {
    ReceiveNode *head,*p;
    head = new_ReceiveNode();
    p = head;
    FILE *file_receiveinfo;
    file_receiveinfo = fopen("receiveinfo.txt","r");
    while(1) {
        fscanf(file_receiveinfo,"%d %d %s %s\n",&p->r.type,&p->r.lfid,p->r.receive_user_schoolId,p->r.receive_time);
        if (!feof(file_receiveinfo)) {
            p->next = new_ReceiveNode();
            p = p->next;
        } else {
            break;
        }
        
    }
    fclose(file_receiveinfo);
    file_receiveinfo = fopen("receiveinfo.txt","w");
    fclose(file_receiveinfo);
    file_receiveinfo = fopen("receiveinfo.txt","a");
    p = head;
    while (p != NULL) {
        if (p->r.lfid == id && p->r.type == type ){
            p = p->next;
            continue;
        }
        fprintf(file_receiveinfo,"%d %d %s %s\n",p->r.type
        ,p->r.lfid,p->r.receive_user_schoolId,p->r.receive_time);
        p = p->next;
    }
    freeReceiveNode(head);
    fclose(file_receiveinfo);
    return OK;
}


Status operate_get_receiveinfo_all(ReceiveNode *head) {
    ReceiveNode *p = head;
    FILE *file_receiveinfo;
    file_receiveinfo = fopen("receiveinfo.txt","r");
    while(1) {
        fscanf(file_receiveinfo,"%d %d %s %s\n",&p->r.type,&p->r.lfid,p->r.receive_user_schoolId,p->r.receive_time);
        if (!feof(file_receiveinfo))
        {
            p -> next = new_ReceiveNode();
            p = p -> next;
        } else {
            break;
        }
        
    }
    fclose(file_receiveinfo);
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
    *lid = ++tmp1;
    fclose(flie_lostinfo);
    return OK;
}


Status operate_insert_lostinfo(LostProperty lp){
    lp.status = 0;
    FILE *flie_lostinfo;
    flie_lostinfo = fopen("lostinfo.txt","a");
    fprintf(flie_lostinfo,"%d %s %s %s %s %s %s %d\n",
    lp.lid,lp.name,lp.description,lp.contact_details,
    lp.submit_user_schoolId,lp.submit_user,lp.submit_time,lp.status);
    fclose(flie_lostinfo);
    return OK;
}

Status operate_get_lostinfo_maxfid(int *fid) {
    FILE *flie_findinfo;
    flie_findinfo = fopen("findinfo.txt","r");
    int tmp1 = 0;
    while(!feof(flie_findinfo)) {
        int tmp2;
        char tmp3[100],tmp4[100],tmp5[100],tmp6[100],tmp7[100],tmp8[100];
        fscanf(flie_findinfo,"%d %s %s %s %s %s %s %d\n",&tmp1,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8,&tmp2);
    }
    *fid = ++tmp1;
    fclose(flie_findinfo);
    return OK;
}

Status operate_insert_findinfo(FindProperty fp) {
    fp.status = 0;
    FILE *flie_findinfo;
    flie_findinfo = fopen("findinfo.txt","a");
    fprintf(flie_findinfo,"%d %s %s %s %s %s %s %d\n",
    fp.fid,fp.name,fp.description,fp.contact_details,
    fp.submit_user_schoolId,fp.submit_user,fp.submit_time,fp.status);
    fclose(flie_findinfo);
    return OK;
}


Status operate_get_lostinfo_all(LostNode *head) {
    LostNode *p = head;
    FILE *flie_lostinfo;
    flie_lostinfo = fopen("lostinfo.txt","r");
    while(1) {
        fscanf(flie_lostinfo,"%d %s %s %s %s %s %s %d\n",
        &p->lp.lid,p->lp.name,p->lp.description,
        p->lp.contact_details,p->lp.submit_user_schoolId,
        p->lp.submit_user,p->lp.submit_time,&p->lp.status);
        if (!feof(flie_lostinfo))
        {
            p -> next = new_LostNode();
            p = p -> next;
        } else {
            break;
        }
        
    }
    fclose(flie_lostinfo);
    return OK;
}

Status operate_insert_receiverinfo_lost(char *login_schoolId,int lid) {
    FILE *fp;
    fp=fopen("receiveinfo.txt","a");
    char time[50];
    getTime(time);
    fprintf(fp,"1 %d %s %s\n",lid,login_schoolId,time);
    fclose(fp); 
    return OK;
}

Status operate_update_lostinfo_all(LostNode *head) {
    LostNode *p = head,*q;
    FILE *flie_lostinfo;
    //删除并新建文件
    flie_lostinfo = fopen("lostinfo.txt","w");
    fclose(flie_lostinfo);
    flie_lostinfo = fopen("lostinfo.txt","a");
    while (p != NULL) {
        fprintf(flie_lostinfo,"%d %s %s %s %s %s %s %d\n",
        p->lp.lid,p->lp.name,p->lp.description,p->lp.contact_details,
        p->lp.submit_user_schoolId,p->lp.submit_user,p->lp.submit_time,p->lp.status);
        q = p;
        p = p->next;
        free(q);
        q = NULL;
    }
    fclose(flie_lostinfo);
}
//传入lid将状态改为1，并写入文件//lid是失物信息的唯一标识 
Status operate_update_lostinfo_byId_status_to_1(int lid) {
    //创建一个用来存所有lostinfo的链表头
    LostNode *head = new_LostNode();//该函数得到一个链表头 
    //传入链表头，获得完整信息
    operate_get_lostinfo_all(head);//将文件中的数据读入链表 
    //这是链表的遍历方式
    LostNode *p = head;
    while (p != NULL) 
	{
        if (lid == p->lp.lid) 
		{
            p->lp.status = 1;//更改对应lid的状态为1 
            break;
        }
        p = p->next;//遍历完一个则p指向下一个结构体 
    }
    operate_update_lostinfo_all(head);// 用fprintf函数把修改后的数据全部重新写入文件 
    return OK;
}

Status operate_update_lostinfo_byId_status_to_2(int lid) {
    //创建一个用来存所有lostinfo的链表头
    LostNode *head = new_LostNode();//该函数得到一个链表头 
    //传入链表头，获得完整信息
    operate_get_lostinfo_all(head);//将文件中的数据读入链表 
    //这是链表的遍历方式
    LostNode *p = head;
    while (p != NULL) 
	{
        if (lid == p->lp.lid) 
		{
            p->lp.status = 2;//更改对应lid的状态为1 
            break;
        }
        p = p->next;//遍历完一个则p指向下一个结构体 
    }
    operate_update_lostinfo_all(head);// 用fprintf函数把修改后的数据全部重新写入文件 
    return OK;
}

Status operate_update_findinfo_byId_status_to_2(int lid) {
    //创建一个用来存所有lostinfo的链表头
    FindNode *head = new_FindNode();//该函数得到一个链表头 
    //传入链表头，获得完整信息
    operate_get_findinfo_all(head);//将文件中的数据读入链表 
    //这是链表的遍历方式
    FindNode *p = head;
    while (p != NULL) 
	{
        if (lid == p->fp.fid) 
		{
            p->fp.status = 2;//更改对应lid的状态为1 
            break;
        }
        p = p->next;//遍历完一个则p指向下一个结构体 
    }
    operate_update_findinfo_all(head);// 用fprintf函数把修改后的数据全部重新写入文件 
    return OK;
}

Status operate_get_findinfo_all(FindNode *head) {
    FindNode *p = head;
    FILE *flie_findinfo;
    flie_findinfo = fopen("findinfo.txt","r");
    while(1) {
        fscanf(flie_findinfo,"%d %s %s %s %s %s %s %d\n",
        &p->fp.fid,p->fp.name,p->fp.description,
        p->fp.contact_details,p->fp.submit_user_schoolId,
        p->fp.submit_user,p->fp.submit_time,&p->fp.status);
        if (!feof(flie_findinfo))
        {
            p -> next = new_FindNode();
            p = p -> next;
        } else {
            break;
        }
        
    }
    fclose(flie_findinfo);
    return OK;
}


Status operate_update_findinfo_all(FindNode *head) {
    FindNode *p = head,*q;
    FILE *flie_findinfo;
    //删除并新建文件
    flie_findinfo = fopen("findinfo.txt","w");
    fclose(flie_findinfo);
    flie_findinfo = fopen("findinfo.txt","a");
    while (p != NULL) {
        fprintf(flie_findinfo,"%d %s %s %s %s %s %s %d\n",
        p->fp.fid,p->fp.name,p->fp.description,p->fp.contact_details,
        p->fp.submit_user_schoolId,p->fp.submit_user,p->fp.submit_time,p->fp.status);
        q = p;
        p = p->next;
        free(q);
        q = NULL;
    }
    fclose(flie_findinfo);
}

