#include "code.h"
#include "stdafx.h"

int memu()  //主目录 
{
	
	int a;     //用以记录用户在主目录的抉择 
	
	time_t t;
	struct tm *lt;
	time(&t);
	lt = localtime(&t);
	
	printf("\n\t\t   当前系统时间：%d年%d月%d日,",lt->tm_year + 1900,lt->tm_mon,lt->tm_mday);
	switch(lt->tm_wday)
	{
		case 0:
			printf("星期日");
			break; 
		case 1:
			printf("星期一");
			break; 
		case 2:
			printf("星期二");
			break; 
		case 3:
			printf("星期三");
			break; 
		case 4:
			printf("星期四");
			break; 
		case 5:
			printf("星期五");
			break; 
		case 6:
			printf("星期六");
			break; 
	}
	printf(",%d时%d分%d秒\n",lt->tm_hour ,lt->tm_min ,lt->tm_sec );
	
	printf("\n\n\t\t*************************************************\t\t\n") ;
    printf("\t\t*\t\t超市管理系统\t\t\t*\t\n");
	printf("\t\t*1、管理员登录\t\t\t\t\t*\n");
	printf("\t\t*2、老板登录\t\t\t\t\t*\n");
	printf("\t\t*3、顾客登录\t\t\t\t\t*\n");
	printf("\t\t*4、退出系统\t\t\t\t\t*\n");
	printf("\t\t*************************************************\t\t\n") ;
	printf("请输入您的选择：");
	scanf("%d",&a);
	return a;
}
int goodmemu()    //商品信息管理目录 
{
	int a;        //定义变量记录用户在商品管理上的选择 
	
		
		time_t t;
	struct tm *lt;
	time(&t);
	lt = localtime(&t);
	
	printf("\n\t\t   当前系统时间：%d年%d月%d日,",lt->tm_year + 1900,lt->tm_mon,lt->tm_mday);
	switch(lt->tm_wday)
	{
		case 0:
			printf("星期日");
			break; 
		case 1:
			printf("星期一");
			break; 
		case 2:
			printf("星期二");
			break; 
		case 3:
			printf("星期三");
			break; 
		case 4:
			printf("星期四");
			break; 
		case 5:
			printf("星期五");
			break; 
		case 6:
			printf("星期六");
			break; 
	}
	printf(",%d时%d分%d秒\n",lt->tm_hour ,lt->tm_min ,lt->tm_sec );
	
	
	printf("\n\n\n\n\n\t\t*************************************************\t\t\n") ;
    printf("\t\t*\t\t商品管理系统(管理员)\t\t*\n");
	printf("\t\t*1、商品信息录入\t\t\t\t*\n");
	printf("\t\t*2、补充商品库存\t\t\t\t*\n");
	printf("\t\t*3、商品信息查询\t\t\t\t*\n");
	printf("\t\t*4、商品信息修改\t\t\t\t*\n");
	printf("\t\t*5、商品信息删除\t\t\t\t*\n");
	printf("\t\t*6、设置优惠促销活动\t\t\t\t*\n");	
	printf("\t\t*7、商品信息展示\t\t\t\t*\n"); 
	printf("\t\t*8、商品信息统计\t\t\t\t*\n");
	printf("\t\t*9、商品信息储存入文件\t\t\t\t*\n"); 
	printf("\t\t*10、文件中导出商品信息\t\t\t\t*\n");
	printf("\t\t*11、退出\t\t\t\t\t*\n");
	printf("\t\t*************************************************\t\t\n") ;
	printf("请输入你的选择：");
	scanf("%d",&a);
	return a;
} 
int shopmemu(double level)  //店铺信息管理目录 
{
	int a;     //定义一个变量记录用户在店铺信息管理上的抉择 
		
	time_t t;
	struct tm *lt;
	time(&t);
	lt = localtime(&t);
	
	printf("\n\t\t   当前系统时间：%d年%d月%d日,",lt->tm_year + 1900,lt->tm_mon,lt->tm_mday);
	switch(lt->tm_wday)
	{
		case 0:
			printf("星期日");
			break; 
		case 1:
			printf("星期一");
			break; 
		case 2:
			printf("星期二");
			break; 
		case 3:
			printf("星期三");
			break; 
		case 4:
			printf("星期四");
			break; 
		case 5:
			printf("星期五");
			break; 
		case 6:
			printf("星期六");
			break; 
	}
	printf(",%d时%d分%d秒\n",lt->tm_hour ,lt->tm_min ,lt->tm_sec );
	if(level <= 100)
		printf("\n\t\t     青铜会员您好,欢迎您的登录");
	if(level <= 500 && level >100)
		printf("\n\t\t     白银会员您好,欢迎您的登录,您可享受0.98折优惠");
	if(level <= 1000 && level >500)
		printf("\n\t\t     黄金会员您好,欢迎您的登录,您可享受0.95折优惠");
	if(level > 1000)
		printf("\n\t\t     铂金会员您好,欢迎您的登录,您可享受0.9折优惠");	
	
	
	printf("\n\n\n\t\t*************************************************\t\t\n") ;
    printf("\t\t*\t\t购物管理(顾客)\t\t\t*\t\n");   
	printf("\t\t*1、查询商品\t\t\t\t\t*\n");
	printf("\t\t*2、购买商品\t\t\t\t\t*\n");
	printf("\t\t*3、退换商品\t\t\t\t\t*\n");
	printf("\t\t*4、查看促销活动\t\t\t\t*\n");
	printf("\t\t*5、查看消费历史记录\t\t\t\t*\n"); 
	printf("\t\t*6、为商品撰写评价\t\t\t\t*\n"); 
	printf("\t\t*7、投诉管理员、收银员\t\t\t\t*\n");
	printf("\t\t*8、为超市提供建议\t\t\t\t*\n"); 
	printf("\t\t*9、统计消费信息\t\t\t\t*\n"); 
	printf("\t\t*10、退出\t\t\t\t\t*\n");
	printf("\t\t*************************************************\t\t\n") ;
	printf("请输入你的选择：");
	scanf("%d",&a);
	return a;
}
int staffmemu()  //员工信息管理目录 
{
	int a;       //定义一个变量记录用户在员工信息管理上的抉择 
		
		time_t t;
	struct tm *lt;
	time(&t);
	lt = localtime(&t);
	
	printf("\n\t\t   当前系统时间：%d年%d月%d日,",lt->tm_year + 1900,lt->tm_mon,lt->tm_mday);
	switch(lt->tm_wday)
	{
		case 0:
			printf("星期日");
			break; 
		case 1:
			printf("星期一");
			break; 
		case 2:
			printf("星期二");
			break; 
		case 3:
			printf("星期三");
			break; 
		case 4:
			printf("星期四");
			break; 
		case 5:
			printf("星期五");
			break; 
		case 6:
			printf("星期六");
			break; 
	}
	printf(",%d时%d分%d秒\n",lt->tm_hour ,lt->tm_min ,lt->tm_sec );
	
	
	printf("\n\n\n\n\t\t*************************************************\t\t\n") ;
    printf("\t\t*\t\t员工管理系统(老板)\t\t*\t\n");
	printf("\t\t*1、添加新员工\t\t\t\t\t*\n");
	printf("\t\t*2、辞退员工\t\t\t\t\t*\n");
	printf("\t\t*3、显示所有员工\t\t\t\t*\n");
	printf("\t\t*4、商品信息展示\t\t\t\t*\n");
	printf("\t\t*5、商品信息统计\t\t\t\t*\n");
	printf("\t\t*6、查看投诉信息\t\t\t\t*\n");
	printf("\t\t*7、查看顾客建议\t\t\t\t*\n");
	printf("\t\t*8、退出老板界面\t\t\t\t*\n");
	printf("\t\t*************************************************\t\t\n") ;
	printf("请输入你的选择：");
	scanf("%d",&a);
	return a;
}

int codeMenu(int flag)
{	
	struct user our_users[N];		//	结构体储存账户信息 
	
	int count = 0;					//	账户总数 
	int current_user;				//	当前账户 



	FILE* fp = fopen("account_system.dat","r");
	char buffer[8];
    fread(&buffer, sizeof(buffer), 1, fp);
	int val = atoi(buffer);
	fclose(fp);
    count = val-10000 + 1;			// 获取已注册成功的账户数 
    

	switch(show_menu(flag))
	{
	case 1:
		if(user_register(our_users,count))
		{
			count++;
			printf("\n注册成功!");
			system("pause") ;
			system("CLS");
		}
		break;
//注册
	case 2:
		if((current_user = is_my_user(our_users,count)))
		{
			printf("\n登陆成功!");
			display_user(our_users[current_user - 1]);
			return 1; 
		}
		else
		{
			system("CLS");
			printf("\n登陆失败!");
		}
		break;
//登陆
	case 3:
		update_password(our_users,count);
		break;
//修改密码
	case 4:
		return -1;
		break;
//退出
	default:
		printf("请正确输入");
	}
}
	
