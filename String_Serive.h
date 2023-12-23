

#ifndef STRING_SERIVE_H_
#define STRING_SERIVE_H_
typedef enum{
	STRING_SAME=0,
	STRING1_LESS,
	STRING1_BIGGER
	
	}String_Cmpr_type;

u8 String_Len(u8*str);
void String_Reverse(u8*str);
void String_Cpy(u8*str1,u8*str2);
String_Cmpr_type String_Cmpr(u8*str1,u8*str2);
u32 String_To_Decimal(u8*str);

void String_Print(u8*str);

#endif /* STRING_SERIVE_H_ */