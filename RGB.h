

#ifndef RGB_H_
#define RGB_H_

typedef struct{
	u8 RGB_red;
	u8 RGB_green;
	u8 RGB_blue;
	
	}RGB_leds_type;

typedef enum {
	RBG_RED=0,
	RBG_DARKORANGE,
	RBG_ORANGE, 
	RBG_BABYORANGE, 
	RBG_YELLOW, 
	RBG_BABYYELLOW, 
	RBG_CHARTERUSE, 
	RBG_BABYGREEN, 
	RBG_GREEN, 
	RBG_BABYAQUAMARINE, 
	RBG_AQUAMARINE, 
	RBG_BABYCAYAN, 
	RBG_CAYAN, 
	RBG_BABYAZURE, 
	RBG_AZURE, 
	RBG_BABYBLUE, 
	RBG_BLUE, 
	RBG_BABYVIOLET, 
	RBG_VIOLET, 
	RBG_BABYMAGNETA, 
	RBG_MAGNETA, 
	RBG_DARKMAGNET, 
	RBG_BABYROSE, 
	RBG_ROSE,
	RGB_WHITE,
	RGB_BLACK,
	RGB_NUMS  
	}RGB_color_type;

void RGB_Init(void);
void RGB_Color(RGB_color_type color);
void RGB_Color_to_Color(RGB_color_type color1,RGB_color_type color2,u16 time);
void RGB_FuncTime(void);

#endif /* RGB_H_ */