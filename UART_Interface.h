
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_Init(void);

//busy wait
void UART_Send(u8 data);
u8 UART_Receive(void);
u8 UART_ReceivePerodic(u8*pdata);

void UART_Tx_InterruptEnable(void);
void UART_Tx_InterruptDisable(void);
void UART_Rx_InterruptEnable(void);
void UART_Tx_InterruptDisable(void);

void UART_Tx_SetCallback(void(*LocalFptr)(void));
void UART_Rx_SetCallback(void(*LocalFptr)(void));

void UART_SendNoBlock(u8 data);
u8 UART_ReceiveNoBlock(void);









#endif /* UART_INTERFACE_H_ */