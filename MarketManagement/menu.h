#include "code.h"
#include "stdafx.h"

int memu()  //��Ŀ¼ 
{
	
	int a;     //���Լ�¼�û�����Ŀ¼�ľ��� 
	
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
	
	printf("\n\n\t\t*************************************************\t\t\n") ;
    printf("\t\t*\t\t���й���ϵͳ\t\t\t*\t\n");
	printf("\t\t*1������Ա��¼\t\t\t\t\t*\n");
	printf("\t\t*2���ϰ��¼\t\t\t\t\t*\n");
	printf("\t\t*3���˿͵�¼\t\t\t\t\t*\n");
	printf("\t\t*4���˳�ϵͳ\t\t\t\t\t*\n");
	printf("\t\t*************************************************\t\t\n") ;
	printf("����������ѡ��");
	scanf("%d",&a);
	return a;
}
int goodmemu()    //��Ʒ��Ϣ����Ŀ¼ 
{
	int a;        //���������¼�û�����Ʒ�����ϵ�ѡ�� 
	
		
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
	
	
	printf("\n\n\n\n\n\t\t*************************************************\t\t\n") ;
    printf("\t\t*\t\t��Ʒ����ϵͳ(����Ա)\t\t*\n");
	printf("\t\t*1����Ʒ��Ϣ¼��\t\t\t\t*\n");
	printf("\t\t*2��������Ʒ���\t\t\t\t*\n");
	printf("\t\t*3����Ʒ��Ϣ��ѯ\t\t\t\t*\n");
	printf("\t\t*4����Ʒ��Ϣ�޸�\t\t\t\t*\n");
	printf("\t\t*5����Ʒ��Ϣɾ��\t\t\t\t*\n");
	printf("\t\t*6�������Żݴ����\t\t\t\t*\n");	
	printf("\t\t*7����Ʒ��Ϣչʾ\t\t\t\t*\n"); 
	printf("\t\t*8����Ʒ��Ϣͳ��\t\t\t\t*\n");
	printf("\t\t*9����Ʒ��Ϣ�������ļ�\t\t\t\t*\n"); 
	printf("\t\t*10���ļ��е�����Ʒ��Ϣ\t\t\t\t*\n");
	printf("\t\t*11���˳�\t\t\t\t\t*\n");
	printf("\t\t*************************************************\t\t\n") ;
	printf("���������ѡ��");
	scanf("%d",&a);
	return a;
} 
int shopmemu(double level)  //������Ϣ����Ŀ¼ 
{
	int a;     //����һ��������¼�û��ڵ�����Ϣ�����ϵľ��� 
		
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
	if(level <= 100)
		printf("\n\t\t     ��ͭ��Ա����,��ӭ���ĵ�¼");
	if(level <= 500 && level >100)
		printf("\n\t\t     ������Ա����,��ӭ���ĵ�¼,��������0.98���Ż�");
	if(level <= 1000 && level >500)
		printf("\n\t\t     �ƽ��Ա����,��ӭ���ĵ�¼,��������0.95���Ż�");
	if(level > 1000)
		printf("\n\t\t     �����Ա����,��ӭ���ĵ�¼,��������0.9���Ż�");	
	
	
	printf("\n\n\n\t\t*************************************************\t\t\n") ;
    printf("\t\t*\t\t�������(�˿�)\t\t\t*\t\n");   
	printf("\t\t*1����ѯ��Ʒ\t\t\t\t\t*\n");
	printf("\t\t*2��������Ʒ\t\t\t\t\t*\n");
	printf("\t\t*3���˻���Ʒ\t\t\t\t\t*\n");
	printf("\t\t*4���鿴�����\t\t\t\t*\n");
	printf("\t\t*5���鿴������ʷ��¼\t\t\t\t*\n"); 
	printf("\t\t*6��Ϊ��Ʒ׫д����\t\t\t\t*\n"); 
	printf("\t\t*7��Ͷ�߹���Ա������Ա\t\t\t\t*\n");
	printf("\t\t*8��Ϊ�����ṩ����\t\t\t\t*\n"); 
	printf("\t\t*9��ͳ��������Ϣ\t\t\t\t*\n"); 
	printf("\t\t*10���˳�\t\t\t\t\t*\n");
	printf("\t\t*************************************************\t\t\n") ;
	printf("���������ѡ��");
	scanf("%d",&a);
	return a;
}
int staffmemu()  //Ա����Ϣ����Ŀ¼ 
{
	int a;       //����һ��������¼�û���Ա����Ϣ�����ϵľ��� 
		
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
    printf("\t\t*\t\tԱ������ϵͳ(�ϰ�)\t\t*\t\n");
	printf("\t\t*1�������Ա��\t\t\t\t\t*\n");
	printf("\t\t*2������Ա��\t\t\t\t\t*\n");
	printf("\t\t*3����ʾ����Ա��\t\t\t\t*\n");
	printf("\t\t*4����Ʒ��Ϣչʾ\t\t\t\t*\n");
	printf("\t\t*5����Ʒ��Ϣͳ��\t\t\t\t*\n");
	printf("\t\t*6���鿴Ͷ����Ϣ\t\t\t\t*\n");
	printf("\t\t*7���鿴�˿ͽ���\t\t\t\t*\n");
	printf("\t\t*8���˳��ϰ����\t\t\t\t*\n");
	printf("\t\t*************************************************\t\t\n") ;
	printf("���������ѡ��");
	scanf("%d",&a);
	return a;
}

int codeMenu(int flag)
{	
	struct user our_users[N];		//	�ṹ�崢���˻���Ϣ 
	
	int count = 0;					//	�˻����� 
	int current_user;				//	��ǰ�˻� 



	FILE* fp = fopen("account_system.dat","r");
	char buffer[8];
    fread(&buffer, sizeof(buffer), 1, fp);
	int val = atoi(buffer);
	fclose(fp);
    count = val-10000 + 1;			// ��ȡ��ע��ɹ����˻��� 
    

	switch(show_menu(flag))
	{
	case 1:
		if(user_register(our_users,count))
		{
			count++;
			printf("\nע��ɹ�!");
			system("pause") ;
			system("CLS");
		}
		break;
//ע��
	case 2:
		if((current_user = is_my_user(our_users,count)))
		{
			printf("\n��½�ɹ�!");
			display_user(our_users[current_user - 1]);
			return 1; 
		}
		else
		{
			system("CLS");
			printf("\n��½ʧ��!");
		}
		break;
//��½
	case 3:
		update_password(our_users,count);
		break;
//�޸�����
	case 4:
		return -1;
		break;
//�˳�
	default:
		printf("����ȷ����");
	}
}
	
