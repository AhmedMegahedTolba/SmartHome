

#ifndef UART_SERVICE_INTERFACE_H_
#define UART_SERVICE_INTERFACE_H_

#define UART_STACK_NUM    9
typedef enum {
	UART_STACK_OK,
	UART_STACK_FULL,
	UART_STACK_EMPTY
}UART_StackStatus_type;

typedef struct {
	 volatile u8 UART_StackArr[UART_STACK_NUM];
	 volatile u8 i;
    volatile UART_StackStatus_type flag_stack;
	}UART_Stack_type;

typedef enum {
	BIG_ENDIAN=0,
	LITTLE_ENDIAN
	}Endian_type;
	
typedef enum{
	UART_IN_PROGRESS,
	UART_FINISHED_SEND,
	UART_FINISHED_RECEIVED
	
}UART_Status_type; 	
	
typedef enum {
	UART_WRONGSUM=0,
	UART_RIGHTSUM
}UART_CheckSum_type;

u16 UART_Frame_Sw(u8 data);
void UART_Send_Sw(u16 frame,u32 baudrate);
void UART_SendString(u8*str);
void UART_ReceiveString(u8*str);
void UART_SendNum1(u32 num);
void UART_SendNum1(u32 num);
u32 UART_ReceiveNum1(void);
u32 UART_ReceiveNum2(void);

u8 Endian_Check(void);

u32 Endian_Convert_u32(u32 num);
u32 Endian_Convert_u32_2(u32 num);

void UART_SendStringCHeckSum(u8*str);
UART_CheckSum_type UART_ReceiveStringCHeckSum(u8*str);

void UART_SendStringAsynch_Queue(u8*str);
void SendString_AsynchQueue_Func(void);

void UART_SendStringAsynch_Stack(u8*str);
void SendString_AsynchStack_Func(void);

void UART_SendString_Init(u8*str);
void UART_SendString_Runnable(void);
void SendString_Func_Runnable(void);

void UART_ReceiveString_Init(void);
void UART_ReciveString_Func(void);
UART_Status_type UART_GetRecivedStrings(u8**str);

void UART_Stack_Fuc(void);
void UART_StackPush(void);
UART_StackStatus_type UART_StackPoP(u8*pdata);
UART_StackStatus_type UART_StackFlag(void);

#endif /* UART_SERVICE_INTERFACE_H_ */