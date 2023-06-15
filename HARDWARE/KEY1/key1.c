#include "KEY1.h"
#include "delay.h"
#include "sys.h"

unsigned char Y1,Y2,Y3,Y4;


void Matrix_Key_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;   
   RCC_APB2PeriphClockCmd(X1_RCC|X2_RCC|X3_RCC|X4_RCC|Y1_RCC|Y2_RCC|Y3_RCC|Y4_RCC|RCC_APB2Periph_AFIO, ENABLE);
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	
   GPIO_InitStructure.GPIO_Pin =  X1_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(X1_GPIO_PORT, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin =  X2_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(X2_GPIO_PORT, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin =  X3_GPIO_PIN ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(X3_GPIO_PORT, &GPIO_InitStructure);
	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Pin = X4_GPIO_PIN ;    
   GPIO_Init(X4_GPIO_PORT, &GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Pin =  Y1_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(Y1_GPIO_PORT, &GPIO_InitStructure);	
   
   GPIO_InitStructure.GPIO_Pin =  Y2_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(Y2_GPIO_PORT, &GPIO_InitStructure);	
   
   GPIO_InitStructure.GPIO_Pin =  Y3_GPIO_PIN ;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(Y3_GPIO_PORT, &GPIO_InitStructure);	
	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Pin = Y4_GPIO_PIN;      
   GPIO_Init(Y4_GPIO_PORT, &GPIO_InitStructure);	
	 
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOF, &GPIO_InitStructure);
}

int Matrix_Key_Scan(void)
{
	static char key_down = 0;
	uchar KeyVal = KEY_ERR;
	GPIO_SetBits(X1_GPIO_PORT,X1_GPIO_PIN);  
	GPIO_SetBits(X2_GPIO_PORT,X2_GPIO_PIN);  
	GPIO_SetBits(X3_GPIO_PORT,X3_GPIO_PIN);  
	GPIO_SetBits(X4_GPIO_PORT,X4_GPIO_PIN);  

	if ((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN)==1) || (GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y2_GPIO_PIN)==1) || (GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y3_GPIO_PIN)==1) || (GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y4_GPIO_PIN)==1))
	{
		delay_ms(10);
		if ((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN)==1) || (GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y2_GPIO_PIN)==1) || (GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y3_GPIO_PIN)==1) || (GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y4_GPIO_PIN)==1))
		{
			if (key_down == 0)
			{	
				key_down = 1;		
				
				GPIO_SetBits(X1_GPIO_PORT,X1_GPIO_PIN);
				GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
				GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
				GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);
					 
				Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);
				Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
				Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);
				Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
				
				if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
					KeyVal='A';
				if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
					KeyVal='B';
				if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
					KeyVal='C';
				if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
					KeyVal='D';
/**************************************************/		
				
				GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
				GPIO_SetBits(X2_GPIO_PORT,X2_GPIO_PIN);
				GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
				GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);
								
				Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);
				Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
				Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);
				Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
				
				if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
					KeyVal=3;
				if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
					KeyVal=6;
				if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
					KeyVal=9;
				if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
					KeyVal='#';
				
/**************************************************/
				
				GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
				GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
				GPIO_SetBits(X3_GPIO_PORT,X3_GPIO_PIN);
				GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);   

				Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);
				Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
				Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);
				Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
				
				if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
					KeyVal=2;
				if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
					KeyVal=5;
				if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
					KeyVal=8;
				if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
					KeyVal=0;	
				
/**************************************************/
				
				GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
				GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN); 
				GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN); 
				GPIO_SetBits(X4_GPIO_PORT,X4_GPIO_PIN); 
				
				Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);
				Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
				Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);
				Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
				
				if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
					KeyVal=1;
				if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
					KeyVal=4;
				if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
					KeyVal=7;
				if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
					KeyVal='*';
			}
		}
	}
	else
	{
		key_down = 0;
		KeyVal = KEY_ERR;
	}
	
	return KeyVal;
}


//void Matrix_Key_Test(void) 
//{
//    int num;
//	  num = Matrix_Key_Scan();
//	  switch(num)
//	  { 
//				case KEY_ERR:break;
//        case 0: printf("0\r\n"); break;					  				      
//				case 1: printf("1\r\n"); break;					  				       
//				case 2: printf("2\r\n"); break;					  				     
//				case 3: printf("3\r\n"); break;					  				     
//				case 4: printf("4\r\n"); break;				 	       
//				case 5: printf("5\r\n"); break;					  				      
//				case 6: printf("6\r\n"); break;					  				      
//				case 7: printf("7\r\n"); break;					 			       
//				case 8: printf("8\r\n"); break;								 		       
//				case 9: printf("9\r\n"); break;							 				     	
//        case 'A': printf("A\r\n"); break;						 				      		
//				case 'B': printf("B\r\n"); break;					 				      
//				case 'C': printf("C\r\n"); break;							 				      	
//        case 'D': printf("D\r\n"); break;							 				       	
//				case '*': printf("*\r\n"); break;					 				      
//				case '#': printf("#\r\n"); break;				 
//      }
//	
//}
