

#ifndef TIMER_SERVICE_H_
#define TIMER_SERVICE_H_
typedef enum{
	TIMER0_PIN0,
	TIMER1_PINA,
	TIMER1_PINB
	
	}TIMER_Pin_type;
void PWM_Init(void);
void PWM_Freq_HZ(u16 freq);
void PWM_Freq_KHZ(u16 freq);
//void PWM_Duty(u16 duty);
void PWM_Duty(u16 duty,TIMER_Pin_type pin);
static void Func_ICU(void);
u8 PWM_Measure(u32*Pfreq,u8*Pduty,u32 timepout);
void TIMER1_SetInterruptTime_ms(u16 time,void(*local_fptr)(void));
void TIMER1_SetInterruptTime_us(u16 time,void(*local_fptr)(void));

void TIMER2_SetInterruptTime_ms(u16 time,void(*local_fptr)(void));
void TIMER2_FuncTime(void);



#endif /* TIMER_SERVICE_H_ */