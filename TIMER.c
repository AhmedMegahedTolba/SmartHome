#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "TIMER_Interface.h"
#include "LCD_Inerface.h"

/*************************Pointer to functions to be assigned to ISR*********************************/
static void(*TIMER0_OVF_Fptr)(void)=NULLPTR;
static void(*TIMER0_OC_Fptr)(void)=NULLPTR;

/* Timer 0  func*/
void TIMER0_Init(TIMER0_Mode_type mode,TIMER0_Scaler_type scaler)
{
	switch(mode)
	{
		case TIMER0_NORMAL_MODE :
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		
		case TIMER0_PHASECORRECT_MODE :
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		
		case TIMER0_CTC_MODE :
		SET_BIT(TCCR0,WGM01);
		CLR_BIT(TCCR0,WGM00);
		break;
		
		case TIMER0_FASTPWM_MODE :
		SET_BIT(TCCR0,WGM01);
		SET_BIT(TCCR0,WGM00);
		break;
		
	}
	//scaler
	TCCR0&=0xF8;//0b11111000
	TCCR0|=scaler;
	
}

void TIMER0_OC0mode(TIMER0_OC0_Mode_type mode)
{
	switch(mode)
	{
		case OC0_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		
		case OC0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		
		case OC0_CLEAR_ON_COMPAREMATCH://Non Inverting
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		
		case OC0_SET_ON_COMPAREMATCH://Inverting
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		
	}
}
/****************************Timer 0 Interrupt functions**************************************/
void TIMER0_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_OVF_InterrupDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void TIMER0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
}
void TIMER0_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}

/*********************************Timer 0 Call Back functions*****************************************/

void TIMER0_OVF_SetCallBack(void(*local_fptr)(void))
{
	TIMER0_OVF_Fptr=local_fptr;
}

void TIMER0_OC_SetCallBack(void(*local_fptr)(void))
{
	TIMER0_OC_Fptr=local_fptr;
}
/*********************************Timer 0 ISR functions*********************************************/

ISR(TIMER0_OVF_vect)
{
	if(TIMER0_OVF_Fptr!=NULLPTR)
	{
		TIMER0_OVF_Fptr();
	}
}

ISR(TIMER0_OC_vect)
{
	if(TIMER0_OC_Fptr!=NULLPTR)
	{
		TIMER0_OC_Fptr();
	}
}


/********************************************************************************************************************/
/*************************Pointer to functions to be assigned to ISR*********************************/

static void (*TIMER1_OVF_Fptr) (void)=NULLPTR;
static void (*TIMER1_OCA_Fptr) (void)=NULLPTR;
static void (*TIMER1_OCB_Fptr) (void)=NULLPTR;
static void (*TIMER1_ICU_Fptr) (void)=NULLPTR;

/* Timer 1 funcs */

void TIMER1_Init( TIMER1_Mode_type mode,TIMER1_Scaler_type scaler)
{
		switch (mode)
		{
			case TIMER1_NORMAL_MODE:
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			case TIMER1_CTC_ICR_TOP_MODE:
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
			
			case TIMER1_CTC_OCRA_TOP_MODE:
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			break;
			
			case TIMER1_FASTPWM_ICR_TOP_MODE:
			CLR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
			
			case TIMER1_FASTPWM_OCRA_TOP_MODE:
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
		}

		TCCR1B&=0XF8;
		TCCR1B|=scaler;
}

void TIMER1_OC1AMode(OC1A_Mode_type oc1a_mode)
{
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_CLEAR_ON_COMPAREMATCH://Non Inverting
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_SET_ON_COMPAREMATCH://Inverting
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}

}
void TIMER1_OC1BMode(OC1B_Mode_type oc1b_mode)
{
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRA_CLEAR_ON_COMPAREMATCH://Non Inverting
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case OCRA_SET_ON_COMPAREMATCH://Inverting
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}
void TIMER1_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	SET_BIT(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	CLR_BIT(TCCR1B,ICES1);
}
/****************************Timer 1 Interrupt functions**************************************/
void TIMER1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void TIMER1_OVF_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE1);
}
void TIMER1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
	
}
void TIMER1_OCA_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1A);
}
void TIMER1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
	
}
void TIMER1_OCB_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1B);
}
void TIMER1_ICU_InterruptEnable(void)
{
		SET_BIT(TIMSK,TICIE1);
}
void TIMER1_ICU_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TICIE1);
}

/*********************************Timer 1 Call Back functions*****************************************/

void TIMER1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	TIMER1_OVF_Fptr=LocalFptr;
}
void TIMER1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	TIMER1_OCA_Fptr=LocalFptr;
		
}
void TIMER1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	TIMER1_OCB_Fptr=LocalFptr;
}
void TIMER1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	TIMER1_ICU_Fptr=LocalFptr;
}

/*********************************Timer 1 ISR functions*********************************************/
ISR(TIMER1_OVF_vect)
{
	if(TIMER1_OVF_Fptr!=NULLPTR)
	{
		TIMER1_OVF_Fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(TIMER1_OCA_Fptr!=NULLPTR)
	{
		TIMER1_OCA_Fptr();
	}

	
}
ISR(TIMER1_OCB_vect)
{
	if(TIMER1_OCB_Fptr!=NULLPTR)
	{
		TIMER1_OCB_Fptr();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(TIMER1_ICU_Fptr!=NULLPTR)
	{
		TIMER1_ICU_Fptr();
	}
}


/*****************************************************************************************************************/

/* Timer 2 */

/*************************Pointer to functions to be assigned to ISR*********************************/
static void(*TIMER2_OVF_Fptr)(void)=NULLPTR;
static void(*TIMER2_OC_Fptr)(void)=NULLPTR;

/* Timer 2  func*/
void TIMER2_Init(TIMER2_Mode_type mode,TIMER2_Scaler_type scaler)
{
	switch(mode)
	{
		case TIMER2_NORMAL_MODE :
		CLR_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		
		case TIMER2_PHASECORRECT_MODE :
		SET_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		
		case TIMER2_CTC_MODE :
		SET_BIT(TCCR2,WGM21);
		CLR_BIT(TCCR2,WGM20);
		break;
		
		case TIMER2_FASTPWM_MODE :
		SET_BIT(TCCR2,WGM21);
		SET_BIT(TCCR2,WGM20);
		break;
		
	}
	//scaler
	TCCR2&=0xF8;//0b11111000
	TCCR2|=scaler;
	
}

void TIMER2_OC2mode(TIMER2_OC2_Mode_type mode)
{
	switch(mode)
	{
		case OC2_DISCONNECTED:
		CLR_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		
		case OC2_TOGGLE:
		SET_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		
		case OC2_CLEAR_ON_COMPAREMATCH://Non Inverting
		CLR_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
		
		case OC2_SET_ON_COMPAREMATCH://Inverting
		SET_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
		
	}
}
/****************************Timer 2 Interrupt functions**************************************/
void TIMER2_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE2);
}
void TIMER2_OVF_InterrupDisable(void)
{
	CLR_BIT(TIMSK,TOIE2);
}
void TIMER2_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE2);
}
void TIMER2_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE2);
}

/*********************************Timer 2 Call Back functions*****************************************/

void TIMER2_OVF_SetCallBack(void(*local_fptr)(void))
{
	TIMER2_OVF_Fptr=local_fptr;
}

void TIMER2_OC_SetCallBack(void(*local_fptr)(void))
{
	TIMER2_OC_Fptr=local_fptr;
}
/*********************************Timer 2 ISR functions*********************************************/

ISR(TIMER2_OVF_vect)
{
	if(TIMER2_OVF_Fptr!=NULLPTR)
	{
		TIMER2_OVF_Fptr();
	}
}

ISR(TIMER2_OC_vect)
{
	if(TIMER2_OC_Fptr!=NULLPTR)
	{
		TIMER2_OC_Fptr();
	}
}

