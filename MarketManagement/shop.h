#pragma once
#include "stdafx.h"
struct shop  //���ѽṹ�� 
{
	int 	number;  					// ��Ʒ��� 
    char 	name[10];					// ��Ʒ���� 
    double price;						// ��Ʒ���ۼ� 
    int   buy_number;					// ��Ʒ�Ĺ�������
    int		opinion;					// ��Ʒ������
	struct shop *next; 
};


struct complain
{
	int number;						// ����Ա���
	char str[256];					// ��� 
};

void valShop(struct shop *head)  								//	��Ʒ���� 
{
	if(!head)  //�������޿ɲ�ѯ����Ʒ��Ϣ 
	{
		printf("����û�����Ѽ�¼");
		return ;
	}
	char c;
	int a;
	struct shop *p=NULL;
	printf("�������Ƿ���Ҫ�����ѹ���Ʒ����Y/N��");
	scanf(" %c",&c);      
	for(;c=='Y'||c=='y';)
	{
	    printf("�������������۵���Ʒ�ı��:");       //���ݱ���ҵ�ָ����Ʒ 
	    scanf("%d",&a);
		for(p=head;p;p=p->next)
		{
			if(a==p->number)
	        {
			 printf("��������������\n");
			 scanf("%d",&p->opinion ); 
		     printf("���۳ɹ���\n");
		     break;
	        }
		} 
	    if(p==NULL) printf("û���ҵ�����Ʒ����Ϣ\n");     //δ�ҵ�ָ������Ʒ��Ϣ�������䲢������ 
		printf("����������������ѹ���Ʒ�𣿣�Y/N��");
		scanf(" %c",&c); 
	}
	save_shop(head);
}


void show_good(struct Good* head)
{
	if(!head)  //���������ڿ����������Ʒ��Ϣ 
	{
		printf("û�пɹ��������Ʒ��Ϣ��");
		return ; 
	}
    struct Good *p=NULL;
    printf("  ��Ʒ���  ��Ʒ����  ��Ʒ�ۼ�  ��Ʒ���      ��������      ��������\n");
    for(p=head;p;p=p->next) //���������ע���ʽ 
    {
       printf("%8d  %10s  %6g    %6d  %15s  %15s\n",p->number,p->name,p->price,p->sale_number,p->pd,p->exd);
	}
	
}



struct shop *purchase(struct shop *shophead,struct Good *head)  //	����
{
	if(!head)  //�������޿ɲ�ѯ����Ʒ��Ϣ 
	{
		printf("û����Ʒ��Ϣ");
		return ;
	}
	
	char c = 'y';
	int buy_number = 0;
	int a =0 ;
	for(a=0;c=='Y'||c=='y';a++) 
	{

		int b;
		struct Good *p=NULL;   
		printf("���������빺�����Ʒ�ı��:");       //���ݱ���ҵ�ָ����Ʒ 
		scanf("%d",&b);
		for(p=head;p;p=p->next)
		{
			if(b==p->number)
	    	{
				printf("����Ʒ��Ϣ���£�\n");
	    		printf("  ��Ʒ���  ��Ʒ����  ��Ʒ�ۼ�  ��Ʒ���    ��������    ��������\n");
		     	printf("%8d  %10s  %6g    %6d  %15s  %15s\n",p->number,p->name,p->price,p->sale_number,p->pd,p->exd);
				break;	
	    	}
		} 
		if(p==NULL) printf("û���ҵ�����Ʒ����Ϣ\n");     //δ�ҵ�ָ������Ʒ��Ϣ�������䲢������ 
	     
	

		printf("\n�������빺�����Ʒ��(Y/N)��");
    	scanf(" %c",&c);
    	if(c!='Y'&&c!='y')
    		break;
		printf("\n���������빺�������");
		fflush(stdin);
		scanf("%d",&buy_number); 
		
		if(buy_number > p->sale_number )
		{
			printf("\n��Ǹ������Ʒ��治��,��Ϊ������%d������Ʒ\n",p->sale_number); 	
			buy_number = p->sale_number ;	
		}
		else
		 	printf("\n\t ����ɹ���\n");
		p->sale_number -= buy_number; 			//	��ȥ�ѹ�������� 
		


		struct shop *p1=NULL;
	    struct shop *p2=NULL; 
	    p1=(struct shop *)malloc(SHOP);   //����ռ� 
		if(!p1)
	    {
	    	printf("�����ڴ治���ʧ���ˣ�");
		    return shophead;
	    }  //�����ڴ�ʧ�� 
	    p1->next=NULL;
	    
	    

		p1->number = p->number;
		strcpy(p1->name,p->name);

		if(level <= 100)
			p1->price = p->price;
		if(level <= 500 && level >100)
			p1->price = p->price*0.98;		
		if(level <= 1000 && level >500)
			p1->price = p->price*0.95;
		if(level > 1000)
			p1->price = p->price*0.9;

		p1->buy_number = buy_number;
		p1->opinion = 5;								// Ĭ������Ϊ���� 5 
		
	    
	    if(!shophead)
	    {
		    shophead=p1;
      	}   
	    else
	    {
		  for(p2=shophead;p2->next;p2=p2->next);
		  p2->next=p1;
	    }

	    
		printf("�����������������Ʒ��(Y/N)");
		scanf(" %c",&c);
	}   
		system("cls");
	printf("�ѳɹ�����%d����Ʒ\n",a);   //��ʱ�����û���Ϣ¼�����

	save_shop(shophead);
	storage_good(head);

	return shophead;
}


void print_shop(struct shop * shophead)  						//	������Ѽ�¼ 
{

	
	if(!shophead)   //������û�п�����ĵ�����Ϣ��Ӧ�˳� 
	{
		printf("��Ǹ��û�п�����ĵ�����Ϣ��");
		return ; 
	}
	struct shop *p=NULL;
	printf("��Ʒ���  ��Ʒ����  ��Ʒ�ۼ�  ��������  ��������\n");
	for(p=shophead;p;p=p->next)
	{
	  printf("%6d  %8s  %6g  %6d  %6d\n",p->number,p->name,p->price,p->buy_number,p->opinion);
	}
}

void complain()													//	Ͷ�� 
{
	char buffer[100];
	memset(buffer,0,sizeof(buffer));
	FILE* fp =NULL;
	sprintf(buffer,".\\Complain\\%d_complain.txt",consumer_id);
	fp = fopen(buffer,"w");
	
	char c;

	struct complain *com1;
	com1 = (struct complain*)malloc(sizeof(struct complain));
	memset(com1,0,sizeof(struct complain));

	printf("��������Ͷ���̵����Ա�𣿣�Y/N��");
	scanf(" %c",&c);
    if(c=='Y'||c=='y') 
	{ 
		printf("��������ҪͶ�ߵĹ���Ա���:\n");
		scanf("%d",&com1->number);
		fflush(stdin);
		printf("����������Ͷ��ԭ��\n");
		scanf("%s",com1->str );
		fflush(stdin);
			
		printf("Ͷ�߳ɹ������ǽ����촦��\n"); 
		fwrite(com1,sizeof(struct complain),1,fp);
	 
	}

	fclose(fp);
	
	
}

void suggest()													//	���� 
{
	FILE* fp =NULL;
	char buffer[100];
	sprintf(buffer,".\\Suggestion\\%d_suggestion.txt",consumer_id);
	fp = fopen(buffer,"w");
	char str[512];
	memset(str,0,sizeof(str));
	char c;
	int a,b;

	printf("�����������ǵķ�����߲�Ʒ�и��õ���������𣿣�Y/N��");
	scanf(" %c",&c);
    for(b=0;c=='Y'||c=='y';b++) 
	{ 

		printf("����������������߽��飬��������ǲ��ɺ󣬽��������һ���Ľ�����лл����֧��\n");
		
		scanf("%s",str );
		fflush(stdin);
			
		printf("��л������������飬ף���������\n"); 
		
		fwrite(str,512*sizeof(char),1,fp);

	    printf("����������������������𣿣�Y/N��");
	    scanf(" %c",&c);
	}
	fclose(fp);
 } 


struct shop *Deleteshop (struct shop * head) 					//	ɾ��ָ���ѹ���Ʒ��Ϣ 
{
	if(!head) //����Ϊ�գ��޿ɱ�ɾ���ĵ�����Ϣ 
	{
		printf("��Ǹ����û�п���ɾ���ĵ�����Ϣ\n");
		return head;
    }
	char c;
	int a,b;
	printf("��������ɾ��������Ϣ�𣿣�Y/N��");
	scanf(" %c",&c);
    for(b=0;c=='Y'||c=='y';b++) 
	{ 
		struct shop *p=NULL;
	    struct shop *q=NULL;
	    printf("������������ɾ���ĵ��̵ı��:");
	    scanf("%d",&a);
	    for(p=head;p;q=p,p=p->next)//Ѱ��ָ�������������е�λ�� 
		{
			if(a==p->number)
	        {
	         	if(q!=NULL) q->next=p->next;
	            else        head=p->next;
		        free(p);    //�ͷŸÿռ� 
		        printf("�õ��̵���Ϣɾ���ɹ���\n");
		        break;
	        } 
		}  
	    if(p==NULL)
	    {
		    printf("û���ҵ�������ɾ���ĵ���\n"); 
		    b--;
	    }
	    printf("�������������ɾ��������Ϣ�𣿣�Y/N��");
	    scanf(" %c",&c);
	}
	printf("%d�����̵���Ϣ�Ѿ�ɾ���ɹ�\n",b);   //��ʱ�����û�ɾ����� 
	return head;
}

struct shop *modifyshop(struct shop *head,struct Good *ghead) 	//	��Ʒ�˻� 
{
	if(!head)
	{
		printf("����û�����Ѽ�¼");
		return head;
	}
	int a,b;
	char c;
	printf("������������ѹ���Ʒ��(Y/N)��");
	scanf(" %c",&c);
	for(a=0;c=='Y'||c=='y';a++)
	{
	   struct shop *p=NULL;
	   printf("���������Ʒ�ı�ţ�");
	   scanf("%d",&b);
	   for(p=head;p;p=p->next) //�ҵ�ָ���������޸� 
	   {
	   	   if(b==p->number)
	       {
	        printf("��������Ҫ��������Ʒ��Ϣ\n");
	        printf("�����������������Ʒ�ı�ţ�");
	        int pFlag = 0;
	        scanf("%d",&pFlag) ;
	        struct Good *gp;

			for(gp=ghead;gp;gp=gp->next)
			{
				if(pFlag==gp->number)
	    		{
					printf("����Ʒ��Ϣ���£�\n");
	    			printf("  ��Ʒ���  ��Ʒ����  ��Ʒ�ۼ�  ��Ʒ���      ��������      ��������\n");
		     		printf("%8d  %10s  %6g    %6d  %15s  %15s\n",gp->number,gp->name,gp->price,gp->sale_number,gp->pd,gp->exd);
					break;	
	    		}
			} 
			if(p==NULL) printf("û���ҵ�����Ʒ����Ϣ\n");     //δ�ҵ�ָ������Ʒ��Ϣ�������䲢������ 
	     
	     	printf("�Ƿ����Ϊ����Ʒ��(Y/N)\t");
	     	char cht;
	     	fflush(stdin);
	     	scanf("%c",&cht);
	     	if(cht != 'y'&& cht != 'Y')
	        	break;
	        	
	        
	        if(gp->sale_number < p->buy_number)
	        {
	        	printf("\n��Ǹ������Ʒ��治��,��Ϊ������%d������Ʒ\n",gp->sale_number); 	

				struct shop *temp=(struct shop*)malloc(SHOP);
				temp->next = p->next;
				p->next = temp;
				temp->buy_number = p->buy_number - gp->sale_number ;
				temp->number = p->number ;
				strcpy(temp->name,p->name);
				temp->opinion = 5;
				temp->price = p->price;
				
				p->buy_number = gp->sale_number ;

			}
	        	
	        	
			p->number = gp->number;
			strcpy(p->name,gp->name);
			
			if(level <= 100)
				p->price = gp->price;
			if(level <= 500 && level >100)
				p->price = gp->price*0.98;		
			if(level <= 1000 && level >500)
				p->price = gp->price*0.95;
			if(level > 1000)
				p->price = gp->price*0.9;

			p->opinion = 5;
			gp->sale_number -= p->buy_number ;
	        
	        printf("�ѹ���Ʒ�����ɹ���\n");
	        
	        
	        struct Good *tp;

			for(tp=ghead;tp;tp=tp->next)
			{
				if(b==tp->number)
	    		{
					tp->sale_number += p->buy_number ; 
					
					break;	
	    		}
			}
	        
	        
	        
	        
	        
	        break;
	       } 
        }
       if(p==NULL)
	   {
	   	 printf("δ��ѯ������������Ķ������������Ƿ�������ȷ��\n");
	   	 a--;
	   }
	   printf("����������������������Ʒ��(Y/N)");
	   scanf(" %c",&c);
	} 
	printf("%d���ѹ���Ʒ�Ѿ������ɹ���\n",a);
	save_shop(head);
	storage_good(ghead);
	return head; 
}

void buy_sum(struct shop * head) //ͳ����Ʒ����Ϣ 
{

	
	int 	a=0; //���������ܺ�  
	double 	b=0; //�������ܺ�  
	int		c=0; //��Ʒ�����ܺ� 

	struct shop *p=NULL;
	for(p=head;p;p=p->next)
	{
		a+=p->buy_number;
		b+=p->price * p->buy_number;
		c++;

	}
	printf("ͳ�����ݺ��֪��\n");       //ͳ���Ժ󽫽���������û� 
	printf("1���������%d����Ʒ\n",c);
	printf("2����Ʒ�����ѽ���ܺ�Ϊ��%g\n",b);
	printf("3����Ʒ�����������ܺ�Ϊ��%d\n",a); 
}






void save_shop (struct shop * head) 							//	�����ѹ���Ʒ��Ϣ 
{
	struct shop * p=NULL;
	FILE *fp;
	char buffer[100];
	sprintf(buffer,".\\Shop\\%d.txt",consumer_id);
	
	
	if(!head) 
	{
		printf("û�й˿���Ϣ�ɹ�����\n");
		return ;
	}
	if((fp=fopen(buffer,"wb"))==NULL)
	{
		printf("�򲻿��˿���Ϣ�ļ�\n");
		return ;
	}
	for(p=head;p;p=p->next)
	{
		fwrite(p,SHOP,1,fp);
	}
	fclose(fp);
	printf("���Ѽ�¼��Ϣ�ѳɹ������ļ���\n");
}

struct shop *open_shop(struct shop *head)						//	��ȡ�ѹ���Ʒ��Ϣ 
{
	FILE *fp;
	struct shop *p,*q;
	char buffer[100];
	sprintf(buffer,".\\Shop\\%d.txt",consumer_id);
	
	if((fp=fopen(buffer,"rb"))==NULL)
	{
		printf("�򲻿��˿���Ϣ�ļ���\n");
		return head;
	}
    p=(struct shop *)malloc(SHOP);
	head=p;
	q=head;
	while(!feof(fp))
	{
		if(fread(p,SHOP,1,fp)!=1) break;
	    p->next=(struct shop *)malloc(SHOP);
        q=p->next;
        q=p;
        p=p->next;
	}
	q->next=NULL;
	fclose(fp);
	printf("��ȡ���Ѽ�¼�ļ��ɹ�\n");
	return head;
}


double VIP(struct shop *head)
{
	FILE *fp;
	struct shop *p,*q;
	char buffer[100];
	sprintf(buffer,".\\Shop\\%d.txt",consumer_id);
	
	if((fp=fopen(buffer,"rb"))==NULL)
	{
		printf("�򲻿��˿���Ϣ�ļ���\n");
		return 0;
	}
    p=(struct shop *)malloc(SHOP);
	head=p;
	q=head;
	while(!feof(fp))
	{
		if(fread(p,SHOP,1,fp)!=1) break;
	    p->next=(struct shop *)malloc(SHOP);
        q=p->next;
        q=p;
        p=p->next;
	}
	q->next=NULL;
	fclose(fp);
	
	double value = 0;
	
	p = NULL;
	for(p=head;p;p=p->next)
	{
		value+=p->price * p->buy_number;
	}
	
	return value;
	
}

