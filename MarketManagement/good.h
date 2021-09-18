#include "stdafx.h"
struct Good    							// 商品结构体 
{  
	int number;  						// 商品编号 
    char name[10];						// 商品名称 
    double cost; 						// 商品的进价 
    double price;						// 商品的售价
    int   sale_number;					// 商品的库存 
    char pd[15];						// 商品的生产日期
	char exd[15];						// 商品的有效截至日期 
	double bargain;						// 是否参与优惠促销活动 
    struct Good *next; 
};


struct Good * Increase_good (struct Good * head) //增添商品的信息 
{
	int a; 
	char c;
	printf("请问您是否想要录入商品信息？（Y/N）");
	scanf(" %c",&c);
	for(a=0;c=='Y'||c=='y';a++)
	{
		struct Good *p=NULL;
	    struct Good *q=NULL;
		p=(struct Good *)malloc(GOOD);
		if(!p)       //申请结点失败应当退出 
		{
			printf("录入信息失败\n");
		    return head;
		}
		p->next=NULL;
		printf("请输入该商品的相关信息\n");
		printf("①请输入商品编号：");
	    scanf("%d",&p->number) ;
		fflush(stdin); 
		
	    printf("②请输入商品名称：");
	    scanf("%s",p->name);
		fflush(stdin); 
	
	    printf("③请输入商品进价：");
     	scanf("%lf",&p->cost);
     	fflush(stdin);
     	
    	printf("④请输入商品售价：");
	    scanf("%lf",&p->price);
	    fflush(stdin);
	    
	    printf("⑤请输入商品数量：");
		scanf("%d",&p->sale_number);
		fflush(stdin);
		
		printf("⑥请输入商品的生产日期(如2020-01-01)：");
		scanf("%s",p->pd);
		fflush(stdin);
		
		printf("⑦请输入商品的有效日期(如2020-01-01)：");
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
	   	printf("请问您是否想要继续录入商品信息呢？（Y/N）");
	    scanf(" %c",&c);
	}
	printf("%d个商品的信息已经录入成功！\n",a);  //反馈给用户信息存储情况 
	return head;
}
void Show_Good(struct Good *head)   //显示链表中商品的信息 
{
	if(!head)  //空链表不存在可以输出的商品信息 
	{
		printf("没有可供输出的商品信息！");
		return ; 
	}
    struct Good *p=NULL;
    printf("  商品编号  商品名称  商品进价  商品售价  是否优惠促销  商品库存      生产日期      截至日期\n");
    for(p=head;p;p=p->next) //依次输出，注意格式 
    {
       printf("%8d  %10s  %6g  %6g    %6g        %6d  %15s  %15s\n",p->number,p->name,p->cost,p->price,p->bargain ,p->sale_number,p->pd,p->exd);
	}
}
void searchGood(struct Good *head)  //查询商品信息的功能函数 
{
	if(!head)  //空链表无可查询的商品信息 
	{
		printf("没有商品信息可供查询");
		
		return ;
	}
	char c;
	int a;
	struct Good *p=NULL;
	printf("请问您是否想要查询商品信息？（Y/N）");
	scanf(" %c",&c);      
	for(;c=='Y'||c=='y';)
	{
	    printf("请输入您想查询的商品的编号:");       //根据编号找到指定商品 
	    scanf("%d",&a);
		for(p=head;p;p=p->next)
		{
			if(a==p->number)
	        {
			 printf("该商品信息如下：\n");
	         printf("  商品编号  商品名称  商品进价  商品售价  是否优惠促销  商品库存        生产日期        截至日期\n");
		     printf("%8d  %10s  %6g  %6g    %6g        %6d  %15s  %15s\n",p->number,p->name,p->cost,p->price,p->bargain ,p->sale_number,p->pd,p->exd);
			 break;	
	        }
		} 
	    if(p==NULL) printf("没有找到该商品的信息\n");     //未找到指定的商品信息，可能其并不存在 
		printf("请问您想继续查询吗？（Y/N）");
		scanf(" %c",&c); 
	}
}
struct Good* Deletegood(struct Good *head)  //删除指定商品的信息 
{
	if(!head)    //空链表无可删除的商品信息 
	{
		printf("抱歉,没有可供删除的商品信息\n");
		return head;
	}
	int a,b;
	char c;
	printf("请问您想删除商品信息吗？（Y/N）");
	scanf(" %c",&c);
	for(a=0;c=='Y'||c=='y';a++)
	{
	   struct Good *p=NULL;
	   struct Good *q=NULL;
	   printf("请输入您所想删除的商品的编号:");    //根据商品编号找到需要删除的商品 
	   scanf("%d",&b);
	    for(p=head;p;q=p,p=p->next)
	    {
	   	    if(b==p->number)
	        {
	         	if(q!=NULL) q->next=p->next;
	            else        head=p->next;
		        free(p);    //释放该空间 
		        printf("该商品的信息删除成功！\n");
		        break;
	        } 
	    }  
	    if(p==NULL)                //未找到指定商品，可能其不存在无法删除 
	    {
		 printf("没有找到您所想删除的商品\n"); 
		 a--;
	    }
	    printf("请问您还想继续删除商品信息吗？（Y/N）");
	    scanf(" %c",&c);
	}	
	printf("%d个商品的信息已经删除成功！\n",a);   //及时反馈给用户删除情况
	return head;
}
struct Good * modifygood(struct Good *head)  //修改商品的信息 
{
	if(!head)           //空链表无可用以修改的商品信息 
	{
		printf("没有商品信息可供修改\n");
		return head; 
	}
	char c;
	printf("请问您想修改商品信息吗(Y/N)？");
	scanf(" %c",&c);
	int a,b;
	for(b=0;c=='Y'||c=='y';b++)
	{
	    struct Good *p=NULL;
		printf("请输入该商品的编号：");
		scanf("%d",&a);
	    for(p=head;p;p=p->next) //找到指定商品的位置 
	    {
	    	if(a==p->number)   
	        {
	         	printf("请输入商品的新信息\n");      //该商品所有的信息都重新输入 
	        	printf("①请输入商品编号：");
	   	 		scanf("%d",&p->number) ;
				fflush(stdin); 
		
	    		printf("②请输入商品名称：");
	    		scanf("%s",p->name);
				fflush(stdin); 
		

	    		printf("③请输入商品进价：");
     			scanf("%lf",&p->cost);
     			fflush(stdin);
     	
    			printf("④请输入商品售价：");
	    		scanf("%lf",&p->price);
	    		fflush(stdin);
	    
	    		printf("⑤请输入商品数量：");
				scanf("%d",&p->sale_number);
				fflush(stdin);
		
				printf("⑥请输入商品的生产日期(如2020-01-01)：");
				scanf("%s",p->pd);
				fflush(stdin);
		
				printf("⑦请输入商品的有效日期(如2020-01-01)：");
				scanf("%s",p->exd);
				fflush(stdin);
		     		break;
	        }
		}
	    if(p==NULL)      //找不到指定商品来修改 
	    {
	    	printf("未查到该商品以修改\n");
            b--;
		}
	    printf("请问您想继续修改商品信息吗？(Y/N)");
		scanf(" %c",&c); 
		getchar();
	} 
	printf("%d个商品的信息已经修改成功!\n",b);  //及时反馈商品修改信息 
	return head; 
}

void showBargain(struct Good* head)
{
	if(!head)  //空链表无可查询的商品信息 
	{
		printf("没有商品信息可供查询");
		return ;
	}
	struct Good *p=NULL;
	int num = 0;
	printf("  商品编号  商品名称  商品售价  是否优惠促销  商品库存        生产日期        截至日期\n");
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
		if(!head)  //空链表无可查询的商品信息 
	{
		return ;
		beSure = 1;
	}
	struct Good *p=NULL;
	int num 	= 0;
	int zero 	= 0;
	//printf("  商品编号  商品名称  商品售价  是否优惠促销  商品库存        生产日期        截至日期\n");
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
		printf("您的库存充足,暂无需处理的事件.\n");
		beSure = 1;
		return;
	}
	if(num != 0)
	{
		char buffer[216];
		sprintf(buffer,"您有%d件商品库存不足50,其中有%d已经售罄,请及时处理\n",num,zero);
		printf("%s。\n",buffer);

			MessageBox(NULL,buffer,"超市管理系统提示",MB_OK);
			beSure = 1;

	}
	
}



void setBargain(struct Good* head)
{
	if(!head)  //空链表无可查询的商品信息 
	{
		printf("没有商品信息可供查询");
		return ;
	}
	struct Good *p=NULL;
	int num = 0;
	printf("  商品编号  商品名称  商品进价  商品售价  是否优惠促销  商品库存        生产日期        截至日期\n");
	for(p = head;p;p=p->next)
	{
		if(p->bargain != 0)
		{
			num++;
		    printf("%8d  %10s  %6g  %6g    %6g        %6d  %15s  %15s\n",p->number,p->name,p->cost,p->price,p->bargain ,p->sale_number,p->pd,p->exd);
		}
	}
	printf("已有优惠促销商品共%d种\n",num);
	
	char c;
	int a;
	printf("请问您是否想要添加优惠促销商品信息？（Y/N）");
	scanf(" %c",&c);      
	for(;c=='Y'||c=='y';)
	{
	    printf("请输入您想加入优惠促销活动的商品编号:");       //根据编号找到指定商品 
	    scanf("%d",&a);
		for(p=head;p;p=p->next)
		{
			if(a==p->number)
	        {
	        	
			 system("cls");
			 printf("该商品信息如下：\n");
	         printf("  商品编号  商品名称  商品进价  商品售价  是否优惠促销  商品库存        生产日期        截至日期\n");
		     printf("%8d  %10s  %6g  %6g    %6g        %6d  %15s  %15s\n",p->number,p->name,p->cost,p->price,p->bargain ,p->sale_number,p->pd,p->exd);
			 printf("请输入想为该商品设置的折扣：");
			 scanf("%lf",&p->bargain);



			 printf("已经成功将该商品加入优惠促销活动。\n") ;
			 printf("该商品价格由%6g 调整为%6g。\n",p->price,p->price*p->bargain*0.1);
			 p->price = p->price * p->bargain * 0.1;
			 break;	
			 
	        }
		} 
	    if(p==NULL) printf("没有找到该商品的信息\n");     //未找到指定的商品信息，可能其并不存在 

		printf("请问您想继续添加优惠促销商品信息？（Y/N）");
		scanf(" %c",&c); 
	}
}



struct Good* add_good(struct Good* head)
{
	if(!head)           //	空链表无可用以修改的商品信息 
	{
		printf("没有商品信息\n");
		return head; 
	}
	char c;
	printf("请问您想补充商品库存量吗(Y/N)？");
	scanf(" %c",&c);
	int a,b;
	for(b=0;c=='Y'||c=='y';b++)
	{
	    struct Good *p=NULL;
		printf("请输入该商品的编号：");
		scanf("%d",&a);
	    for(p=head;p;p=p->next) //找到指定商品的位置 
	    {
	    	if(a==p->number)   
	        {
	         	printf("请输入补充的商品信息\n");      //该商品所有的信息都重新输入 


	    
	    		printf("⑤请输入商品进货数量：");
	    		int num1= 0; 
				scanf("%d",&num1);
				p->sale_number += num1;
				fflush(stdin);
		

		     		break;
	        }
		}
	    if(p==NULL)      //找不到指定商品来修改 
	    {
	    	printf("未查到该商品信息\n");
            b--;
		}
	    printf("请问您想继续补充商品库存量吗？(Y/N)");
		scanf(" %c",&c); 
		getchar();
	} 
	printf("%d个商品的库存已经更新!\n",b);  //及时反馈商品修改信息 
	return head; 
}




void sale_sum(struct Good * head) //统计商品的信息 
{
	int 	a=0; //销售数量总和  
	double 	b=0; //销售金额总和  
	int		c=0; //商品数量总和 
	double 	d=0;  //进货金额总和 
	struct Good *p=NULL;
	for(p=head;p;p=p->next)
	{
		a+=p->sale_number;
		b+=p->price * p->sale_number;
		c++;
		d+=p->cost * p->sale_number ; 
	}
	printf("统计数据后可知：\n");       //统计以后将结果反馈给用户 
	printf("1、共有%d种商品\n",c);
	printf("2、商品的进货金额总和为：%g\n",d);
	printf("3、商品的销售数量总和为：%d\n",a); 
	printf("4、商品的销售金额总和为：%g\n",b);
}
void storage_good (struct Good * head) //保存商品信息 
{
	if(!head) 
	{
		printf("没有商品信息可供储存\n");
		return ;
	}
	struct Good * p=NULL;
	FILE *fp;
	if((fp=fopen(".\\Good\\good.txt","wb"))==NULL)
	{
		printf("不能打开商品信息文件\n");
		return ;
	}
	for(p=head;p;p=p->next)
	{
		fwrite(p,GOOD,1,fp);
	}
	fclose(fp);
	printf("所有商品信息已成功存入文件！\n");
}
struct Good *open_good(struct Good *head)
{
	FILE *fp;
	struct Good *p,*q;
	if((fp=fopen(".\\Good\\good.txt","rb"))==NULL)
	{
		printf("打不开商品信息文件！\n");
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
	printf("读取商品信息文件成功\n");
	return head;
}
