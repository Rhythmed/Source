






#define  GOOD  sizeof(struct Good)   //�궨����Ʒ��Ϣ�ṹ��ĳ��� 
#define  SHOP  sizeof(struct shop)   //�궨�������Ϣ�ṹ��ĳ��� 
#define  STAFF sizeof(struct staff)  //�궨��Ա����Ϣ�ṹ��ĳ��� 
#include "menu.h"     //�˵�ͷ�ļ� 
#include "code.h"	  //�����¼���ļ� 
#include "good.h"     //���й�����Ʒ��Ϣ�ĺ��� 
#include "shop.h"     //���й��������Ϣ�ĺ��� 
#include "staff.h"    //���й���Ա����Ϣ�ĺ��� 







int main() 
{
	system("color 0F");   //ʹ��system������������ɫ�������û������� 
	int choice;           //��¼�û��Ĺ���ѡ�� 
	int i;
	char c;
	static struct Good *goodhead=NULL; //������Ʒ��Ϣͷָ�� 
    static struct shop *shophead=NULL; //���������Ϣͷָ�� 
    static struct staff *staffhead=NULL; //����Ա����Ϣͷָ�� 
    
    
    while(1)
    { 
    	
	    choice=memu();  //�����溯������ 
	    system("cls");  //��ʱ�������������� 
	    if(choice==1) 			//�������Ա��¼���� 
	    {
	    	int codeTemp = 0;
	    	codeTemp = codeMenu(1); 
	    	if(codeTemp == -1)			// ѡ���˳� 
	    	{
				system("cls");
				printf("��Ʒ��Ϣ����ϵͳ��ӭ�ٴ�Ϊ������\n");
				system("pause");
				system("cls"); 

			} 
	    	
	    	
	    	while(codeTemp == 1)			// ��¼�ɹ� 
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
	    		
	    		
	    		

	    		i=goodmemu(); //ѡ����Ʒ������йع��� 
		 		if(i==1)  //������Ʒ��Ϣ����ģ�� 
		 		{
					system("cls");
					goodhead=Increase_good(goodhead); //����������Ʒ��Ϣ�ĺ��� 
					system("pause");  
					system("cls");    //��ʱ��������������
		 		} 
		 		
		 		if(i==2)  //�����޸���Ʒ�����Ϣģ�� 
		 		{
					system("cls");
					
		    		goodhead=add_good(goodhead);  //�����޸���Ʒ��Ϣ�ĺ��� 
		    		system("pause");
		    		system("cls");
		 		}
		 		
		 		
		 		
		 		if(i==3) //�����ѯ��Ʒ��Ϣģ�� 
		 		{
					system("cls");
					searchGood(goodhead); //���ò�ѯ��Ʒ��Ϣ�ĺ��� 
					system("cls");	
		 		}
		 		if(i==4)  //�����޸���Ʒ��Ϣģ�� 
		 		{
					system("cls");
		    		goodhead=modifygood(goodhead);  //�����޸���Ʒ��Ϣ�ĺ��� 
		    		system("pause");
		    		system("cls");
		 		}
		 		if(i==5)  //����ɾ����Ʒ��Ϣģ�� 
		 		{
					system("cls");
					goodhead=Deletegood(goodhead);  //����ɾ����Ʒ��Ϣ�ĺ��� 
					system("pause");
					system("cls");
		 		}
		 		
		 		if(i == 6)							//	�����Żݴ���� 
		 		{
		 			system("cls");
					setBargain(goodhead);
					system("cls");
				}
		 		
		 		
				if(i==7) //��ʾ��Ʒ��Ϣ��ͳ����� 
		 		{
					system("cls");
					Show_Good(goodhead); //������ʾ��Ʒ��Ϣ�ĺ��� 
					system("pause");
					system("cls");
		 		} 
		 		if(i==8)    //��ʾ��Ʒͳ����Ϣ
		 		{ 
		    		system("cls");
		 			sale_sum(goodhead);  //����ͳ����Ʒ��Ϣ�ĺ��� 
		 			system("pause"); 
					system("cls");
		 		}
		 		if(i==9)   //����Ʒ��Ϣ���浽�ļ��б��� 
		 		{
		 			system("cls");
		 			storage_good(goodhead);    //������Ʒ��Ϣ���溯�� 
		 			system("pause");
					system("cls");
		 		}
		 		if(i==10)   //���ļ��е�����Ʒ��Ϣ 
		 		{
		 			system("cls");
		 			goodhead=open_good(goodhead);  //���õ�����Ʒ��Ϣ�ĺ��� 
		 			system("pause");
					system("cls");
		 		}

		 		if(i==11)  //�����˳�ϵͳ 
		 		{
					system("cls");
					printf("��Ʒ��Ϣ����ϵͳ��ӭ�ٴ�Ϊ������\n");
					system("pause");
					system("cls"); 
					break; 
		 		} 
			}
			
			
		
  	    }
	   
	   
	   
	   	if(choice==2)  	 		//�����ϰ��¼���� 
	    {
	    	int codeTemp = 0;
	    	codeTemp = codeMenu(2); 
	    	if(codeTemp == -1)			// ѡ���˳� 
	    	{
				system("cls");
				printf("Ա���������ϵͳ��ӭ�ٴ�Ϊ������\n");
				system("pause");
				system("cls"); 
			} 
	    	while(codeTemp == 1)		// ��¼�ɹ� 
	    	{
	    		system("pause");
	    		system("cls");
	    		
	    		i=staffmemu();
				if(i==1)  //����Ա������Ϣ 
				{ 
		    		system("cls");
					staffhead=Add_staff(staffhead); //��������Ա����Ϣ�ĺ��� 
					storage_staff(staffhead);  //���ñ���Ա����Ϣ�ĺ��� 
	        		system("pause");
	        		system("cls");
				}
				if(i==2)  //����Ա��
				{
					system("cls");
		    		staffhead=Delete_staff(staffhead); //����ɾ��Ա����Ϣ�ĺ��� 
		   			storage_staff(staffhead);  //���ñ���Ա����Ϣ�ĺ��� 
	        		system("pause");
	        		system("cls");
				}
				if(i==3)  //��ʾ����Ա����Ϣ 
				{
		   			system("cls");
		   			showstaff(staffhead); //����չʾԱ����Ϣ�ĺ���
					staffhead=open_staff(staffhead); //���õ���Ա����Ϣ�ĺ��� 
		   			system("pause");
		   			system("cls");
				}
				if(i==4) //��Ʒ��Ϣչʾ 
				{
					goodhead=open_good(goodhead);  	//���õ�����Ʒ��Ϣ�ĺ��� 
					
					system("cls");
					Show_Good(goodhead); 			//������ʾ��Ʒ��Ϣ�ĺ��� 
					system("pause");
					system("cls");
				}
				if(i==5)  //��Ʒ��Ϣͳ�� 
				{
		    		system("cls");
		 			sale_sum(goodhead);  //����ͳ����Ʒ��Ϣ�ĺ��� 
		 			system("pause"); 
					system("cls");
				} 
				if(i==6)  //�鿴Ͷ����Ϣ 
				{
		    		system("cls");
		 			read_Complain();
		 			system("pause"); 
					system("cls");
				} 
				if(i==7)  //�鿴�˿ͽ��� 
				{
		    		system("cls");
		 			read_Suggestion();
		 			system("pause"); 
					system("cls");
				} 
				
				if(i==8)  //�˳� 
				{
					system("cls");
					printf("Ա������ϵͳ��ӭ�ٴ�Ϊ�������ټ�~\n"); 
					system("pause");
		    		system("cls");
					break;
				} 
			}
	    
		}	
	    	

	  	if(choice == 3)					//�˿�ϵͳ 
		{

			int codeTemp = 0;
	    	codeTemp = codeMenu(3); 
	    	if(codeTemp == -1)			// ѡ���˳� 
	    	{
				system("cls");
				printf("�������ϵͳ��ӭ�ٴ�Ϊ������\n");
				system("pause");
				system("cls"); 
			} 
			while(codeTemp == 1)
			{
				level = VIP(shophead);
				
				system("pause");
	    		system("cls");
	    		i=shopmemu(level);
				
				
				if(i==1) //�����ѯ��Ʒ��Ϣģ�� 
		 		{
		 			goodhead=open_good(goodhead);  	//���õ�����Ʒ��Ϣ�ĺ��� 
					system("cls");
					searchGood(goodhead); //���ò�ѯ��Ʒ��Ϣ�ĺ��� 
					system("cls");	
		 		}
		 		if(i == 2)
				{
					goodhead=open_good(goodhead);  	//���õ�����Ʒ��Ϣ�ĺ��� 
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
					showBargain(goodhead); 			//������ʾ��Ʒ��Ϣ�ĺ��� 
					system("pause");
					system("cls");
				}
		 		if(i == 5)
		 		{
		 			shophead = open_shop(shophead);
		 			system("cls");			 
					print_shop(shophead);			//	��ӡ������ʷ��¼ 
	
				}
				if(i == 6)
				{
					system("cls");
					valShop(shophead); 				//	�����ѹ������Ʒ 
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
				
				if(i==10)  //�˳� 
				{
					system("cls");
					printf("�������ϵͳ��ӭ�ٴ�Ϊ�������ټ�~\n"); 
					system("pause");
		    		system("cls");
					break;
				} 
				
				
				
				
				
				
			}
			
		}
	    

	while(choice==4) //�˳�ϵͳ 
	{
		system("cls");
		printf("���й���ϵͳ��ӭ�ٴ�Ϊ�������ټ�~\n"); 
		exit(0);
	}
   }
	return 0;
}
