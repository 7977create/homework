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

//�����������ж���������ת���ı�־
u8 lock_flag=0;
u8 lock_Lcd_flag=0;
u8 lcd_clear_flage=0;								//���ڷ���������ʱ������
/*************************************************************************/
//��Ŀ����Ҫ���ݣ�STM32���ESP8266ģ������������ݽ���

//ESP8266�����ӣ�USART3��PB10��PB11��

//����ж����ݽ�����ȫ��
//1�������˻��з���
//2���������10ms�˶�û����һ�����ݣ�TIM7������10ms�Ķ�ʱ����
/*************************************************************************/


/*************************************************************************/
//�������������

unsigned char Password2[7]={4,1,2,4,1,2,0};//���õ����޸ĺ������������������У�Ȼ������ʵ�ʳ���Ϊ6���������һλ������������ı�־λ
unsigned char Password[6]={0,0,0,0,0,0};
#define SIZE 							sizeof(Password2)		//���鳤��
#define FLASH_SAVE_ADDR  	0X08070000//��������ĵ�ַ
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
����������޸Ĳ��洢�İ�������
*/

void change_key()
{
	
	static unsigned int i_c=0;
//	unsigned char a;
	if((key_back=='#')&&(flag_key_back1==1))//ѡ���޸�������һλ
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
	if((key_back=='D')&&(flag_key_back==1))//ѡ���޸�������һλ֮�󣬶���һλ���������޸ģ����õ��ǵ���ģʽ���ӵ��ź󷵻�0
	{
			a_c++;
		  if(a_c>9)
				a_c=0;
			Password2[i_c-1]=a_c;
			LCD_ShowChar(50+i_c*8,8,Password2[i_c-1]+'0',16,0);			
			
	}
	if(key_back==0)	//�޸�������ɺ����������
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
������������������������бȽϣ������Ƿ���ȷ
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
		if(key_back>0&&key_back<=9)			  //�������룬0-9
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
		else if((key_back=='A'))				  //������������
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
		else if((key_back=='B')&&(Password1[6]==0))				  //ȷ�ϰ�������123456/��Password1
			 {
				 if((Password[0]==1&&Password[1]==2&&Password[2]==3&&Password[3]==4&&Password[4]==5&&Password[5]==6))
						{  
							LCD_Clear(WHITE);
							LCD_ShowString(20,20,width,24,24,"AdminSuccess");							
							flag_key_back1=0;
							flag_data_key1=0;
							LCD_ShowString(60,80,width,24,24,"Open>>>>");
							Server_180_Angle();
							lcd_clear_flage=1;								//���ڷ���������ʱ������							
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
							lcd_clear_flage=1;								//���ڷ���������ʱ������						
					}
					else 
					 {
							LCD_Clear(WHITE);
						 LCD_ShowString(20,20,width,24,24,"password1ERROR");		
						 flag_key_back1=0;
						 flag_data_key1=0;
						 lcd_clear_flage=1;								//���ڷ���������ʱ������	 
					 }
			 }
			 		else if((key_back=='B')&&(Password1[6]==1))				  //ȷ�ϰ�������Password1
			 {
				 if((Password[0]==1&&Password[1]==2&&Password[2]==3&&Password[3]==4&&Password[4]==5&&Password[5]==6))
						{  
								LCD_Clear(WHITE);
								LCD_ShowString(60,30,width,24,24,"AdminSuccess");
								LCD_ShowString(60,80,width,24,24,"Open>>>>");
							  //���ת��
								Server_180_Angle();
								lcd_clear_flage=1;								//���ڷ���������ʱ������
						}
					else if(Password[0]==Password2[0]&&Password[1]==Password2[1]&&Password[2]==Password2[2]
						&&Password[3]==Password2[3]&&Password[4]==Password2[4]&&Password[5]==Password2[5])
					{
								LCD_Clear(WHITE);
								LCD_ShowString(60,30,width,24,24,"UserSuccess");
								LCD_ShowString(60,80,width,24,24,"Open>>>>");
								Server_180_Angle();			
								lcd_clear_flage=1;								//���ڷ���������ʱ������
					}
					else 
					 {
							LCD_Clear(WHITE);
							LCD_ShowString(20,30,width,24,24,"password2ERROR");
							LCD_ShowString(20,80,width,24,24,Password);
							lcd_clear_flage=1;								//���ڷ���������ʱ������

					 }
				 }
	}
}

 


/*************************************************************************/
//������

int main(void)
 {
/*************************************************************************/
/*
	 version:rfid
*/
/*************************************************************************/
//������� 
	 u8 res1=0;
	 GPIO_InitTypeDef GPIO_InitStructure;
/*************************************************************************/
//���ֳ�ʼ��
	 
		Matrix_Key_Init();												//������̳�ʼ������ 
		TIM8_PWM_Init();													//�����ʼ�� 
		LED_Init();  															//LED�˿ڳ�ʼ��
		delay_init();															//��ʱ������ʼ��
/*************************************************************************/
//ʱ��ʹ��
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//���GPIOB�˿ڵ�ʱ��ʹ�ܡ�
/*************************************************************************/
//��LED�˿����ߣ�Ϩ������LED	 

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;  					//ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 	//�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOB ,&GPIO_InitStructure); 	   				// ��ʼ��GPIO 

/*************************************************************************/
//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 		
/*************************************************************************/
//���ڡ�spi��ʼ��

	uart_init(115200);	 				
	usart2_init(115200);
	usart3_init(115200);
/*************************************************************************/
//Lcd���ڳ�ʼ��

LCD_Init();	
POINT_COLOR=BLACK;

/*************************************************************************/
//esp8266���г�ʼ��

//	esp8266_start_trans();							
//	esp8266_send_data("12",50);
//	USART3_RX_BUF[0]=0;
//	res1=USART3_RX_BUF[0];
	
/*************************************************************************/
//rc522��ʼ��

	RC522_Init();

/*************************************************************************/
//	add exti

	EXTIX_Init();											//��ʼ���ⲿ�ж�0�������
	
/*************************************************************************/
//�������

//��ȡflash�д��������ֵ
STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)Password1,SIZE);

/*************************************************************************/


/*************************************************************************/
//������
	while(1){
//	 res1=USART3_RX_BUF[0]-48;
//	 if(res1==1)
//	 {
//		 Server_180_Angle();	
//		 LCD_ShowString(200,140,210,24,24,"OPENDED");
//		 USART3_RX_BUF[0]=0;
//	 }
//	 esp8266_send_cmd("AT+CIPMODE=1","OK",200);				//͸��ģʽ�� ��ʼ�������ݵ�ָ�� ���ָ��֮��Ϳ���ֱ�ӷ�������
//	 esp8266_send_cmd("AT+CIPSEND","OK",50);	
//	
		if(lcd_clear_flage==1)
		{
			lcd_clear_flage=0;                        //����������̣�����
			LCD_Clear(WHITE);
		}
	 LCD_ShowString(10,10,210,24,24,"CQUPT 08052004");
	 LCD_ShowString(10,40,210,24,24,"2020212610");
	 LCD_ShowString(10,80,210,24,24,"2020212595");		
	 LCD_ShowString(10,120,200,24,24,"Time:2023/06/10"); 
	 LCD_ShowString(10,160,210,24,24,"DOOR SITUATION:");
	 

/*************************************************************************/
	 //�������������
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
//rfid����

	 RC522_Han();


			}
 	
 }

 
 
 

