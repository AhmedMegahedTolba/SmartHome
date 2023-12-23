#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "TIMER_Interface.h"
#include "SERVO_Cfg.h"
#include "SERVO_Interface.h"
#include "DIO_Interface.h"
#include "LCD_Inerface.h"

static u32 Con,Coff;
void SERVO_Init(void)
{
  TIMER1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
  TIMER1_OC1AMode(OCRA_CLEAR_ON_COMPAREMATCH);
  ICR1=19999;//Tot=20000(50Hz)
  
  
  
  	
}

void SERVO_SetPos(u8 pos)
{
	if(pos>180)
	{
		pos=180;
	}
	SERVO_PWM_REG=((((u32)pos*1000)+90)/180)+999;//Proteus(1000-2000)
	//OCR1A=((((u32)pos*2000)+90)/180)+499;//real(500-2500)
}

void SERVO_SetPos2(u8 pos)
{
	u32 Ton,Toff;
	if(pos>180)
	{
		pos=180;
	}
	Ton=((((u32)pos*1000)+90)/180)+1000;//Proteus(1000-2000);
	Toff=20000-Ton;
	TIMER2_OVF_InterruptEnable();
	TIMER2_OVF_SetCallBack(Func_Servo2);
	Con=Ton/50;
	Coff=Toff/50;
	
	
	
	
}

void Func_Servo2(void)
{
	static u32 c;
	c++;
	
	if(c==Con)
	{
		DIO_WritePin(PINB0,LOW);
		
	}
	if(c==(Coff+Con))
	{
		DIO_WritePin(PINB0,HIGH);
		c=0;
	}
	
	
	
}