#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "usart2.h"
#include "usart3.h"
#include "esp8266.h"
#include "string.h"
#include "timer.h"
#include "tft.h"
#include "led.h"
#include "rc522.h"
#include "server.h"
#include "exti.h"
#include "flash.h"
#include "KEY1.h"

//用于密码锁中断与主程序转换的标志
u8 lock_flag=0;
u8 lock_Lcd_flag=0;
u8 lcd_clear_flage=0;								//用于返回主函数时，清屏
/*************************************************************************/
//项目的主要内容：STM32配合ESP8266模块与服务器数据交互

//ESP8266的连接：USART3（PB10、PB11）

//如何判断数据接收完全？
//1、出现了换行符；
//2、如果超过10ms了都没有下一条数据（TIM7来进行10ms的定时）。
/*************************************************************************/


/*************************************************************************/
//密码锁相关配置

unsigned char Password2[7]={4,1,2,4,1,2,0};//设置的是修改后密码放入在这个数组中，然后密码实际长度为6，数组最后一位是输入新密码的标志位
unsigned char Password[6]={0,0,0,0,0,0};
#define SIZE 							sizeof(Password2)		//数组长度
#define FLASH_SAVE_ADDR  	0X08070000//储存密码的地址
#define FLASH_SAVE_ADDR1  0X08020000
#define width     				240
#define size							16
u8 flag=0;

unsigned char Password1[7]={1,1,1,1,1,1,0};;
unsigned char Password_count=0; 
unsigned int a_c,b_c,c_c,d_c;
unsigned char key_back;
unsigned char flag_key_back=0,flag_key_back1=0;
u16 flag_key_data=0;
u16* flag_key=&flag_key_data;
/*
对密码进行修改并存储的按键函数
*/

void change_key()
{
	
	static unsigned int i_c=0;
//	unsigned char a;
	if((key_back=='#')&&(flag_key_back1==1))//选择修改密码哪一位
	{
		a_c=Password[i_c];
		i_c++;
		if(i_c==7)
		{
			i_c=1;
			
		}

		LCD_ShowChar(50+i_c*8,8,13+' ',size,0);
		
		if(i_c>1)
		{

		LCD_ShowChar(50+(i_c-1)*8,8,10+' ',size,0);		
			
		}
		flag_key_back=1;
	}
	if((key_back=='D')&&(flag_key_back==1))//选择修改密码哪一位之后，对这一位进行密码修改，采用的是递增模式，加到九后返回0
	{
			a_c++;
		  if(a_c>9)
				a_c=0;
			Password2[i_c-1]=a_c;
			LCD_ShowChar(50+i_c*8,8,Password2[i_c-1]+'0',16,0);			
			
	}
	if(key_back==0)	//修改密码完成后按下零键导入
  { 
			LCD_Clear(WHITE);
			Password2[6]=1;
		  delay_ms(10);
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)Password2,SIZE);

			LCD_ShowString(0,0,width,24,24,">");
		  delay_ms(100);
			LCD_ShowString(0,0,width,24,24,">>");
		  delay_ms(100);
			LCD_ShowString(0,0,width,24,24,">>>");
		  delay_ms(100);
			LCD_ShowString(0,0,width,24,24,">>>>");
		  delay_ms(100);
			LCD_ShowString(0,0,width,24,24,">>>>>");
		  delay_ms(100);
			LCD_ShowString(0,0,width,24,24,">>>>>>");
		  delay_ms(100);
			LCD_ShowString(0,0,width,24,24,">>>>>>>");
		  delay_ms(100);
			LCD_ShowString(0,0,width,24,24,">>>>>>>>");
		  delay_ms(100);
			
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)Password1,SIZE);
			
			LCD_ShowString(25,25,width,12,12,"Suscess!");
			delay_ms(50);
			LCD_ShowString(25,25,width,16,16,"Suscess!");
			delay_ms(50);
			LCD_ShowString(25,25,width,24,24,"Suscess!");
			delay_ms(50);			
			

	}
}
/*
按键处理函数，对输入密码进行比较，看看是否正确
*/

void data_key()
{
	 unsigned char i;
	 unsigned char flag_data_key1=0;

		i=' ';

	if(key_back=='C')
	{
			LCD_Clear(WHITE);
			LCD_ShowString(0,8,width,16,16,"input:");
		
		flag=1;
    Password_count=0;
		flag_key_back=0;
		flag_key_back1=1;
		flag_data_key1=1;


	}
	if(flag==1)
	{
		if(key_back>0&&key_back<=9)			  //输入密码，0-9
		    {
			   if(Password_count<6) 
			    {
				   Password[Password_count]=key_back;
				   Password_count++;
					 if(Password_count==1)
					 {

						 
							LCD_ShowChar(50+Password_count*8,8,10+i,size,0);
							LCD_ShowChar(58+Password_count*8,8,13+i,size,0);
					 }
					 if(Password_count==2)
					 {

							LCD_ShowChar(50+Password_count*8,8,10+i,size,0);
							LCD_ShowChar(58+Password_count*8,8,13+i,size,0);						 
					 }
					 if(Password_count==3)
					 {

							LCD_ShowChar(50+Password_count*8,8,10+i,size,0);
							LCD_ShowChar(58+Password_count*8,8,13+i,size,0);						 
					 }
					 if(Password_count==4)
					 {

							LCD_ShowChar(50+Password_count*8,8,10+i,size,0);
							LCD_ShowChar(58+Password_count*8,8,13+i,size,0);						 

					 }
					 if(Password_count==5)
					 {

							LCD_ShowChar(50+Password_count*8,8,10+i,size,0);
							LCD_ShowChar(58+Password_count*8,8,13+i,size,0);						 
					 }
					 if(Password_count==6)
					 {

							LCD_ShowChar(50+Password_count*8,8,10+i,size,0);
							LCD_ShowChar(58+Password_count*8,8,13+i,size,0);						 
					 }
				  }
			  }
		else if((key_back=='A'))				  //撤销按键按下
			 {
			   	if(Password_count>0) Password_count--;
				 if(Password_count==0)
					 {

						LCD_ShowChar(58+Password_count*8,8,13+i,size,0);
						LCD_ShowChar(58+(Password_count+1)*8,8,i,size,0);						 
					 }
					 if(Password_count==1)
					 {

						LCD_ShowChar(58+Password_count*8,8,13+i,size,0);
						LCD_ShowChar(58+(Password_count+1)*8,8,i,size,0);						 
					 }
					 if(Password_count==2)
					 {

						LCD_ShowChar(58+Password_count*8,8,13+i,size,0);
						LCD_ShowChar(58+(Password_count+1)*8,8,i,size,0);						 
					 }
					 if(Password_count==3)
					 {

						LCD_ShowChar(58+Password_count*8,8,13+i,size,0);
						LCD_ShowChar(58+(Password_count+1)*8,8,i,size,0);						 

					 }
					 if(Password_count==4)
					 {

						LCD_ShowChar(58+Password_count*8,8,13+i,size,0);
						LCD_ShowChar(58+(Password_count+1)*8,8,i,size,0);						 
					 }
					 if(Password_count==5)
					 {

						LCD_ShowChar(58+Password_count*8,8,13+i,size,0);
						LCD_ShowChar(58+(Password_count+1)*8,8,i,size,0);						 
					 }
				  
			 }	
		else if((key_back=='B')&&(Password1[6]==0))				  //确认按键密码123456/密Password1
			 {
				 if((Password[0]==1&&Password[1]==2&&Password[2]==3&&Password[3]==4&&Password[4]==5&&Password[5]==6))
						{  
							LCD_Clear(WHITE);
							LCD_ShowString(20,20,width,24,24,"AdminSuccess");							
							flag_key_back1=0;
							flag_data_key1=0;
							LCD_ShowString(60,80,width,24,24,"Open>>>>");
							Server_180_Angle();
							lcd_clear_flage=1;								//用于返回主函数时，清屏							
						}
					else if(
					 (Password[0]==Password1[0]&&Password[1]==Password1[1]&&Password[2]==Password1[2]
						&&Password[3]==Password1[3]&&Password[4]==Password1[4]&&Password[5]==Password1[5]))
					{
							LCD_Clear(WHITE);
							LCD_ShowString(60,30,width,24,24,"UserSuccess");
							flag_key_back1=0;
							flag_data_key1=0;
							LCD_ShowString(60,80,width,24,24,"Open>>>>");
							Server_180_Angle();	
							lcd_clear_flage=1;								//用于返回主函数时，清屏						
					}
					else 
					 {
							LCD_Clear(WHITE);
						 LCD_ShowString(20,20,width,24,24,"password1ERROR");		
						 flag_key_back1=0;
						 flag_data_key1=0;
						 lcd_clear_flage=1;								//用于返回主函数时，清屏	 
					 }
			 }
			 		else if((key_back=='B')&&(Password1[6]==1))				  //确认按键密码Password1
			 {
				 if((Password[0]==1&&Password[1]==2&&Password[2]==3&&Password[3]==4&&Password[4]==5&&Password[5]==6))
						{  
								LCD_Clear(WHITE);
								LCD_ShowString(60,30,width,24,24,"AdminSuccess");
								LCD_ShowString(60,80,width,24,24,"Open>>>>");
							  //舵机转动
								Server_180_Angle();
								lcd_clear_flage=1;								//用于返回主函数时，清屏
						}
					else if(Password[0]==Password2[0]&&Password[1]==Password2[1]&&Password[2]==Password2[2]
						&&Password[3]==Password2[3]&&Password[4]==Password2[4]&&Password[5]==Password2[5])
					{
								LCD_Clear(WHITE);
								LCD_ShowString(60,30,width,24,24,"UserSuccess");
								LCD_ShowString(60,80,width,24,24,"Open>>>>");
								Server_180_Angle();			
								lcd_clear_flage=1;								//用于返回主函数时，清屏
					}
					else 
					 {
							LCD_Clear(WHITE);
							LCD_ShowString(20,30,width,24,24,"password2ERROR");
							LCD_ShowString(20,80,width,24,24,Password);
							lcd_clear_flage=1;								//用于返回主函数时，清屏

					 }
				 }
	}
}

 


/*************************************************************************/
//主函数

int main(void)
 {
/*************************************************************************/
/*
	 version:rfid
*/
/*************************************************************************/
//定义变量 
	 u8 res1=0;
	 GPIO_InitTypeDef GPIO_InitStructure;
/*************************************************************************/
//各种初始化
	 
		Matrix_Key_Init();												//密码键盘初始化配置 
		TIM8_PWM_Init();													//舵机初始化 
		LED_Init();  															//LED端口初始化
		delay_init();															//延时函数初始化
/*************************************************************************/
//时钟使能
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//完成GPIOB端口的时钟使能。
/*************************************************************************/
//将LED端口拉高，熄灭所有LED	 

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;  					//选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 	//设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB ,&GPIO_InitStructure); 	   				// 初始化GPIO 

/*************************************************************************/
//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 		
/*************************************************************************/
//串口、spi初始化

	uart_init(115200);	 				
	usart2_init(115200);
	usart3_init(115200);
/*************************************************************************/
//Lcd串口初始化

LCD_Init();	
POINT_COLOR=BLACK;

/*************************************************************************/
//esp8266进行初始化

//	esp8266_start_trans();							
//	esp8266_send_data("12",50);
//	USART3_RX_BUF[0]=0;
//	res1=USART3_RX_BUF[0];
	
/*************************************************************************/
//rc522初始化

	RC522_Init();

/*************************************************************************/
//	add exti

	EXTIX_Init();											//初始化外部中断0服务程序
	
/*************************************************************************/
//密码键盘

//读取flash中存入的密码值
STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)Password1,SIZE);

/*************************************************************************/


/*************************************************************************/
//主函数
	while(1){
//	 res1=USART3_RX_BUF[0]-48;
//	 if(res1==1)
//	 {
//		 Server_180_Angle();	
//		 LCD_ShowString(200,140,210,24,24,"OPENDED");
//		 USART3_RX_BUF[0]=0;
//	 }
//	 esp8266_send_cmd("AT+CIPMODE=1","OK",200);				//透传模式下 开始发送数据的指令 这个指令之后就可以直接发数据了
//	 esp8266_send_cmd("AT+CIPSEND","OK",50);	
//	
		if(lcd_clear_flage==1)
		{
			lcd_clear_flage=0;                        //跳出密码键盘，清屏
			LCD_Clear(WHITE);
		}
	 LCD_ShowString(10,10,210,24,24,"CQUPT 08052004");
	 LCD_ShowString(10,40,210,24,24,"2020212610");
	 LCD_ShowString(10,80,210,24,24,"2020212595");		
	 LCD_ShowString(10,120,200,24,24,"Time:2023/06/10"); 
	 LCD_ShowString(10,160,210,24,24,"DOOR SITUATION:");
	 

/*************************************************************************/
	 //密码键盘主函数
while(lock_flag) 
{
	if(lock_Lcd_flag)
	{			
		LCD_Clear(WHITE);
		LCD_ShowString(0,0,width,16,16," ----------------- ");   
		LCD_ShowString(20,16,width,24,24, "Welecome");  
		LCD_ShowString(25,46,width,16,16,"MY HOST");  
		lock_Lcd_flag=0;
		delay_ms(1000);
		
		STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)Password2,SIZE);//
		STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)Password1,SIZE);//
		LCD_ShowString(25,66,width,16,16,"flash readed");  //
	}
	key_back=Matrix_Key_Scan();
	data_key();
	change_key();
}	 
/*************************************************************************/
//rfid函数

	 RC522_Han();


			}
 	
 }

 
 
 

