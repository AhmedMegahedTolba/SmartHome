#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "UART_Private.h"
#include "UART_Interface.h"
#include "UART_Service_Private.h"
#include "UART_Service_Cfg.h"
#include "UART_Service_Interface.h"

#include "LCD_Inerface.h"
#include "String_Serive.h"


#define F_CPU 8000000
#include <util/delay.h>

#if UART_PARITY==UART_PARITY_EVEN

u16 UART_Frame_Sw(u8 data)//even partity
{
	u16 frame=0;
	u8 ones=0;
	frame=data<<1;//stop bit +data
	while(data)
	{
		if(READ_BIT(data,0)==1)
		{
			ones++;
		}
		data=data>>1;
	}
	if(ones%2==1)
	{
		SET_BIT(frame,9);//Parity =1;
	}
	
	SET_BIT(frame,10);
	return frame;
}

#elif UART_PARITY==UART_PARITY_ODD

u16 UART_Frame_Sw(u8 data)//odd partity
{
	u16 frame=0;
	u8 ones=0;
	frame=data<<1;//stop bit +data
	while(data)
	{
		if(READ_BIT(data,0)==1)
		{
			ones++;
		}
		data=data>>1;
	}
	if(ones%2==0)
	{
		SET_BIT(frame,9);//Parity =1;
	}
	
	SET_BIT(frame,10);
	return frame;
}
#elif UART_PARITY==UART_NOPARITY

u16 UART_Frame_Sw(u8 data)//No partity
{
	u16 frame=0;
	frame=data<<1;//start bit +data

	SET_BIT(frame,9);
	return frame;
}

#endif


void UART_Send_Sw(u16 frame,u32 baudrate)
{
	u8 i;
	u8 Frame_bit=0;
	u32 time_bit=(u32)1000000/baudrate;
	for ( i=0;i<11;i++)
	{
		//Frame_bit=READ_BIT(frame,i);
		DIO_WritePin(PIND1,READ_BIT(frame,i));
		//_delay_us(104);
		for(u8 j=0;j<time_bit;j++)
		{
			_delay_us(1);
		}
	}
	LCD_GoTO(1,0);
	LCD_WriteNum(READ_BIT(frame,i-1));
	LCD_GoTO(1,5);
	LCD_WriteNum(i);
	
	
	
}
/* block CPU */
void UART_SendString(u8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	
}
/*

void UART_ReceiveString(u8*str)//func ???? ???? string ?? 10 ????
{
	u8 i;
	for(i=0;i<10;i++)
	{
        str[i]=UART_Receive();	
	
    }
}
*/
/* block CPU */
void UART_ReceiveString(u8*str)
{
	u8 i=0,c;
	str[0]=UART_Receive();
	while(str[i]!=0xD)//0xD)//Enter in terminal
	{
		i++;
		str[i]=UART_Receive();
		
	}
	str[i]=0;
	//c=UART_Receive();//In Doclight Only
}

/* block CPU */
void UART_SendNum1(u32 num)//1450
{
	u8 data_frame;
	u8 i=0;
	
// 	LCD_GoTO(0,1);
// 	LCD_WriteNum(num);
// 	LCD_WriteString("   ");
	
	for(i=0;i<4;i++)
	{
		data_frame=(u8)num;
			
		UART_Send(data_frame);
		num>>=8;
		
	
		
	}
	
}

/* block CPU */
u32 UART_ReceiveNum1(void)
{
	u32 num=0;
	u8 b0=UART_Receive();
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	
	num=(u32)b0 | (u32)b1 << 8 | (u32)b2<< 16  |  (u32)b3 << 24  ;
	return  num;
	
}
/* block CPU */
void UART_SendNum2(u32 num)
{
	u8*p=&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
	
}

/* block CPU */
u32 UART_ReceiveNum2(void)
{
	u32 num;
	u8*p=&num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
		
	return num;
}

Endian_type Endian_Check(void)
{
	u16 x=1;
	
	if((u8)x==1) // Little Endian
	{
		return LITTLE_ENDIAN;
	}
	else         //Big Endian
	{
		return BIG_ENDIAN;
	}
}

u32 Endian_Convert_u32(u32 num)//0xFFEE5522
{
	num=(num<<24) |(num>>24) | (num<<8)&0xff0000 | (num>>8)&0xff00 ;
	//num=(num<<24) |(num>>24) | (((num<<16)>>24)<<16) | (((num>>16)<<24)>>16) ;
	return num;
}
u32 Endian_Convert_u32_2(u32 num)
{
	u8*p=&num;
	u8 temp;
	temp=p[3];
	p[3]=p[0];
	p[0]=temp;
	temp=p[2];
	p[2]=p[1];
	p[1]=temp;
	
	return num;
}


void UART_SendStringCHeckSum(u8*str)
{
	u16 sum=0;//2byte
	u8 str_len,i;
	for(i=0;str[i];i++)
	{
		sum+=str[i];
	}
	str_len=i;
	
	//send String length
	UART_Send(str_len);
	
	//Send String
	UART_SendString(str);
	
	//send checkSum
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
	
}

UART_CheckSum_type UART_ReceiveStringCHeckSum(u8*str)
{
	u16 sum_rec=0,sum_calc=0,b0,b1;
	u8 str_len,i;
	str_len=UART_Receive();
	for(i=0;i<str_len;i++)
	{
		str[i]=UART_Receive();
		sum_calc+=str[i];
	}
	str[i]=0;
	b0=UART_Receive();
	b1=UART_Receive();
	sum_rec= b0 | (b1<<8);
	
	
	
	if(sum_rec==sum_calc)
	{
		return UART_RIGHTSUM;
	}
	else
	{
		return UART_WRONGSUM;
	}
}
/*ASync func Using Interrupts */
static volatile u8*STR[20];
volatile static u8 j,flag;
volatile static u16 c;
void UART_SendStringAsynch_Queue(u8*str)
{
	
	//String_Cpy(str,STR[j+c]);
	//LCD_WriteStringGoTo(c,0,STR[j+c]);
	STR[j+c]=str;
	//LCD_WriteStringGoTo(c,0,STR[j+c]);
     c++;
    if(flag==0)
	{
		UART_Tx_SetCallback(SendString_AsynchQueue_Func);
		UART_Tx_InterruptEnable();
		UART_SendNoBlock(STR[j][0]);
		flag=1;
	}
	
	
	
}

void SendString_AsynchQueue_Func(void)
{
	static u8 i;
	i++;
	
	if(STR[j][i]!=0)
	{
		UART_SendNoBlock(STR[j][i]);
		
		
	}
	else
	{
		j++;
		c--;
		i=0;
		flag=1;
		
		if (STR[j][0]==0)
		{
			//UART_Tx_InterruptDisable();
			
		}
		
		else
		{
			UART_SendNoBlock(STR[j][0]);
		}
	}
	
	
}
static volatile u8*STR2[20];
volatile static u8 k,flag2,G;
volatile static u16 c2;
void UART_SendStringAsynch_Stack(u8*str)
{
	
	//String_Cpy(str,STR[j+c]);
	//LCD_WriteStringGoTo(c,0,STR[j+c]);
	STR2[k+c2]=str;
	G=k+c2;
	//LCD_WriteStringGoTo(c,0,STR[j+c]);
	c2++;
	if(flag2==0)
	{
		UART_Tx_SetCallback(SendString_AsynchStack_Func);
		UART_Tx_InterruptEnable();
		UART_SendNoBlock(STR2[k][0]);
		flag2=1;
	}
	
	
	
}
void SendString_AsynchStack_Func(void)
{
	static u8 i;
	i++;
	
	if(STR2[k][i]!=0)
	{
		UART_SendNoBlock(STR2[k][i]);
		
		
	}
	else
	{
		k=G;
		G--;
		c2++;
		i=0;
		flag2=1;
		if(k==0)
		{
			UART_Tx_InterruptDisable();
		}
		else if (STR2[k][0]==0)
		{
			//UART_Tx_InterruptDisable();
			
		}
	
		else
		{
			UART_SendNoBlock(STR2[k][0]);
		}
	}
	
	
}



//UART_SENDSTING Using INT BuT Not USe UART_SendNoBlock  (BCM(Basic Communication Module ))
static u8*STR3,Flag_Run=1;
void UART_SendString_Init(u8*str)
{
	UART_Tx_SetCallback(SendString_Func_Runnable);
	UART_Tx_InterruptEnable();
	STR3=str;
}
void UART_SendString_Runnable(void)
{
	static u8 i;
	if (Flag_Run==1)
	{
		UART_SendNoBlock(STR3[i]);
		i++;
		Flag_Run=0;
	}
	
}
void SendString_Func_Runnable(void)
{
	Flag_Run=1;
}

static u8 flag_st;
 volatile u8 data_write[10][50]={0},data_read[10][50]={0},flag_rec;
void UART_ReceiveString_Init(void)
{
	
		UART_Rx_SetCallback(UART_ReciveString_Func);
		UART_Rx_InterruptEnable();
		
	 
}

void UART_ReciveString_Func(void)
{
	static u8 i,j;
	if(flag_st==0)
	{
		data_write[j][0]=UART_ReceiveNoBlock();
		flag_st=1;
	}
	
	else if(data_write[j][i]!=0x0D)
	{
		i++;
		data_write[j][i]=UART_ReceiveNoBlock();
		if(data_write[j][i]==0x0D)
		{
			data_write[j][i]=0;
			
			for(i=0;data_write[j][i];i++)
			{
				data_read[j][i]=data_write[j][i];
			}
			data_read[j][i]=0;
// 			LCD_WriteStringGoTo(0,0,data_read[0]);
// 			_delay_ms(3000);
			flag_rec++;
			flag_st=0;
			j++;
			i=0;
		}
		
		
		
	}
	
	
	
	
}
UART_Status_type UART_GetRecivedStrings(u8**str)
{
	u8 i=0;
	while(i<flag_rec)
	{
		str[i]=data_read[i];
		i++;
		
	}
	if (flag_rec==0)
	{
		return UART_IN_PROGRESS;
	}
	else
	{
		return UART_FINISHED_RECEIVED;
		
	}
}

void UART_ReciveString_Runnable(void)
{
	
	
}




UART_Stack_type UART_Stack;
volatile u8 flag_full;
void UART_Stack_Fuc(void)
{
	UART_Rx_SetCallback(UART_StackPush);
	UART_Rx_InterruptEnable();

	
}

void UART_StackPush(void)
{
	if((UART_Stack.i)>=UART_STACK_NUM)
	{
		UART_ReceiveNoBlock();
		UART_Stack.flag_stack=UART_STACK_FULL;
		LCD_GoTO(0,0);
		LCD_WriteString("StackFull");
		LCD_WriteString("   ");

	
		
			
		
		
	}
	else
	{
		UART_Stack.UART_StackArr[UART_Stack.i]=UART_ReceiveNoBlock();
		(UART_Stack.i)++;
		UART_Stack.flag_stack=UART_STACK_OK;
		
	}
	
	
}

UART_StackStatus_type UART_StackPoP(u8*pdata)
{
	flag_full=0;
	if(UART_Stack.i==0)
	{
		UART_Stack.flag_stack=UART_STACK_EMPTY;
		
		
	}
	else
	{
		(UART_Stack.i)--;
		*pdata=UART_Stack.UART_StackArr[UART_Stack.i];
		UART_Stack.flag_stack=UART_STACK_OK;
	}
	return (UART_Stack.flag_stack);
	
}

UART_StackStatus_type UART_StackFlag(void)
{
	return UART_Stack.flag_stack;
}

