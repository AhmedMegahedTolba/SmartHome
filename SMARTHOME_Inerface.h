


#ifndef SMARTHOME_INERFACE_H_
#define SMARTHOME_INERFACE_H_


typedef struct{
	const u8 Name[50];
	void (*Smart_home_Fptr)(u8 num);
	
	}Task_type;
	
void Count_HAL_Name_Val(u8*str);
void SAMARTHOME_LED_On(u8 led_num);
void SAMARTHOME_LED_Off(u8 led_num);
void SAMARTHOME_LCD_Write(u8 val);

void SMARTHOME_Runnable(void);
void SAMARTHOME_RGB(u8 val);

#endif /* SMARTHOME_INERFACE_H_ */