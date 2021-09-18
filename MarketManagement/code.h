#pragma once


#include "stdafx.h"
#define N 100
struct user
{
int user_id;
char user_name[19];		// ���18λ
char password[13];		// ���13λ
char like[255];
char sign[255];
};

/*
* ��֤�û��������Ƿ�Ϸ�
*/
int length_user_name(char *p)
{
int l;
l=strlen(p);
if(l>18||l<1)
{
return 0;
}
else
return l;
}

/*
* �ж��û����Ƿ���Чzhi
*/
int valid_user_name(char *p)
{
int i=0;
int len = strlen(p);
if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <='Z')) //�ж����ַ��ǲ�����ĸ
{
for(i = 0; i < len; i++)
{
if(!(p[i] == '_' || (p[i] >= 'a' && p[i] <= 'z') || (p[i] >= 'A' && p[i] <='Z')
||(p[i] >='0' && p[i] <= '9'))) //�жϺ����ַ��Ƿ���Ч
return 0;

}
return 1;
}
else
return 0;

}

/*
* �ж��û����Ƿ���Ч
*/
int is_username_valid(char *p)
{
if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <='Z'))
{
p++;
while(*p)
{
if(!(isalpha(*p) || *p == '_' || isdigit(*p)))
return 0;
p++;
}

return 1;
}
else
{
return 0;
}
}

/*
* ���볤����Ч����֤
*/
int length_password(char *p)
{
int len;
len = strlen(p);
if(len<6||len>12)
{
return 0;
}
else
return len;
}

/*
* �������Ч����֤
*/
int is_password_valid(char *p)
{
int i=0;

for(;*p != '\0'; p++)
{
if(!( (*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <='Z')
||(*p >='0' && *p <= '9'))) //�ж��ַ��Ƿ���Ч
return 0;
}
return 1;
}

int two_password_valid(char *p1,char*p2)
{
if(strcmp(p1,p2)==0)
return 1;
else
return 0;
}



/*
* ���ע�Ṧ��
*/
int user_register(struct user *ptr_user,int size)
{
	FILE* fp = NULL;
	
	fp = fopen("account.dat","a");										// account.txt �����û����� 
	
char password[13];
char repassword[13];
if(size==N)
{
puts("ע����������!");
return 0;
}
printf("������ע������:");
fflush(stdin);
gets(ptr_user[size].user_name);
if(!(length_user_name(ptr_user[size].user_name)&&valid_user_name(ptr_user[size].user_name)))
{
		system("CLS");
printf("�������������Ч,�û�����1-18֮��,���ַ�Ϊ��ĸ,�������Ϊ��ĸ,���ֻ��»���!!!");
return 0;
}


printf("������ע������:");
fflush(stdin);
gets(password);
printf("���ٴ�����ע������:");
fflush(stdin);
gets(repassword);
if(!two_password_valid(password,repassword))
{
		system("CLS");
printf("\n������������벻һ��!");
return 0;
}
else
{
strcpy(ptr_user[size].password,password);
}

if(!(length_password(ptr_user[size].password)&&is_password_valid(ptr_user[size].password)))
{
		system("CLS");
printf("�������������Ч,����Ӧ��6-12֮��,����ֻ�ܰ�����ĸ������!!!");
return 0;
}

printf("���������İ���:");
fflush(stdin);
gets(ptr_user[size].like);
printf("���������ĸ���ǩ��:");
fflush(stdin);
gets(ptr_user[size].sign);
ptr_user[size].user_id=10000+size;
printf("���ı��Ϊ:%d,�⽫�����ĵ�½�ʺ�.",ptr_user[size].user_id);

	fwrite(&ptr_user[size],sizeof(struct user),1,fp);								// д�� 
	fclose(fp);
	

	fp = fopen("account_system.dat","w");
	char buffer[8];
	sprintf(buffer,"%d",ptr_user[size].user_id);
	fwrite(&buffer,sizeof(buffer),1,fp);

	fclose(fp);
	fp = NULL;
	
	
return 1;
}

/*
* �����½�ɹ��򷵻ص�i+1���û�����Ϣ,���򷵻�0
*/
int is_my_user(struct user *p,int size)
{
	FILE* fp = NULL;

	
	fp = fopen("account.dat","r");
	
	int temp = 0;
	 for(; temp<N; temp++)
    {
    	fread(&p[temp], sizeof(struct user), 1, fp);

    }
    fclose(fp);
    fp = NULL;

	
int i;
int zhanghu;
char mima[15];
printf("�����������ʺ�: ");
scanf("%d",&zhanghu);
fflush(stdin);
printf("��������������: ");
gets(mima);
for(i=0;i<N;i++)
{
if((zhanghu == p[i].user_id)&&(strcmp(mima,p[i].password) == 0))
{
	consumer_id = zhanghu;
return i + 1;
}
}
return 0;
}

void display_user(struct user u)
{
printf("\n����ʺ���:%d",u.user_id);
printf("\n��ע��������:%s",u.user_name);
printf("\n��İ���:%s",u.like);
printf("\n��ĸ���ǩ��:%s",u.sign);
}

void update_password(struct user *ptr_user,int size)
{
	FILE* fp = NULL;

	
	fp = fopen("account.dat","r");
	int temp = 0;
	 for(; temp<N; temp++)
    {
    	fread(&ptr_user[temp], sizeof(struct user), 1, fp);
    }
    fclose(fp);
    fp = NULL;

char mima1[13],mima2[13];
int i = is_my_user(ptr_user,size);
if(i)
{
i--;
}
else
{
	system("CLS");
printf("\n�ʺ����벻����!");
return;
}

printf("������������: ");
scanf("%s",mima1);
printf("���ٴ�����������: ");
scanf("%s",mima2);

if(two_password_valid(mima1,mima2) && length_password(mima1) && is_password_valid(mima1))
{
strcpy(ptr_user[i].password,mima1);//����¾�����ĵ���
	system("CLS");
printf("\n���ĵ������޸ĳɹ�!");
}
else
{
	system("CLS");
printf("���������޸�ʧ��!");
	
}



	temp = 0;

	

	fp = fopen("account.dat","w");
	 for(; temp<size; temp++)
    {
    	fwrite(&ptr_user[temp], sizeof(struct user), 1, fp);
    }
    fclose(fp);
    fp = NULL;

}

//��ʾ�˵�
int show_menu(int flag)
{
	int choice;
	
	
	time_t t;
	struct tm *lt;
	time(&t);
	lt = localtime(&t);
	
	printf("\n\t\t   ��ǰϵͳʱ�䣺%d��%d��%d��,",lt->tm_year + 1900,lt->tm_mon,lt->tm_mday);
	switch(lt->tm_wday)
	{
		case 0:
			printf("������");
			break; 
		case 1:
			printf("����һ");
			break; 
		case 2:
			printf("���ڶ�");
			break; 
		case 3:
			printf("������");
			break; 
		case 4:
			printf("������");
			break; 
		case 5:
			printf("������");
			break; 
		case 6:
			printf("������");
			break; 
	}
	printf(",%dʱ%d��%d��\n",lt->tm_hour ,lt->tm_min ,lt->tm_sec );
	
	
	printf("\n\n\n\n\t\t*************************************************\t\t\n") ;
	if(flag == 1)
		printf("\t\t*\t\t���й���ϵͳ(����Ա)\t\t*\t\n");
	if(flag == 2)
	    printf("\t\t*\t\t���й���ϵͳ(�ϰ�)\t\t*\t\n");
	if(flag == 3) 
	    printf("\t\t*\t\t���й���ϵͳ(�˿�)\t\t*\t\n");
	printf("\t\t*1��ע��\t\t\t\t\t*\n");
	printf("\t\t*2����¼\t\t\t\t\t*\n");
	printf("\t\t*3���޸�����\t\t\t\t\t*\n");
	printf("\t\t*4���˳�\t\t\t\t\t*\n");
	printf("\t\t*************************************************\t\t\n") ;
	printf("����������ѡ��");

	scanf("%d",&choice);

	return choice;
}



