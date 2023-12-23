#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "TIMER_Interface.h"
#include "TIMER_Service.h"
#include "RGB.h"
#include "DIO_Interface.h"
#include "LCD_Inerface.h"

#define F_CPU 8000000
#include <util/delay.h>

RGB_leds_type CLR1,CLR2;
static u8 RGB_BlueDiff,RGB_RedFiff,RGB_GreenDiff;
static u16 R_b,R_g,R_r;

volatile u32 c_rgb,cb,cr,cg,count;
/*
RGB_leds_type RGB_Arr[26]={
	{255,0,0},    //RED-0
	{255,100,0},
	{255,150,0},  //ORANGE-2
	{255,200,0},
	{255,255,0},  //YELLOW-4
	{200,255,0},
	{150,255,0}, //CHARTERUSE-6
	{100,255,0},
	{0,255,0},   //GREEN-8		
	{0,255,100}, 
	{0,255,150}, //AQUAMARINE-10
	{0,255,200},
	{0,255,255}, //CAYAN-12
	{0,200,255},
	{0,150,255}, //AZURE-14
	{0,100,255},
	{0,0,255},	 //BLUE-16
	{100,0,255},
	{150,0,255}, //VIOLET-18
	{200,0,255},
	{255,0,255}, //MAGNETA-20
	{255,0,200},
	{255,0,150},
	{255,0,100},							 	 	 	 		
		 			 		
};
*/
//clear in compare match
RGB_leds_type RGB_Arr[RGB_NUMS]={
	{254,0,0},    //RED-0
	{254,100,0},
	{254,150,0},  //ORANGE-2
	{254,200,0},
	{254,254,0},  //YELLOW-4
	{200,254,0},
	{150,254,0}, //CHARTERUSE-6
	{100,254,0},
	{0,254,0},   //GREEN-8
	{0,254,100},
	{0,254,150}, //AQUAMARINE-10
	{0,254,200},
	{0,254,254}, //CAYAN-12
	{0,200,254},
	{0,150,254}, //AZURE-14
	{0,100,254},
	{0,0,254},	 //BLUE-16
	{100,0,254},
	{150,0,254}, //VIOLET-18
	{200,0,254},
	{254,0,254}, //MAGNETA-20
	{254,0,200},
	{254,0,150},
	{254,0,100},
	{254,254,254},
	{0,0,0},
	
};
void RGB_Init(void)
{
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	TIMER0_OC0mode(OC0_CLEAR_ON_COMPAREMATCH);
	TIMER1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	TIMER1_OC1AMode(OCRA_CLEAR_ON_COMPAREMATCH);
	TIMER1_OC1BMode(OCRB_CLEAR_ON_COMPAREMATCH);
	
	TIMER2_Init(TIMER2_CTC_MODE,TIMER2_SCALER_8);
	OCR2=99;
	ICR1=255;
// 	OCR1A=20;
// 	OCR1B=30;
// 	OCR0=50;
// 	PWM_Duty(100,OCR1B);
// 	PWM_Duty(100,OCR1A);
// 	PWM_Duty(0,OCR0);
}

void RGB_Color(RGB_color_type color)
{
	OCR0=RGB_Arr[color].RGB_blue;
	OCR1A=RGB_Arr[color].RGB_green;
	OCR1B=RGB_Arr[color].RGB_red;
	
}

void RGB_Color_to_Color(RGB_color_type color1,RGB_color_type color2,u16 time)
{
	TIMER2_OC_InterruptEnable();
	TIMER2_OC_SetCallBack(RGB_FuncTime);
	OCR0=RGB_Arr[color1].RGB_blue;
	OCR1A=RGB_Arr[color1].RGB_green;
	OCR1B=RGB_Arr[color1].RGB_red;
	CLR1=RGB_Arr[color1];
	CLR2=RGB_Arr[color2];

	if(CLR1.RGB_blue>CLR2.RGB_blue)
	{
		RGB_BlueDiff=CLR1.RGB_blue-CLR2.RGB_blue;

	}
	else
	{
		RGB_BlueDiff=CLR2.RGB_blue-CLR1.RGB_blue;

	}
	
	if(CLR1.RGB_red>CLR2.RGB_red)
	{
		RGB_RedFiff=CLR1.RGB_red-CLR2.RGB_red;

	}
	else
	{
		RGB_RedFiff=CLR2.RGB_red-CLR1.RGB_red;

	}
	if(CLR1.RGB_green>CLR2.RGB_green)
	{
		RGB_GreenDiff=CLR1.RGB_green-CLR2.RGB_green;

	}
	else
	{
		RGB_GreenDiff=CLR2.RGB_green-CLR1.RGB_green;

	}
	
   count=((u32)time*1000)/(OCR2+1);
 
   if(RGB_BlueDiff>0)
   {
	   R_b=count/RGB_BlueDiff;
   }
   if(RGB_RedFiff>0)
   {
	  R_r=count/RGB_RedFiff; 
   }
   if(RGB_GreenDiff>0)
   {
	   R_g=count/RGB_GreenDiff;
   }
//    LCD_GoTO(0,0);
//    LCD_WriteNum(R_r);
//    LCD_WriteString(" ");
//    
//    LCD_GoTO(0,10);
//    LCD_WriteNum(R_g);
//    LCD_WriteString(" ");
//    
//    LCD_GoTO(1,0);
//    LCD_WriteNum(R_b);
//    LCD_WriteString(" ");
   
}

void RGB_FuncTime(void)
{
	u32 static c1=0,cb,cr,cg;
	c1++;
	s16 temp;

// 	c_rgb++;
// 	DIO_TogglePin(PINC0);
	
	cb++;
	cr++;
	cg++;
	if(cb==R_b)
	{
		cb=0;
		if(CLR1.RGB_blue>CLR2.RGB_blue)
		{
			OCR0=OCR0-1;
			temp=OCR0-1;
			if(temp<0)
			{
				OCR0=0;
			}
			

		}
		else if(CLR1.RGB_blue<CLR2.RGB_blue)
		{
			OCR0=OCR0+1;
			temp=OCR0-1;
			if(temp>254)
			{
				OCR0=254;
			}

		}
	}

	if(cr==R_r)
	{
		if(CLR1.RGB_red>CLR2.RGB_red)
		{
			OCR1B=OCR1B-1;
			temp=OCR1B-1;
			if(temp<0)
			{
				OCR1B=0;
			}
		}
		else if(CLR1.RGB_red<CLR2.RGB_red)
		{
			OCR1B=OCR1B+1;
			temp=OCR1B+1;
			if(temp>254)
			{
				OCR1B=254;
			}

		}
		cr=0;
	}
	if(cg==R_g)
	{
		if(CLR1.RGB_green>CLR2.RGB_green)
		{
			OCR1A=OCR1A-1;
			temp=OCR1A-1;
			if(temp<0)
			{
				OCR1A=0;
			}
		}
		else if(CLR1.RGB_green<CLR2.RGB_green)
		{
			OCR1A=OCR1A+1;
			temp=OCR1A+1;
			if(temp>254)
			{
				OCR1A=254;
			}

		}
		cg=0;
		
	}
	
// 	if(c_rgb==count)
// 	{
// 		
// 		c_rgb=0;
// 		OCR0=CLR2.RGB_blue;
// 		OCR1B=CLR2.RGB_red;
// 		OCR1A=CLR2.RGB_green;
// 		TIMER2_OC_InterruptDisable();
// 				  
// 		
// 		
// 	}
	if(c1==count)
	{
		DIO_TogglePin(PINC0);
		c1=0;
				
		OCR0=CLR2.RGB_blue;
		OCR1B=CLR2.RGB_red;
		OCR1A=CLR2.RGB_green;
		TIMER2_OC_InterruptDisable();
	}

}