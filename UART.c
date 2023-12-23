#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Cfg.h"

#define F_CPU 8000000
#include <util/delay.h>
/*
void UART_Frame_Sw(u8 data,u32 baudRate)
{
	u8 i=0,c=0,p=0,bit;
	u16 time_bit=1000000/baudRate;
	DIO_WritePin(PIND1,LOW);
	for(int i=0;i<time_bit;i++)
	{
		_delay_us(1);
	}
	for(i=0;i<8;i++)
	{
		bit=READ_BIT(data,i);
		DIO_WritePin(PIND1,bit);
		for(int i=0;i<time_bit;i++)
		{
			_delay_us(1);
		}
		if(bit==1)
		{
			c++;
		}
	}
	if(c%2==0)
	{
		p=0;
	}
	else
	{
		p=1;
	}
	DIO_WritePin(PIND1,p);
	for(int i=0;i<time_bit;i++)
	{
		_delay_us(1);
	}
	DIO_WritePin(PIND1,HIGH);
	
	
	
	
	
}
*/
void UART_Init(void)
{
	
	
	#if UART_MODE==UART_NORMAL_MODE
	
	
	CLR_BIT(UCSRA,U2X);//Normal mode
		
	//Baud Rate
	
	UBRRL=((u32)F_CPU/(16*(u32)UART_BAUD_RATE))-1;//9600

	#elif UART_MODE==UART_DOUBLESPEED_MODE
	
	
	SET_BIT(UCSRA,U2X);//double speed
	
	//Baud Rate
	
	UBRRL=((u32)F_CPU/(8*(u32)UART_BAUD_RATE))-1;//9600
	#endif


	
	//Transmitter Enable
	SET_BIT(UCSRB,TXEN);
	
	//Receiver Enable
	SET_BIT(UCSRB,RXEN);
	 
	//Frame (datalength - parity - stop )
	
// 	SET_BIT(UCSRC,URSEL); //UCSRC register selected
// 	
// 	CLR_BIT(UCSRC,UMSEL);//ASynchronous mode
// 	
// 	CLR_BIT(UCSRC,USBS);// 1 stop bit
// 	
// 	SET_BIT(UCSRC,UCSZ0); // 8bit selcet data length
// 	SET_BIT(UCSRC,UCSZ1);
// 	
	
	
}
//Busy wait design
void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	
	UDR=data;
	
}

u8 UART_Receive(void)
{
	u8 data;
	while(!READ_BIT(UCSRA,RXC));
	
	data=UDR;
	return data;
	
}

u8 UART_ReceivePerodic(u8*pdata)//Periodic check
{

	if(READ_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
		return 1;
	}
	else
	{
		return 0;
	}
	
	
	
	
}

void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}

/**************************** Uart Pointer to Func To be assigned to ISR **************************************/

 static void (*UART_Tx_Fptr)(void)=NULLPTR;
static void (*UART_Rx_Fptr)(void)=NULLPTR;

/**************************** Uart Interrupt functions **************************************/

void UART_Tx_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_Tx_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_Rx_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_Rx_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

/********************************* Uart Call Back functions*****************************************/

void UART_Tx_SetCallback(void(*LocalFptr)(void))
{
	UART_Tx_Fptr=LocalFptr;
}

void UART_Rx_SetCallback(void(*LocalFptr)(void))
{
	UART_Rx_Fptr=LocalFptr;
}

/*********************************Uart ISR functions*********************************************/

ISR(UART_TX_vect)
{
	if (UART_Tx_Fptr!=NULLPTR)
	{
		UART_Tx_Fptr();
	}
}

ISR(UART_RX_vect)
{
	if (UART_Rx_Fptr!=NULLPTR)
	{
		UART_Rx_Fptr();
	}
}















