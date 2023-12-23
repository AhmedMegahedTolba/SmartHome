
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "TIMER_Interface.h"
#include "TIMER_Service.h"
#include "DIO_Interface.h"
#include "LCD_Inerface.h"

#define F_CPU 8000000
#include <util/delay.h>

volatile static u8 flag=0;
u16 T1,T2,T3,t;
u16 c,count;
void (*TIMER2_Fptr)(void);


void PWM_Init(void)
{
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	TIMER0_OC0mode(OC0_CLEAR_ON_COMPAREMATCH);
	TIMER1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	TIMER1_OC1AMode(OCRA_CLEAR_ON_COMPAREMATCH);
	TIMER1_OC1BMode(OCRB_CLEAR_ON_COMPAREMATCH);
// 	PWM_Duty(10,TIMER1_PINB);
// 	PWM_Duty(20,TIMER1_PINA);
// 	PWM_Duty(30,TIMER0_PIN0);
}

void PWM_Freq_HZ(u16 freq)
{
	u16 Ttot=0;
	if(freq==0);
	else
	{
		Ttot=((u32)1000000/freq);
		if(Ttot>=1)
		{
			ICR1=Ttot-1;
		}
		else
		{
			ICR1=0;
		}
	}
	
}
void PWM_Freq_KHZ(u16 freq)
{
	u16 Ttot=0;
	if(freq==0);
	else
	{
		Ttot=(1000/freq);
		if(Ttot>=1)
		{
			ICR1=Ttot-1;
		}
		else
		{
			ICR1=0;
		}
	}
	
}
/*
void PWM_Duty(u16 duty)
{
	u16 Ton=0;
	if(duty<=100)
	{
		Ton=((u32)duty*(ICR1+1))/100;
		if(Ton>1)
		{
			OCR1A=Ton-1;
		}
		else
		{
			OCR1A=0;
		}
	}
}
*/

void PWM_Duty(u16 duty,TIMER_Pin_type pin) //clear in compare match
{
	u16 Ton=0;
	switch(pin)
	{
		case TIMER0_PIN0 :
		if(duty<=100)
		{
			Ton=((u32)duty*(256))/100;
			if(Ton>1)
			{
				OCR0=Ton-1;
			}
			else
			{
				OCR0=0;
			}
			
		}
		
		break;
		
		case TIMER1_PINA :
		if(duty<=100)
		{
			Ton=((u32)duty*(ICR1+1))/100;
			if(Ton>1)
			{
				OCR1A=Ton-1;
			}
			else
			{
				OCR1A=0;
			}
		}
		 
		break;
		
		case TIMER1_PINB :
		if(duty<=100)
		{
			Ton=((u32)duty*(ICR1+1))/100;
			if(Ton>1)
			{
				OCR1B=Ton-1;
			}
			else
			{
				OCR1B=0;
			}
		} 
		  
		 
		
		break;
		
	}

	
	
	
}

/*
void PWM_Duty(u16 duty,TIMER_Pin_type pin)//set on compare match
{
	u16 Ton=0;
	duty=100-duty;
	
	LCD_WriteString(" ");
	switch(pin)
	{
		case TIMER0_PIN0 :
		if(duty<=100)
		{
			Ton=((u32)duty*(256))/100;
			if(Ton>1)
			{
				OCR0=Ton-1;
			}
			else
			{
				OCR0=0;
			}
			
		}
		
		break;
		
		case TIMER1_PINA :
		if(duty<=100)
		{
			Ton=((u32)duty*(ICR1+1))/100;
			if(Ton>1)
			{
				OCR1A=Ton-1;
			}
			else
			{
				OCR1A=0;
			}
		}
		
		break;
		
		case TIMER1_PINB :
		if(duty<=100)
		{
			Ton=((u32)duty*(ICR1+1))/100;
			if(Ton>1)
			{
				OCR1B=Ton-1;
			}
			else
			{
				OCR1B=0;
			}
		}
		
		
		
		break;
		
	}

	
	
	
}
*/
//0 - 65 (ms)
void TIMER1_SetInterruptTime_ms(u16 time,void(*local_fptr)(void))
{
	if(time<=65)
	{
		OCR1A=time*1000-1;
		TIMER1_OCA_SetCallBack(local_fptr);
		TIMER1_OCA_InterruptEnable();

	}
	
	
}
//0-65536
void TIMER1_SetInterruptTime_us(u16 time,void(*local_fptr)(void))
{
	if(time<=65536)
	{
		OCR1A=time-1;
		TIMER1_OCA_SetCallBack(local_fptr);
		TIMER1_OCA_InterruptEnable();

	}
	
	
}

void TIMER1_SetInterruptTime_ms2(u16 time,void(*local_fptr)(void))
{
	if(time<=8388)
	{
		
		OCR1A=((((u32)time*1000)+64)/128)-1;
		TIMER1_OCA_SetCallBack(local_fptr);
		TIMER1_OCA_InterruptEnable();

	}
	
	
}
void TIMER2_SetInterruptTime_ms(u16 time,void(*local_fptr)(void))
{
	
		
		OCR2=99;
		count=((u32)time*1000)/(OCR2+1);
		c=0;
		TIMER2_Fptr=local_fptr;
		TIMER2_OC_SetCallBack(TIMER2_FuncTime);
		TIMER2_OC_InterruptEnable();
		

	
	
	
}
u8 PWM_Measure(u32*Pfreq,u8*Pduty,u32 timeout)//timeout(ms)
{
	u16 Ton,Toff;
	u32 c;
	TCNT1=0;
	TIMER1_ICU_SetCallBack(Func_ICU);
	TIMER1_InputCaptureEdge(RISING);
	TIMER1_ICU_InterruptEnable();
	flag=0;
	while((flag<3)&&(c<(timeout*1000)))
	{
		c++;
		_delay_us(1);
	}
	if(flag==3)
	{
		Ton=T2-T1;
		Toff=T3-T2;
		*Pfreq=((u32)1000000)/((u32)Ton+Toff);
		*Pduty=((u32)Ton*100)/((u32)Ton+Toff);
		
	}
	else
	{
		*Pfreq=0;
		if(DIO_ReadPin(PIND6)==LOW)
		{
			*Pduty=0;
		}
		else
		{
			*Pduty=100;
			
		}
	}
	
}

static void Func_ICU(void)
{
	if(flag==0)
	{
		T1=ICR1;
		TIMER1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if(flag==1)
	{
		T2=ICR1;
		TIMER1_InputCaptureEdge(RISING);
		flag=2;
	}
	else if(flag==2)
	{
		T3=ICR1;
		TIMER1_ICU_InterruptDisable();
		flag=3;
	}
}

void TIMER2_FuncTime(void)
{
	c++;
	if(c==count)
	{
		c=0;
		TIMER2_Fptr();
		
	}
	
}

