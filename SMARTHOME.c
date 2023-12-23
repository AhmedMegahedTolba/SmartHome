#include "StdTypes.h"
#include "UART_Interface.h"
#include "TIMER_Service.h"
#include "RGB.h"
#include "SERVO_Interface.h"
#include "DIO_Interface.h"
#include "String_Serive.h"
#include "LCD_Inerface.h"
#include "SMARTHOME_Inerface.h"

#define F_CPU 8000000
#include <util/delay.h>

Task_type Arr_Task[10]={
	{"LEDON",SAMARTHOME_LED_On},
	{"LEDOFF",SAMARTHOME_LED_Off},
	{"LCD",SAMARTHOME_LCD_Write},
	{"RGB",SAMARTHOME_RGB},		
	
} ;

static u8 UART_Message[50];
 u8 HAL_Name[50];
 u16 HAL_value;
void SMARTHOME_Init(void)
{
	
}

void SMARTHOME_Runnable(void)
{
	u8 i=0;
	UART_ReceiveString(UART_Message);
/*	LCD_WriteStringGoTo(0,0,UART_Message);*/
	Count_HAL_Name_Val(UART_Message);
// 	LCD_GoTO(1,0);
// 	LCD_WriteString(HAL_Name);
// 	
// 	LCD_GoTO(1,10);
// 	LCD_WriteString(HAL_value);
// 	_delay_ms(5000);
	
	for(i=0;i<4;i++)
	{
		if (String_Cmpr(HAL_Name,Arr_Task[i].Name)==STRING_SAME)
		{
			Arr_Task[i].Smart_home_Fptr(HAL_value);
			
			
		}
	}
// 	LCD_WriteStringGoTo(0,0,HAL_Name);
// 	LCD_GoTO(1,0);
// 	LCD_WriteNum(HAL_value);
	
}

void Count_HAL_Name_Val(u8*str)
{
	u8 i;
	
	for(i=0;str[i]!=' ';i++)
	{
		HAL_Name[i]=str[i];
	}
	HAL_Name[i]=0;
	i++;
	HAL_value=String_To_Decimal(str+i);
	
	
}

void SAMARTHOME_LED_On(u8 led_num)
{
	switch(led_num)
	{
		case 0:
		DIO_WritePin(PINC0,HIGH);
		break;
		
		case 1:
		DIO_WritePin(PINC1,HIGH);
		break;
		
		case 2:
		DIO_WritePin(PINC2,HIGH);
		break;
		
		case 3:
		DIO_WritePin(PINC3,HIGH);
		break;
		
		case 4:
		DIO_WritePin(PINC4,HIGH);
		break;
		
		case 5:
		DIO_WritePin(PINC5,HIGH);
		break;
		
		case 6:
		DIO_WritePin(PINC6,HIGH);
		break;
		
		case 7:
		DIO_WritePin(PINC7,HIGH);
		break;
	}
}

void SAMARTHOME_LED_Off(u8 led_num)
{
	switch(led_num)
	{
		case 0:
		DIO_WritePin(PINC0,LOW);
		break;
		
		case 1:
		DIO_WritePin(PINC1,LOW);
		break;
		
		case 2:
		DIO_WritePin(PINC2,LOW);
		break;
		
		case 3:
		DIO_WritePin(PINC3,LOW);
		break;
		
		case 4:
		DIO_WritePin(PINC4,LOW);
		break;
		
		case 5:
		DIO_WritePin(PINC5,LOW);
		break;
		
		case 6:
		DIO_WritePin(PINC6,LOW);
		break;
		
		case 7:
		DIO_WritePin(PINC7,LOW);
		break;
	}
}
void SAMARTHOME_LCD_Write(u8 val)
{
	LCD_WriteNum(val);
}

void SAMARTHOME_RGB(u8 val)
{
	RGB_Color(val);
}

