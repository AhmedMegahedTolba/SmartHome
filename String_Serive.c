#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "String_Serive.h"
#include "LCD_Inerface.h"

u8 String_Len(u8*str)
{
	u8 i=0;
	for(i=0;str[i];i++);
	return i;
}
void String_Reverse(u8*str)
{
	u8 i,j,temp;
	u8 l=String_Len(str);
	for(i=0,j=l-1;i<=j;i++,j--)
	{
		temp=str[i];
		str[i]=str[j];
		str[j]=temp;
	}
	
}

void String_Cpy(u8*str1,u8*str2)
{
	u8 i;
	for(i=0;str1[i];i++)
	{
		str2[i]=str1[i];
		
	}
	str2[i]=0;
	
}

String_Cmpr_type String_Cmpr(u8*str1,u8*str2)
{
	u8 i,j;
	u8 c1,c2;
	u8 l1=String_Len(str1);
	u8 l2=String_Len(str2);
	String_Cmpr_type flag=STRING_SAME;
	for(i=0;str1[i] || str2[i] ;i++)
	{
		c1=str1[i];
		c2=str2[i];
		if(c1>='A'&&c1<='Z')
		{
			c1=c1-'A'+'a';
		}
		if(c2>='A'&&c2<='Z')
		{
			c2=c2-'A'+'a';
		}
		
		if(c1<c2)
		{
			flag=STRING1_LESS;
			break;
			
		}
		else if(c1>c2)
		{
			flag=STRING1_BIGGER;
			break;
		}
		
		
	}
	return flag;
}
u32 String_To_Decimal(u8*str)
{
	u32 res=0;
	u8 i=0;
	for(i=0;str[i];i++)
	{
		res=res*10+(str[i]-'0');
	}
	return res;
}

void String_Print(u8*str)
{
	for(u8 i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}