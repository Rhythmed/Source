#pragma once
#include "stdafx.h"
struct shop  //消费结构体 
{
	int 	number;  					// 商品编号 
    char 	name[10];					// 商品名称 
    double price;						// 商品的售价 
    int   buy_number;					// 商品的购买数量
    int		opinion;					// 商品的评价
	struct shop *next; 
};


struct complain
{
	int number;						// 管理员编号
	char str[256];					// 意见 
};

void valShop(struct shop *head)  								//	商品评价 
{
	if(!head)  //空链表无可查询的商品信息 
	{
		printf("近期没有消费记录");
		return ;
	}
	char c;
	int a;
	struct shop *p=NULL;
	printf("请问您是否想要评价已购商品？（Y/N）");
	scanf(" %c",&c);      
	for(;c=='Y'||c=='y';)
	{
	    printf("请输入您想评价的商品的编号:");       //根据编号找到指定商品 
	    scanf("%d",&a);
		for(p=head;p;p=p->next)
		{
			if(a==p->number)
	        {
			 printf("请输入您的评分\n");
			 scanf("%d",&p->opinion ); 
		     printf("评价成功！\n");
		     break;
	        }
		} 
	    if(p==NULL) printf("没有找到该商品的信息\n");     //未找到指定的商品信息，可能其并不存在 
		printf("请问您想继续评价已购商品吗？（Y/N）");
		scanf(" %c",&c); 
	}
	save_shop(head);
}


void show_good(struct Good* head)
{
	if(!head)  //空链表不存在可以输出的商品信息 
	{
		printf("没有可供输出的商品信息！");
		return ; 
	}
    struct Good *p=NULL;
    printf("  商品编号  商品名称  商品售价  商品库存      生产日期      截至日期\n");
    for(p=head;p;p=p->next) //依次输出，注意格式 
    {
       printf("%8d  %10s  %6g    %6d  %15s  %15s\n",p->number,p->name,p->price,p->sale_number,p->pd,p->exd);
	}
	
}



struct shop *purchase(struct shop *shophead,struct Good *head)  //	购买
{
	if(!head)  //空链表无可查询的商品信息 
	{
		printf("没有商品信息");
		return ;
	}
	
	char c = 'y';
	int buy_number = 0;
	int a =0 ;
	for(a=0;c=='Y'||c=='y';a++) 
	{

		int b;
		struct Good *p=NULL;   
		printf("请输入您想购买的商品的编号:");       //根据编号找到指定商品 
		scanf("%d",&b);
		for(p=head;p;p=p->next)
		{
			if(b==p->number)
	    	{
				printf("该商品信息如下：\n");
	    		printf("  商品编号  商品名称  商品售价  商品库存    生产日期    截至日期\n");
		     	printf("%8d  %10s  %6g    %6d  %15s  %15s\n",p->number,p->name,p->price,p->sale_number,p->pd,p->exd);
				break;	
	    	}
		} 
		if(p==NULL) printf("没有找到该商品的信息\n");     //未找到指定的商品信息，可能其并不存在 
	     
	

		printf("\n请问您想购买该商品吗(Y/N)？");
    	scanf(" %c",&c);
    	if(c!='Y'&&c!='y')
    		break;
		printf("\n请输入您想购买的数量");
		fflush(stdin);
		scanf("%d",&buy_number); 
		
		if(buy_number > p->sale_number )
		{
			printf("\n抱歉，该商品库存不足,已为您购买%d件该商品\n",p->sale_number); 	
			buy_number = p->sale_number ;	
		}
		else
		 	printf("\n\t 购买成功！\n");
		p->sale_number -= buy_number; 			//	减去已购买的数量 
		


		struct shop *p1=NULL;
	    struct shop *p2=NULL; 
	    p1=(struct shop *)malloc(SHOP);   //申请空间 
		if(!p1)
	    {
	    	printf("由于内存不足而失败了！");
		    return shophead;
	    }  //申请内存失败 
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
		p1->opinion = 5;								// 默认评分为中评 5 
		
	    
	    if(!shophead)
	    {
		    shophead=p1;
      	}   
	    else
	    {
		  for(p2=shophead;p2->next;p2=p2->next);
		  p2->next=p1;
	    }

	    
		printf("请问您想继续购买商品吗？(Y/N)");
		scanf(" %c",&c);
	}   
		system("cls");
	printf("已成功购买%d种商品\n",a);   //及时反馈用户信息录入情况

	save_shop(shophead);
	storage_good(head);

	return shophead;
}


void print_shop(struct shop * shophead)  						//	输出消费记录 
{

	
	if(!shophead)   //空链表没有可输出的店铺信息，应退出 
	{
		printf("抱歉，没有可输出的店铺信息！");
		return ; 
	}
	struct shop *p=NULL;
	printf("商品编号  商品名称  商品售价  购买数量  消费评价\n");
	for(p=shophead;p;p=p->next)
	{
	  printf("%6d  %8s  %6g  %6d  %6d\n",p->number,p->name,p->price,p->buy_number,p->opinion);
	}
}

void complain()													//	投诉 
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

	printf("请问您想投诉商店管理员吗？（Y/N）");
	scanf(" %c",&c);
    if(c=='Y'||c=='y') 
	{ 
		printf("请输入您要投诉的管理员编号:\n");
		scanf("%d",&com1->number);
		fflush(stdin);
		printf("请描述您的投诉原因\n");
		scanf("%s",com1->str );
		fflush(stdin);
			
		printf("投诉成功，我们将尽快处理\n"); 
		fwrite(com1,sizeof(struct complain),1,fp);
	 
	}

	fclose(fp);
	
	
}

void suggest()													//	建议 
{
	FILE* fp =NULL;
	char buffer[100];
	sprintf(buffer,".\\Suggestion\\%d_suggestion.txt",consumer_id);
	fp = fopen(buffer,"w");
	char str[512];
	memset(str,0,sizeof(str));
	char c;
	int a,b;

	printf("请问您对我们的服务或者产品有更好的意见或建议吗？（Y/N）");
	scanf(" %c",&c);
    for(b=0;c=='Y'||c=='y';b++) 
	{ 

		printf("请描述您的意见或者建议，意见经我们采纳后，将会给予您一定的奖励，谢谢您的支持\n");
		
		scanf("%s",str );
		fflush(stdin);
			
		printf("感谢您的意见及建议，祝您生活愉快\n"); 
		
		fwrite(str,512*sizeof(char),1,fp);

	    printf("请问您还有其它意见或建议吗？（Y/N）");
	    scanf(" %c",&c);
	}
	fclose(fp);
 } 


struct shop *Deleteshop (struct shop * head) 					//	删除指定已购商品信息 
{
	if(!head) //链表为空，无可被删除的店铺信息 
	{
		printf("抱歉，您没有可以删除的店铺信息\n");
		return head;
    }
	char c;
	int a,b;
	printf("请问您想删除店铺信息吗？（Y/N）");
	scanf(" %c",&c);
    for(b=0;c=='Y'||c=='y';b++) 
	{ 
		struct shop *p=NULL;
	    struct shop *q=NULL;
	    printf("请输入您所想删除的店铺的编号:");
	    scanf("%d",&a);
	    for(p=head;p;q=p,p=p->next)//寻找指定店铺在链表中的位置 
		{
			if(a==p->number)
	        {
	         	if(q!=NULL) q->next=p->next;
	            else        head=p->next;
		        free(p);    //释放该空间 
		        printf("该店铺的信息删除成功！\n");
		        break;
	        } 
		}  
	    if(p==NULL)
	    {
		    printf("没有找到您所想删除的店铺\n"); 
		    b--;
	    }
	    printf("请问您还想继续删除店铺信息吗？（Y/N）");
	    scanf(" %c",&c);
	}
	printf("%d个店铺的信息已经删除成功\n",b);   //及时反馈用户删除情况 
	return head;
}

struct shop *modifyshop(struct shop *head,struct Good *ghead) 	//	商品退换 
{
	if(!head)
	{
		printf("近期没有消费记录");
		return head;
	}
	int a,b;
	char c;
	printf("请问您想更换已购产品吗(Y/N)？");
	scanf(" %c",&c);
	for(a=0;c=='Y'||c=='y';a++)
	{
	   struct shop *p=NULL;
	   printf("请输入该商品的编号：");
	   scanf("%d",&b);
	   for(p=head;p;p=p->next) //找到指定店铺以修改 
	   {
	   	   if(b==p->number)
	       {
	        printf("请输入想要更换的商品信息\n");
	        printf("①请输入想更换的商品的编号：");
	        int pFlag = 0;
	        scanf("%d",&pFlag) ;
	        struct Good *gp;

			for(gp=ghead;gp;gp=gp->next)
			{
				if(pFlag==gp->number)
	    		{
					printf("该商品信息如下：\n");
	    			printf("  商品编号  商品名称  商品售价  商品库存      生产日期      截至日期\n");
		     		printf("%8d  %10s  %6g    %6d  %15s  %15s\n",gp->number,gp->name,gp->price,gp->sale_number,gp->pd,gp->exd);
					break;	
	    		}
			} 
			if(p==NULL) printf("没有找到该商品的信息\n");     //未找到指定的商品信息，可能其并不存在 
	     
	     	printf("是否更换为该商品？(Y/N)\t");
	     	char cht;
	     	fflush(stdin);
	     	scanf("%c",&cht);
	     	if(cht != 'y'&& cht != 'Y')
	        	break;
	        	
	        
	        if(gp->sale_number < p->buy_number)
	        {
	        	printf("\n抱歉，该商品库存不足,已为您更换%d件该商品\n",gp->sale_number); 	

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
	        
	        printf("已购商品更换成功！\n");
	        
	        
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
	   	 printf("未查询到您所想更换的订单，请检查编号是否输入正确！\n");
	   	 a--;
	   }
	   printf("请问您想继续更换购买的商品吗？(Y/N)");
	   scanf(" %c",&c);
	} 
	printf("%d个已购商品已经更换成功！\n",a);
	save_shop(head);
	storage_good(ghead);
	return head; 
}

void buy_sum(struct shop * head) //统计商品的信息 
{

	
	int 	a=0; //购买数量总和  
	double 	b=0; //购买金额总和  
	int		c=0; //商品种类总和 

	struct shop *p=NULL;
	for(p=head;p;p=p->next)
	{
		a+=p->buy_number;
		b+=p->price * p->buy_number;
		c++;

	}
	printf("统计数据后可知：\n");       //统计以后将结果反馈给用户 
	printf("1、共购买过%d种商品\n",c);
	printf("2、商品的消费金额总和为：%g\n",b);
	printf("3、商品的消费数量总和为：%d\n",a); 
}






void save_shop (struct shop * head) 							//	保存已购商品信息 
{
	struct shop * p=NULL;
	FILE *fp;
	char buffer[100];
	sprintf(buffer,".\\Shop\\%d.txt",consumer_id);
	
	
	if(!head) 
	{
		printf("没有顾客信息可供储存\n");
		return ;
	}
	if((fp=fopen(buffer,"wb"))==NULL)
	{
		printf("打不开顾客信息文件\n");
		return ;
	}
	for(p=head;p;p=p->next)
	{
		fwrite(p,SHOP,1,fp);
	}
	fclose(fp);
	printf("消费记录信息已成功存入文件！\n");
}

struct shop *open_shop(struct shop *head)						//	读取已购商品信息 
{
	FILE *fp;
	struct shop *p,*q;
	char buffer[100];
	sprintf(buffer,".\\Shop\\%d.txt",consumer_id);
	
	if((fp=fopen(buffer,"rb"))==NULL)
	{
		printf("打不开顾客信息文件！\n");
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
	printf("读取消费记录文件成功\n");
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
		printf("打不开顾客信息文件！\n");
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

