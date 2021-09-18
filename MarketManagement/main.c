






#define  GOOD  sizeof(struct Good)   //宏定义商品信息结构体的长度 
#define  SHOP  sizeof(struct shop)   //宏定义店铺信息结构体的长度 
#define  STAFF sizeof(struct staff)  //宏定义员工信息结构体的长度 
#include "menu.h"     //菜单头文件 
#include "code.h"	  //密码登录类文件 
#include "good.h"     //含有管理商品信息的函数 
#include "shop.h"     //含有管理店铺信息的函数 
#include "staff.h"    //含有管理员工信息的函数 







int main() 
{
	system("color 0F");   //使用system函数调界面颜色，增加用户的体验 
	int choice;           //记录用户的功能选项 
	int i;
	char c;
	static struct Good *goodhead=NULL; //定义商品信息头指针 
    static struct shop *shophead=NULL; //定义店铺信息头指针 
    static struct staff *staffhead=NULL; //定义员工信息头指针 
    
    
    while(1)
    { 
    	
	    choice=memu();  //主界面函数调用 
	    system("cls");  //及时清屏以美化界面 
	    if(choice==1) 			//进入管理员登录界面 
	    {
	    	int codeTemp = 0;
	    	codeTemp = codeMenu(1); 
	    	if(codeTemp == -1)			// 选择退出 
	    	{
				system("cls");
				printf("商品信息管理系统欢迎再次为您服务！\n");
				system("pause");
				system("cls"); 

			} 
	    	
	    	
	    	while(codeTemp == 1)			// 登录成功 
	    	{
	    		system("pause");
	    		system("cls");
	    		
	    		
				//goodhead = open_good(goodhead);
	    		//remainAdmin(goodhead);
	    		if(beSure == 0)
	    		{
	    			goodhead = open_good(goodhead);
	    			remainAdmin(goodhead);
	    			
				}
	    		
	    		
	    		

	    		i=goodmemu(); //选择商品管理的有关功能 
		 		if(i==1)  //进入商品信息增添模块 
		 		{
					system("cls");
					goodhead=Increase_good(goodhead); //调用增加商品信息的函数 
					system("pause");  
					system("cls");    //及时清屏以美化界面
		 		} 
		 		
		 		if(i==2)  //进入修改商品库存信息模块 
		 		{
					system("cls");
					
		    		goodhead=add_good(goodhead);  //调用修改商品信息的函数 
		    		system("pause");
		    		system("cls");
		 		}
		 		
		 		
		 		
		 		if(i==3) //进入查询商品信息模块 
		 		{
					system("cls");
					searchGood(goodhead); //调用查询商品信息的函数 
					system("cls");	
		 		}
		 		if(i==4)  //进入修改商品信息模块 
		 		{
					system("cls");
		    		goodhead=modifygood(goodhead);  //调用修改商品信息的函数 
		    		system("pause");
		    		system("cls");
		 		}
		 		if(i==5)  //进入删除商品信息模块 
		 		{
					system("cls");
					goodhead=Deletegood(goodhead);  //调用删除商品信息的函数 
					system("pause");
					system("cls");
		 		}
		 		
		 		if(i == 6)							//	设置优惠促销活动 
		 		{
		 			system("cls");
					setBargain(goodhead);
					system("cls");
				}
		 		
		 		
				if(i==7) //显示商品信息和统计情况 
		 		{
					system("cls");
					Show_Good(goodhead); //调用显示商品信息的函数 
					system("pause");
					system("cls");
		 		} 
		 		if(i==8)    //显示商品统计信息
		 		{ 
		    		system("cls");
		 			sale_sum(goodhead);  //调用统计商品信息的函数 
		 			system("pause"); 
					system("cls");
		 		}
		 		if(i==9)   //将商品信息储存到文件中保存 
		 		{
		 			system("cls");
		 			storage_good(goodhead);    //调用商品信息保存函数 
		 			system("pause");
					system("cls");
		 		}
		 		if(i==10)   //从文件中导出商品信息 
		 		{
		 			system("cls");
		 			goodhead=open_good(goodhead);  //调用导出商品信息的函数 
		 			system("pause");
					system("cls");
		 		}

		 		if(i==11)  //正常退出系统 
		 		{
					system("cls");
					printf("商品信息管理系统欢迎再次为您服务！\n");
					system("pause");
					system("cls"); 
					break; 
		 		} 
			}
			
			
		
  	    }
	   
	   
	   
	   	if(choice==2)  	 		//进入老板登录界面 
	    {
	    	int codeTemp = 0;
	    	codeTemp = codeMenu(2); 
	    	if(codeTemp == -1)			// 选择退出 
	    	{
				system("cls");
				printf("员工管理管理系统欢迎再次为您服务！\n");
				system("pause");
				system("cls"); 
			} 
	    	while(codeTemp == 1)		// 登录成功 
	    	{
	    		system("pause");
	    		system("cls");
	    		
	    		i=staffmemu();
				if(i==1)  //增添员工的信息 
				{ 
		    		system("cls");
					staffhead=Add_staff(staffhead); //调用增加员工信息的函数 
					storage_staff(staffhead);  //调用保存员工信息的函数 
	        		system("pause");
	        		system("cls");
				}
				if(i==2)  //辞退员工
				{
					system("cls");
		    		staffhead=Delete_staff(staffhead); //调用删除员工信息的函数 
		   			storage_staff(staffhead);  //调用保存员工信息的函数 
	        		system("pause");
	        		system("cls");
				}
				if(i==3)  //显示所有员工信息 
				{
		   			system("cls");
		   			showstaff(staffhead); //调用展示员工信息的函数
					staffhead=open_staff(staffhead); //调用导出员工信息的函数 
		   			system("pause");
		   			system("cls");
				}
				if(i==4) //商品信息展示 
				{
					goodhead=open_good(goodhead);  	//调用导出商品信息的函数 
					
					system("cls");
					Show_Good(goodhead); 			//调用显示商品信息的函数 
					system("pause");
					system("cls");
				}
				if(i==5)  //商品信息统计 
				{
		    		system("cls");
		 			sale_sum(goodhead);  //调用统计商品信息的函数 
		 			system("pause"); 
					system("cls");
				} 
				if(i==6)  //查看投诉信息 
				{
		    		system("cls");
		 			read_Complain();
		 			system("pause"); 
					system("cls");
				} 
				if(i==7)  //查看顾客建议 
				{
		    		system("cls");
		 			read_Suggestion();
		 			system("pause"); 
					system("cls");
				} 
				
				if(i==8)  //退出 
				{
					system("cls");
					printf("员工管理系统欢迎再次为您服务，再见~\n"); 
					system("pause");
		    		system("cls");
					break;
				} 
			}
	    
		}	
	    	

	  	if(choice == 3)					//顾客系统 
		{

			int codeTemp = 0;
	    	codeTemp = codeMenu(3); 
	    	if(codeTemp == -1)			// 选择退出 
	    	{
				system("cls");
				printf("购物管理系统欢迎再次为您服务！\n");
				system("pause");
				system("cls"); 
			} 
			while(codeTemp == 1)
			{
				level = VIP(shophead);
				
				system("pause");
	    		system("cls");
	    		i=shopmemu(level);
				
				
				if(i==1) //进入查询商品信息模块 
		 		{
		 			goodhead=open_good(goodhead);  	//调用导出商品信息的函数 
					system("cls");
					searchGood(goodhead); //调用查询商品信息的函数 
					system("cls");	
		 		}
		 		if(i == 2)
				{
					goodhead=open_good(goodhead);  	//调用导出商品信息的函数 
					system("cls");
					shophead = purchase(shophead,goodhead);		
					save_shop(shophead);
					system("cls");	
				}
		 		if(i == 3)
		 		{
		 			system("cls");
					shophead = modifyshop(shophead,goodhead);	
					save_shop(shophead);
					system("cls");	
				}
				if(i == 4) 
		 		{
		 			goodhead=open_good(goodhead);
					
					system("cls");
					showBargain(goodhead); 			//调用显示商品信息的函数 
					system("pause");
					system("cls");
				}
		 		if(i == 5)
		 		{
		 			shophead = open_shop(shophead);
		 			system("cls");			 
					print_shop(shophead);			//	打印消费历史记录 
	
				}
				if(i == 6)
				{
					system("cls");
					valShop(shophead); 				//	评价已购买的商品 
					system("pause");
					system("cls");
				}
				if(i == 7)
				{
					system("cls");
					complain();
					system("cls");
				}
				if(i == 8) 
				{
					system("cls");
					suggest(); 
					system("cls");
				}
				
				if(i == 9)
				{
					system("cls");
					shophead = open_shop(shophead);
					buy_sum(shophead);
					system("pause");
					system("cls");
				}
				
				if(i==10)  //退出 
				{
					system("cls");
					printf("购物管理系统欢迎再次为您服务，再见~\n"); 
					system("pause");
		    		system("cls");
					break;
				} 
				
				
				
				
				
				
			}
			
		}
	    

	while(choice==4) //退出系统 
	{
		system("cls");
		printf("超市管理系统欢迎再次为您服务，再见~\n"); 
		exit(0);
	}
   }
	return 0;
}
