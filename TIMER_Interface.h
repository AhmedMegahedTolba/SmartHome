


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/* Timer 0 */
#define TIMER0_WRITE(x) (TCNT0=(u8)x)
#define TIMER0_READ1() (TCNT0)
#define TIMER0_READ2(x) (*(u8*)x=TCNT0)

#define TIMER0_OUTPUT_COMPARE_WRITE(x) (OCR0=(u8)x)
#define TIMER0_OUTPUT_COMPARE_READ1() (OCR0)
#define TIMER0_OUTPUT_COMPARE_READ2(x) (*(u8*)x=OCR0)

typedef enum{
	
	TIMER0_STOP,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNAL_FALLING,
	EXTERNAL_RISING
	}TIMER0_Scaler_type;

typedef enum{
	
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE
	}TIMER0_Mode_type;

typedef enum{
	OC0_DISCONNECTED=0,
	OC0_TOGGLE,
	OC0_CLEAR_ON_COMPAREMATCH,//NOn inverting
	OC0_SET_ON_COMPAREMATCH //inverting
	
	}TIMER0_OC0_Mode_type;

void TIMER0_Init(TIMER0_Mode_type mode,TIMER0_Scaler_type scaler);
void TIMER0_OC0mode(TIMER0_OC0_Mode_type mode);
void TIMER0_OVF_InterruptEnable(void);
void TIMER0_OVF_InterrupDisable(void);
void TIMER0_OC_InterruptEnable(void);
void TIMER0_OC_InterrupDisable(void);
void TIMER0_OVF_SetCallBack(void(*local_fptr)(void));
void TIMER0_OC_SetCallBack(void(*local_fptr)(void));
/*************************************************************************************************/
/* Timer 1 */

#define TIMER1_WRITE(x) (TCNT1=(u16)x)
#define TIMER1_READ1() (TCNT1)
#define TIMER1_READ2(x) (*(u16*)x=TCNT1)

#define TIMER1A_OUTPUT_COMPARE_WRITE(x) (OCR1A=(u16)x)
#define TIMER1A_OUTPUT_COMPARE_READ1() (OCR1A)
#define TIMER1A_OUTPUT_COMPARE_READ2(x) (*(u16*)x=OCR1A)

#define TIMER1B_OUTPUT_COMPARE_WRITE(x) (OCR1B=(u16)x)
#define TIMER1B_OUTPUT_COMPARE_READ1() (OCR1B)
#define TIMER1B_OUTPUT_COMPARE_READ2(x) (*(u16*)x=OCR1B)

#define TIMER1_INPUT_CAPATURE_WRITE(x) (ICR1=(u16)x)
#define TIMER1_INPUT_CAPATURE_READ1() (ICR1)
#define TIMER1_INPUT_CAPATURE_READ2(x) (*(u16*)x=ICR1)

typedef enum{
	
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL1_FALLING,
	EXTERNAL1_RISING
}TIMER1_Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}TIMER1_Mode_type;



typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_CLEAR_ON_COMPAREMATCH,//NOn inverting
	OCRA_SET_ON_COMPAREMATCH  //inverting

}OC1A_Mode_type;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_CLEAR_ON_COMPAREMATCH,//NOn inverting
	OCRB_SET_ON_COMPAREMATCH  //inverting

}OC1B_Mode_type;

typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;


void TIMER1_Init( TIMER1_Mode_type mode,TIMER1_Scaler_type scaler);
void TIMER1_OC1AMode(OC1A_Mode_type oc1a_mode);
void TIMER1_OC1BMode(OC1B_Mode_type oc1b_mode);
void TIMER1_InputCaptureEdge(ICU_Edge_type edge);

void TIMER1_OVF_InterruptEnable(void);
void TIMER1_OVF_InterruptDisable(void);
void TIMER1_OCA_InterruptEnable(void);
void TIMER1_OCA_InterruptDisable(void);
void TIMER1_OCB_InterruptEnable(void);
void TIMER1_OCB_InterruptDisable(void);
void TIMER1_ICU_InterruptEnable(void);
void TIMER1_ICU_InterruptDisable(void);

void TIMER1_OVF_SetCallBack(void(*LocalFptr)(void));
void TIMER1_OCA_SetCallBack(void(*LocalFptr)(void));
void TIMER1_OCB_SetCallBack(void(*LocalFptr)(void));
void TIMER1_ICU_SetCallBack(void(*LocalFptr)(void));

/************************************************************************************************/

/* Timer 2 */
#define TIMER2_WRITE(x) (TCNT2=(u8)x)
#define TIMER2_READ1() (TCNT2)
#define TIMER2_READ2(x) (*(u8*)x=TCNT2)

#define TIMER2_OUTPUT_COMPARE_WRITE(x) (OCR2=(u8)x)
#define TIMER2_OUTPUT_COMPARE_READ1() (OCR2)
#define TIMER2_OUTPUT_COMPARE_READ2(x) (*(u8*)x=OCR2)

typedef enum{

TIMER2_STOP,
TIMER2_SCALER_1,
TIMER2_SCALER_8,
TIMER2_SCALER_32,
TIMER2_SCALER_64,
TIMER2_SCALER_128,
TIMER2_SCALER_256,
TIMER2_SCALER_1024
}TIMER2_Scaler_type;

typedef enum{

TIMER2_NORMAL_MODE=0,
TIMER2_PHASECORRECT_MODE,
TIMER2_CTC_MODE,
TIMER2_FASTPWM_MODE
}TIMER2_Mode_type;

typedef enum{
OC2_DISCONNECTED=0,
OC2_TOGGLE,
OC2_CLEAR_ON_COMPAREMATCH,//NOn inverting
OC2_SET_ON_COMPAREMATCH //inverting

}TIMER2_OC2_Mode_type;

void TIMER2_Init(TIMER2_Mode_type mode,TIMER2_Scaler_type scaler);
void TIMER2_OC2mode(TIMER2_OC2_Mode_type mode);
void TIMER2_OVF_InterruptEnable(void);
void TIMER2_OVF_InterrupDisable(void);
void TIMER2_OC_InterruptEnable(void);
void TIMER2_OC_InterrupDisable(void);
void TIMER2_OVF_SetCallBack(void(*local_fptr)(void));
void TIMER2_OC_SetCallBack(void(*local_fptr)(void));

#endif /* TIMER_INTERFACE_H_ */