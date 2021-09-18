#pragma once
#include "stdafx.h"
struct staff  //Ա���ṹ�� 
{
	int number;  //Ա����� 
	char name[20]; //Ա������ 
	char origin[20];    //Ա��Դ���̱�� 
	double grade;   //Ա��ҵ���������۽���KΪ��λ��
	int  count;    //Ա����������  
	struct staff *next; 
}; 


void read_Complain()
{
	struct complain *com;
	FILE * fp = NULL;
	char *path = ".\\Complain\\*.txt";
	char fileName[100];
	
	long handle;
	struct _finddata_t fileinfo;
	
	handle = _findfirst(path,&fileinfo);
	if(handle == -1)
	{
		printf("������Ͷ����Ϣ\n"); 
		return;
	}
	
	
	sprintf(fileName,".\\Complain\\%s",fileinfo.name);
	fp = fopen(fileName,"r");
	com=(struct complain *)malloc(sizeof(struct complain));
	fread(com,sizeof(struct complain),1,fp);

	printf("��ȡͶ����Ϣ�ļ��ɹ�\n");
	
	printf("��Ͷ�ߵ�Ա�����Ϊ: %d\n",com->number );
	printf("Ͷ������Ϊ��%s\n",com->str );
	fclose(fp);
	
	while(!_findnext(handle,&fileinfo))
	{
		sprintf(fileName,".\\Complain\\%s",fileinfo.name);
		fp = fopen(fileName,"r");
		memset(com,0,sizeof(struct complain));
		
		fread(com,sizeof(struct complain),1,fp);
		printf("��Ͷ�ߵ�Ա�����Ϊ: %d\n",com->number );
		printf("Ͷ������Ϊ��%s\n",com->str );
		fclose(fp);
	}
}

void read_Suggestion()
{
	FILE * fp = NULL;
	char *path = ".\\Suggestion\\*.txt";
	char fileName[100];
	char buffer[512];
	
	memset(fileName,0,sizeof(fileName));
	long handle;
	struct _finddata_t fileinfo;
	
	handle = _findfirst(path,&fileinfo);
	if(handle == -1)
	{
		printf("�����޹˿ͽ�����Ϣ\n"); 
		return;
	}
	
	sprintf(fileName,".\\suggestion\\%s",fileinfo.name);
	fp = fopen(fileName,"r");
	fread(buffer,sizeof(buffer),1,fp);
	printf("�˿ͽ�������Ϊ��%s\n",buffer);
	fclose(fp);
	
	while(!_findnext(handle,&fileinfo))
	{
		sprintf(fileName,".\\suggestion\\%s",fileinfo.name);
		fp = fopen(fileName,"r");
		memset(buffer,0,sizeof(buffer));
		fread(buffer,sizeof(buffer),1,fp);
		printf("�˿ͽ�������Ϊ��%s\n",buffer);
		fclose(fp);
	}

	
} 






struct staff * Add_staff(struct staff *staffhead)   //����Ա������Ϣ 
{
	int a;
	char c;
	printf("������������Ա����Ϣ��(Y/N)��");
    scanf(" %c",&c);
	for(a=0;c=='Y'||c=='y';a++)
	{
		struct staff *p=NULL;
	    struct staff *q=staffhead;
	    p=(struct staff *)malloc(STAFF);  //����ռ� 
		if(!p)
	    {
	    	printf("¼��ʧ�ܣ�\n");
		    return staffhead;
	    }
	    p->next=NULL;
	    printf("�������Ա�����й���Ϣ\n");
    	printf("���������Ա���ı�ţ�");
	    scanf("%d",&p->number) ;
	    printf("���������Ա�������֣�");
	    scanf("%s",p->name) ;
	    printf("���������Ա����Դ�ĵ��̣�");
	    scanf("%s",p->origin) ;
	    printf("���������Ա�������۽�"); 
	    scanf("%lf",&p->grade) ;
	    printf("���������Ա��������������");
		scanf("%d",&p->count);
	    if(!staffhead)
	    {
		    staffhead=p;
      	}   
	    else
	    {
		  for(;q->next;q=q->next);
		  q->next=p;
	    }
		printf("���������������Ա����Ϣ��(Y/N)");
		scanf(" %c",&c); 
	}  
	printf("%d ��Ա������Ϣ�Ѿ�¼���\n",a); 
	return staffhead;
}
void benefit_sum(struct staff *head) //���Ա�������������ܺ��Լ����۽���ܺ� 
{
	int sale_number=0;  //���������ܺ� 
	double a=0;         //���۽���ܺ� 
	struct staff *p=NULL;
	for(p=head;p;p=p->next)
	{
		a+=p->grade;
		sale_number+=p->count;
	}
	printf("��ͳ���Ժ��֪��\n");     //��ʱ�����û�ͳ����� 
	printf("1��Ա�����������ܺ�Ϊ��%d\n",sale_number);
	printf("2��Ա�����۽���ܺ�Ϊ��%g\n",a);                                    
}
void showstaff(struct staff * staffhead)  //չʾԱ������Ϣ 
{
	if(!staffhead)    //������û�п��������Ա����Ϣ 
	{
		printf("û�п������Ա����Ϣ��");
		return ; 
	}
	struct staff *p=NULL;
	printf("Ա�����  Ա������  Դ����  ���۽��  ��������\n");
	for(p=staffhead;p;p=p->next)
	{
	   printf("%6d   %9s  %6s  %8g  %8d\n",p->number,p->name,p->origin,p->grade,p->count);
	}
}
void search_staff(struct staff *staffhead)  //Ѱ��ָ��Ա������Ϣ 
{
	if(!staffhead)     //����������Ϣ�Բ�ѯ 
	{
		printf("û��Ա����Ϣ�ɹ���ѯ!");
		return  ;
	}
	char c;
    int a;
    struct staff *p=NULL;
	printf("�������Ƿ���Ҫ��ѯԱ����Ϣ��(Y/y)");
	scanf(" %c",&c);
	for(;c=='y'||c=='Y';)
    {
	   printf("�������Ա���ı�ţ�");
	   scanf("%d",&a); 
	   for(p=staffhead;p;p=p->next)     //���ݱ��Ѱ��ָ��Ա�� 
	   { 
	      if(a==p->number)
	     {
	       printf("����ѯ��Ա����Ϣ���£�\n");
		   printf("Ա�����  Ա������  Դ����  ���۽��  ��������\n");
		   printf("%6d   %9s  %6s  %8g  %8d\n",p->number,p->name,p->origin,p->grade,p->count);	
		   break; 
	     } 
	   }
	   if(p==NULL)  printf("û���ҵ���Ա���������Ϣ��\n"); 
	   printf("�������Ƿ���Ҫ������ѯԱ����Ϣ��(Y/y)");
	   scanf(" %c",&c);
	}
}
void sort_staff(struct staff *head)  //��Ա����Ϣ���в�������(�������۽��) 
{
	struct staff *a=NULL,*t=NULL;
	struct staff *p=NULL,*q=NULL;
    a=head->next;
	head->next=NULL;
	while(a!=NULL)
	{
		for(t=a,q=head;q&&(q->grade<t->grade);p=q,q=q->next);
		a=a->next;
		if(q==head)
		{
			head=t;
		}
		else
		{
			p->next=t;
		}
		t->next=q;
	} 
	showstaff(head);
}
struct staff *Delete_staff (struct staff * head)  //ɾ��ָ��Ա������Ϣ 
{
	if(!head)      //����������Ϣ��ɾ�� 
	{
		printf("��Ǹ����û�п���ɾ����Ա����Ϣ\n");
		return head;
    }
	char c;
	int a,b;
	printf("��������ɾ��Ա����Ϣ�𣿣�Y/N��");
	scanf(" %c",&c);
    for(b=0;c=='Y'||c=='y';b++)
	{ 
		struct staff *p=NULL;
	    struct staff *q=NULL;
	    printf("������������ɾ����Ա���ı��:");    //���ݱ��ɾ��ָ��Ա������Ϣ 
	    scanf("%d",&a);                             //Ѱ��ָ��Ա���������е�λ�� 
	    for(p=head;p;q=p,p=p->next)   
	    {
	    	if(a==p->number)
	        {
	         	if(q!=NULL) q->next=p->next;
	            else        head=p->next;
		        free(p);    //�ͷŸÿռ� 
		        printf("��Ա����Ϣɾ���ɹ���\n");
		        break;
	        }  
		}
	    if(p==NULL)         //û���ҵ�ָ��Ա�� 
	    {
		    printf("û���ҵ�������ɾ����Ա��\n"); 
	        b--;
	    }
	    printf("�������������ɾ��Ա����Ϣ�𣿣�Y/N��");
	    scanf(" %c",&c);
	}
	printf("%d��Ա������Ϣ�Ѿ�ɾ���ɹ�\n",b);   //��ʱ����ɾ����� 
	return head;
}
struct staff  *modify_staff(struct staff *head)  //�޸�ָ��Ա������Ϣ 
{
	if(!head)    //�������޿��޸ĵ�Ա����Ϣ 
	{
		printf("û��Ա������Ϣ�ɹ��޸�");
		return head;
	}
	int a,b;
	char c;
	printf("���������޸�Ա����Ϣ��(Y/N)��"); 
	scanf(" %c",&c);
	for(a=0;c=='Y'||c=='y';a++)
	{
	   struct staff *p=NULL;
	   printf("�������Ա���ı�ţ�");    //����Ա������ҵ�Ա������Ϣ�����޸� 
	   scanf("%d",&b);
	   for(p=head;p;p=p->next)
       {
	   	if(b==p->number) 
	    {
	     printf("������Ա���µ���Ϣ\n");    //����ȥ¼��Ա������Ϣ 
	     printf("���������Ա���ı�ţ�");
	     scanf("%d",&p->number) ;
	     printf("���������Ա�������֣�");
	     scanf(" %s",p->name) ;
	     printf("���������Ա����Դ�ĵ��̣�");
	     scanf("%s",p->origin) ;
	     printf("���������Ա�������۽�"); 
	     scanf("%lf",&p->grade) ;
	     printf("���������Ա��������������");
		 scanf("%d",&p->count); 
		 break;
	    }
	   } 
	   if(p==NULL) //û���ҵ�Ҫ�޸ĵ�Ա�� 
	   {
		 printf("δ��ѯ���������޸ĵ�Ա�����������Ƿ�������ȷ��\n");
		 a--;
		}  
	    printf("������������޸�Ա����Ϣ��(Y/N)");
	    scanf(" %c",&c);
	} 
	printf("%d��Ա������Ϣ�Ѿ��޸ĳɹ���\n",a);  //��ʱ����Ա����Ϣ 
	return head; 
}
void storage_staff(struct staff  * head) //����Ա����Ϣ 
{
	if(!head) 
	{
		printf("û��Ա����Ϣ�ɹ�����\n");
		return ;
	}
	struct staff  *p=NULL;
	FILE *fp;
	if((fp=fopen(".\\Staff\\staff.txt","wb"))==NULL)
	{
		printf("���ܴ�Ա����Ϣ�ļ�\n");
		return ;
	}
	for(p=head;p;p=p->next)
	{
		fwrite(p,STAFF,1,fp);
	}
	fclose(fp);
	printf("����Ա����Ϣ�ѳɹ������ļ���\n");
}
struct staff  * open_staff(struct staff  *head)
{
	FILE *fp;
	struct staff  *p,*q;
	if((fp=fopen(".\\Staff\\staff.txt","rb"))==NULL)
	{
		printf("�򲻿�Ա����Ϣ�ļ���\n");
		return head;
	}
    p=(struct staff *)malloc(STAFF);
	head=p;
	q=head;
	while(!feof(fp))
	{
		if(fread(p,STAFF,1,fp)!=1) break;
	    p->next=(struct staff  *)malloc(STAFF);
        q=p->next;
        q=p;
        p=p->next;
	}
	q->next=NULL;
	fclose(fp);
	printf("��ȡԱ����Ϣ�ļ��ɹ�\n");
	return head;
}
