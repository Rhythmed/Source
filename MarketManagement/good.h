#include "stdafx.h"
struct Good    							// ��Ʒ�ṹ�� 
{  
	int number;  						// ��Ʒ��� 
    char name[10];						// ��Ʒ���� 
    double cost; 						// ��Ʒ�Ľ��� 
    double price;						// ��Ʒ���ۼ�
    int   sale_number;					// ��Ʒ�Ŀ�� 
    char pd[15];						// ��Ʒ����������
	char exd[15];						// ��Ʒ����Ч�������� 
	double bargain;						// �Ƿ�����Żݴ���� 
    struct Good *next; 
};


struct Good * Increase_good (struct Good * head) //������Ʒ����Ϣ 
{
	int a; 
	char c;
	printf("�������Ƿ���Ҫ¼����Ʒ��Ϣ����Y/N��");
	scanf(" %c",&c);
	for(a=0;c=='Y'||c=='y';a++)
	{
		struct Good *p=NULL;
	    struct Good *q=NULL;
		p=(struct Good *)malloc(GOOD);
		if(!p)       //������ʧ��Ӧ���˳� 
		{
			printf("¼����Ϣʧ��\n");
		    return head;
		}
		p->next=NULL;
		printf("���������Ʒ�������Ϣ\n");
		printf("����������Ʒ��ţ�");
	    scanf("%d",&p->number) ;
		fflush(stdin); 
		
	    printf("����������Ʒ���ƣ�");
	    scanf("%s",p->name);
		fflush(stdin); 
	
	    printf("����������Ʒ���ۣ�");
     	scanf("%lf",&p->cost);
     	fflush(stdin);
     	
    	printf("����������Ʒ�ۼۣ�");
	    scanf("%lf",&p->price);
	    fflush(stdin);
	    
	    printf("����������Ʒ������");
		scanf("%d",&p->sale_number);
		fflush(stdin);
		
		printf("����������Ʒ����������(��2020-01-01)��");
		scanf("%s",p->pd);
		fflush(stdin);
		
		printf("����������Ʒ����Ч����(��2020-01-01)��");
		scanf("%s",p->exd);
		fflush(stdin);
		
		p->bargain = 0.0f; 
		
		if(!head)
		{
			head=p;
		}
		else
		{
			for(q=head;q->next;q=q->next);
			q->next=p;
		} 
	   	printf("�������Ƿ���Ҫ����¼����Ʒ��Ϣ�أ���Y/N��");
	    scanf(" %c",&c);
	}
	printf("%d����Ʒ����Ϣ�Ѿ�¼��ɹ���\n",a);  //�������û���Ϣ�洢��� 
	return head;
}
void Show_Good(struct Good *head)   //��ʾ��������Ʒ����Ϣ 
{
	if(!head)  //���������ڿ����������Ʒ��Ϣ 
	{
		printf("û�пɹ��������Ʒ��Ϣ��");
		return ; 
	}
    struct Good *p=NULL;
    printf("  ��Ʒ���  ��Ʒ����  ��Ʒ����  ��Ʒ�ۼ�  �Ƿ��Żݴ���  ��Ʒ���      ��������      ��������\n");
    for(p=head;p;p=p->next) //���������ע���ʽ 
    {
       printf("%8d  %10s  %6g  %6g    %6g        %6d  %15s  %15s\n",p->number,p->name,p->cost,p->price,p->bargain ,p->sale_number,p->pd,p->exd);
	}
}
void searchGood(struct Good *head)  //��ѯ��Ʒ��Ϣ�Ĺ��ܺ��� 
{
	if(!head)  //�������޿ɲ�ѯ����Ʒ��Ϣ 
	{
		printf("û����Ʒ��Ϣ�ɹ���ѯ");
		
		return ;
	}
	char c;
	int a;
	struct Good *p=NULL;
	printf("�������Ƿ���Ҫ��ѯ��Ʒ��Ϣ����Y/N��");
	scanf(" %c",&c);      
	for(;c=='Y'||c=='y';)
	{
	    printf("�����������ѯ����Ʒ�ı��:");       //���ݱ���ҵ�ָ����Ʒ 
	    scanf("%d",&a);
		for(p=head;p;p=p->next)
		{
			if(a==p->number)
	        {
			 printf("����Ʒ��Ϣ���£�\n");
	         printf("  ��Ʒ���  ��Ʒ����  ��Ʒ����  ��Ʒ�ۼ�  �Ƿ��Żݴ���  ��Ʒ���        ��������        ��������\n");
		     printf("%8d  %10s  %6g  %6g    %6g        %6d  %15s  %15s\n",p->number,p->name,p->cost,p->price,p->bargain ,p->sale_number,p->pd,p->exd);
			 break;	
	        }
		} 
	    if(p==NULL) printf("û���ҵ�����Ʒ����Ϣ\n");     //δ�ҵ�ָ������Ʒ��Ϣ�������䲢������ 
		printf("�������������ѯ�𣿣�Y/N��");
		scanf(" %c",&c); 
	}
}
struct Good* Deletegood(struct Good *head)  //ɾ��ָ����Ʒ����Ϣ 
{
	if(!head)    //�������޿�ɾ������Ʒ��Ϣ 
	{
		printf("��Ǹ,û�пɹ�ɾ������Ʒ��Ϣ\n");
		return head;
	}
	int a,b;
	char c;
	printf("��������ɾ����Ʒ��Ϣ�𣿣�Y/N��");
	scanf(" %c",&c);
	for(a=0;c=='Y'||c=='y';a++)
	{
	   struct Good *p=NULL;
	   struct Good *q=NULL;
	   printf("������������ɾ������Ʒ�ı��:");    //������Ʒ����ҵ���Ҫɾ������Ʒ 
	   scanf("%d",&b);
	    for(p=head;p;q=p,p=p->next)
	    {
	   	    if(b==p->number)
	        {
	         	if(q!=NULL) q->next=p->next;
	            else        head=p->next;
		        free(p);    //�ͷŸÿռ� 
		        printf("����Ʒ����Ϣɾ���ɹ���\n");
		        break;
	        } 
	    }  
	    if(p==NULL)                //δ�ҵ�ָ����Ʒ�������䲻�����޷�ɾ�� 
	    {
		 printf("û���ҵ�������ɾ������Ʒ\n"); 
		 a--;
	    }
	    printf("�������������ɾ����Ʒ��Ϣ�𣿣�Y/N��");
	    scanf(" %c",&c);
	}	
	printf("%d����Ʒ����Ϣ�Ѿ�ɾ���ɹ���\n",a);   //��ʱ�������û�ɾ�����
	return head;
}
struct Good * modifygood(struct Good *head)  //�޸���Ʒ����Ϣ 
{
	if(!head)           //�������޿������޸ĵ���Ʒ��Ϣ 
	{
		printf("û����Ʒ��Ϣ�ɹ��޸�\n");
		return head; 
	}
	char c;
	printf("���������޸���Ʒ��Ϣ��(Y/N)��");
	scanf(" %c",&c);
	int a,b;
	for(b=0;c=='Y'||c=='y';b++)
	{
	    struct Good *p=NULL;
		printf("���������Ʒ�ı�ţ�");
		scanf("%d",&a);
	    for(p=head;p;p=p->next) //�ҵ�ָ����Ʒ��λ�� 
	    {
	    	if(a==p->number)   
	        {
	         	printf("��������Ʒ������Ϣ\n");      //����Ʒ���е���Ϣ���������� 
	        	printf("����������Ʒ��ţ�");
	   	 		scanf("%d",&p->number) ;
				fflush(stdin); 
		
	    		printf("����������Ʒ���ƣ�");
	    		scanf("%s",p->name);
				fflush(stdin); 
		

	    		printf("����������Ʒ���ۣ�");
     			scanf("%lf",&p->cost);
     			fflush(stdin);
     	
    			printf("����������Ʒ�ۼۣ�");
	    		scanf("%lf",&p->price);
	    		fflush(stdin);
	    
	    		printf("����������Ʒ������");
				scanf("%d",&p->sale_number);
				fflush(stdin);
		
				printf("����������Ʒ����������(��2020-01-01)��");
				scanf("%s",p->pd);
				fflush(stdin);
		
				printf("����������Ʒ����Ч����(��2020-01-01)��");
				scanf("%s",p->exd);
				fflush(stdin);
		     		break;
	        }
		}
	    if(p==NULL)      //�Ҳ���ָ����Ʒ���޸� 
	    {
	    	printf("δ�鵽����Ʒ���޸�\n");
            b--;
		}
	    printf("������������޸���Ʒ��Ϣ��(Y/N)");
		scanf(" %c",&c); 
		getchar();
	} 
	printf("%d����Ʒ����Ϣ�Ѿ��޸ĳɹ�!\n",b);  //��ʱ������Ʒ�޸���Ϣ 
	return head; 
}

void showBargain(struct Good* head)
{
	if(!head)  //�������޿ɲ�ѯ����Ʒ��Ϣ 
	{
		printf("û����Ʒ��Ϣ�ɹ���ѯ");
		return ;
	}
	struct Good *p=NULL;
	int num = 0;
	printf("  ��Ʒ���  ��Ʒ����  ��Ʒ�ۼ�  �Ƿ��Żݴ���  ��Ʒ���        ��������        ��������\n");
	for(p = head;p;p=p->next)
	{
		if(p->bargain != 0)
		{
			num++;
		    printf("%8d  %10s  %6g    %6g        %6d  %15s  %15s\n",p->number,p->name,p->price,p->bargain ,p->sale_number,p->pd,p->exd);
		}
	}
}


void remainAdmin(struct Good* head)
{
		if(!head)  //�������޿ɲ�ѯ����Ʒ��Ϣ 
	{
		return ;
		beSure = 1;
	}
	struct Good *p=NULL;
	int num 	= 0;
	int zero 	= 0;
	//printf("  ��Ʒ���  ��Ʒ����  ��Ʒ�ۼ�  �Ƿ��Żݴ���  ��Ʒ���        ��������        ��������\n");
	for(p = head;p;p=p->next)
	{
		if(p->sale_number <= 50 )
		{
			num++;
			if(p->sale_number == 0)
				zero++;
		}
	}
	
	if(num == 0)
	{
		printf("���Ŀ�����,�����账����¼�.\n");
		beSure = 1;
		return;
	}
	if(num != 0)
	{
		char buffer[216];
		sprintf(buffer,"����%d����Ʒ��治��50,������%d�Ѿ�����,�뼰ʱ����\n",num,zero);
		printf("%s��\n",buffer);

			MessageBox(NULL,buffer,"���й���ϵͳ��ʾ",MB_OK);
			beSure = 1;

	}
	
}



void setBargain(struct Good* head)
{
	if(!head)  //�������޿ɲ�ѯ����Ʒ��Ϣ 
	{
		printf("û����Ʒ��Ϣ�ɹ���ѯ");
		return ;
	}
	struct Good *p=NULL;
	int num = 0;
	printf("  ��Ʒ���  ��Ʒ����  ��Ʒ����  ��Ʒ�ۼ�  �Ƿ��Żݴ���  ��Ʒ���        ��������        ��������\n");
	for(p = head;p;p=p->next)
	{
		if(p->bargain != 0)
		{
			num++;
		    printf("%8d  %10s  %6g  %6g    %6g        %6d  %15s  %15s\n",p->number,p->name,p->cost,p->price,p->bargain ,p->sale_number,p->pd,p->exd);
		}
	}
	printf("�����Żݴ�����Ʒ��%d��\n",num);
	
	char c;
	int a;
	printf("�������Ƿ���Ҫ����Żݴ�����Ʒ��Ϣ����Y/N��");
	scanf(" %c",&c);      
	for(;c=='Y'||c=='y';)
	{
	    printf("��������������Żݴ��������Ʒ���:");       //���ݱ���ҵ�ָ����Ʒ 
	    scanf("%d",&a);
		for(p=head;p;p=p->next)
		{
			if(a==p->number)
	        {
	        	
			 system("cls");
			 printf("����Ʒ��Ϣ���£�\n");
	         printf("  ��Ʒ���  ��Ʒ����  ��Ʒ����  ��Ʒ�ۼ�  �Ƿ��Żݴ���  ��Ʒ���        ��������        ��������\n");
		     printf("%8d  %10s  %6g  %6g    %6g        %6d  %15s  %15s\n",p->number,p->name,p->cost,p->price,p->bargain ,p->sale_number,p->pd,p->exd);
			 printf("��������Ϊ����Ʒ���õ��ۿۣ�");
			 scanf("%lf",&p->bargain);



			 printf("�Ѿ��ɹ�������Ʒ�����Żݴ������\n") ;
			 printf("����Ʒ�۸���%6g ����Ϊ%6g��\n",p->price,p->price*p->bargain*0.1);
			 p->price = p->price * p->bargain * 0.1;
			 break;	
			 
	        }
		} 
	    if(p==NULL) printf("û���ҵ�����Ʒ����Ϣ\n");     //δ�ҵ�ָ������Ʒ��Ϣ�������䲢������ 

		printf("���������������Żݴ�����Ʒ��Ϣ����Y/N��");
		scanf(" %c",&c); 
	}
}



struct Good* add_good(struct Good* head)
{
	if(!head)           //	�������޿������޸ĵ���Ʒ��Ϣ 
	{
		printf("û����Ʒ��Ϣ\n");
		return head; 
	}
	char c;
	printf("�������벹����Ʒ�������(Y/N)��");
	scanf(" %c",&c);
	int a,b;
	for(b=0;c=='Y'||c=='y';b++)
	{
	    struct Good *p=NULL;
		printf("���������Ʒ�ı�ţ�");
		scanf("%d",&a);
	    for(p=head;p;p=p->next) //�ҵ�ָ����Ʒ��λ�� 
	    {
	    	if(a==p->number)   
	        {
	         	printf("�����벹�����Ʒ��Ϣ\n");      //����Ʒ���е���Ϣ���������� 


	    
	    		printf("����������Ʒ����������");
	    		int num1= 0; 
				scanf("%d",&num1);
				p->sale_number += num1;
				fflush(stdin);
		

		     		break;
	        }
		}
	    if(p==NULL)      //�Ҳ���ָ����Ʒ���޸� 
	    {
	    	printf("δ�鵽����Ʒ��Ϣ\n");
            b--;
		}
	    printf("�����������������Ʒ�������(Y/N)");
		scanf(" %c",&c); 
		getchar();
	} 
	printf("%d����Ʒ�Ŀ���Ѿ�����!\n",b);  //��ʱ������Ʒ�޸���Ϣ 
	return head; 
}




void sale_sum(struct Good * head) //ͳ����Ʒ����Ϣ 
{
	int 	a=0; //���������ܺ�  
	double 	b=0; //���۽���ܺ�  
	int		c=0; //��Ʒ�����ܺ� 
	double 	d=0;  //��������ܺ� 
	struct Good *p=NULL;
	for(p=head;p;p=p->next)
	{
		a+=p->sale_number;
		b+=p->price * p->sale_number;
		c++;
		d+=p->cost * p->sale_number ; 
	}
	printf("ͳ�����ݺ��֪��\n");       //ͳ���Ժ󽫽���������û� 
	printf("1������%d����Ʒ\n",c);
	printf("2����Ʒ�Ľ�������ܺ�Ϊ��%g\n",d);
	printf("3����Ʒ�����������ܺ�Ϊ��%d\n",a); 
	printf("4����Ʒ�����۽���ܺ�Ϊ��%g\n",b);
}
void storage_good (struct Good * head) //������Ʒ��Ϣ 
{
	if(!head) 
	{
		printf("û����Ʒ��Ϣ�ɹ�����\n");
		return ;
	}
	struct Good * p=NULL;
	FILE *fp;
	if((fp=fopen(".\\Good\\good.txt","wb"))==NULL)
	{
		printf("���ܴ���Ʒ��Ϣ�ļ�\n");
		return ;
	}
	for(p=head;p;p=p->next)
	{
		fwrite(p,GOOD,1,fp);
	}
	fclose(fp);
	printf("������Ʒ��Ϣ�ѳɹ������ļ���\n");
}
struct Good *open_good(struct Good *head)
{
	FILE *fp;
	struct Good *p,*q;
	if((fp=fopen(".\\Good\\good.txt","rb"))==NULL)
	{
		printf("�򲻿���Ʒ��Ϣ�ļ���\n");
		return head;
	}
    p=(struct Good *)malloc(GOOD);
	head=p;
	q=head;
	while(!feof(fp))
	{
		if(fread(p,GOOD,1,fp)!=1) break;
	    p->next=(struct Good *)malloc(GOOD);
        q=p->next;
        q=p;
        p=p->next;
	}
	q->next=NULL;
	fclose(fp);
	printf("��ȡ��Ʒ��Ϣ�ļ��ɹ�\n");
	return head;
}
