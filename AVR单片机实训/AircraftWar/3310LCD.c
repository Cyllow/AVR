
#include <iom16v.h>
#include <macros.h>
#include "ASCII_6x8.h"
#include "3310LCD.h"
#include "chinese_12x12.h"

void LCD_write_byte(unsigned char data, unsigned char dc);
/*-----------------------------------------------------------------------
LCD_init          : 3310LCD初始化

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 
-----------------------------------------------------------------------*/
void delayus(unsigned int counter)
{
	while(counter--)
	{
		NOP();
		NOP();
		NOP();
		NOP();	
	}
}

void LCDInit(void)
{

	PORTA &= ~LCD_RST;          // 产生一个让LCD复位的低电平脉冲
	delayus(10);
	PORTA |= LCD_RST;

	PORTA &= ~LCD_CE ;		//  使能LCD
	delayus(10);

	LCD_write_byte(0x21, 0);	// 使用扩展命令设置LCD模式0b0010 0001
	LCD_write_byte(0b11000000, 0);	// 设置偏置电压Vop  0b1100 1000 //越大，整体越暗  对比度c8
	LCD_write_byte(0x06, 0);	// 温度校正        0b0000 0110
	LCD_write_byte(0x13, 0);	// 1:48 偏置系统   0b0001 0011
	LCD_write_byte(0x20, 0);	// 使用基本命令 0b0010 0000
	LCDFull(0x00);	        // 清屏
	LCD_write_byte(0x0c, 0);	// 设定显示模式，正常显示0b0000 1100

	PORTA |= LCD_CE;          // 关闭LCD
}

/*-----------------------------------------------------------------------
LCD_clear         : LCD清屏函数

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 
-----------------------------------------------------------------------*/
void LCDFull(unsigned char data)
{
	unsigned int i;

	LCD_write_byte(0x0c, 0);			
	LCD_write_byte(0x80, 0);			

	for (i=0; i<504; i++)
		//添加填充代码
		LCD_write_byte(data,1);			
}

/*-----------------------------------------------------------------------
LCD_set_XY        : 设置LCD坐标函数

输入参数：X       ：0－83
Y       ：0－5

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 
-----------------------------------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y)
{
	LCD_write_byte(0x40 | Y, 0);		// column
	LCD_write_byte(0x80 | X, 0);          	// row
}

/*-----------------------------------------------------------------------
LCD_write_char    : 显示英文字符

输入参数：c       ：显示的字符；

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 
-----------------------------------------------------------------------*/
void LCD_write_char(unsigned char c)
{
	unsigned char line;
	c -= 32;
	for(line = 0;line < 6;line++)
	    LCD_write_byte(font6x8[c][line],1);
}

/*-----------------------------------------------------------------------
LCD_write_english_String  : 英文字符串显示函数

输入参数：*s      ：英文字符串指针；
X、Y    : 显示字符串的位置,x 0-83 ,y 0-5

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 		
-----------------------------------------------------------------------*/
void LCD_write_english_string(unsigned char X,unsigned char Y,char *s)
{
	unsigned char i,line;
	LCD_set_XY(X,Y);
	while(*s)
	{
	     LCD_write_char(*s);
		 s++;
	}
}

/*-----------------------------------------------------------------------
LCD_write_byte    : 使用SPI接口写数据到LCD

输入参数：data    ：写入的数据；
command ：写数据/命令选择；

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-13 
-----------------------------------------------------------------------*/
void LCD_write_byte(unsigned char data, unsigned char command)
{
	PORTA &= ~LCD_CE ;		        // 使能LCD

	if (command == 0)
		PORTA &= ~LCD_DC ;	        // 传送命令
	else
		PORTA |= LCD_DC ;		        // 传送数据

	SPDR = data;			// 传送数据到SPI寄存器

	while ((SPSR & 0x80) == 0);         // 等待数据传送完毕

	PORTA |= LCD_CE ;			// 关闭LCD
}

//编写单个汉字
void LCD_WriteCHchar(unsigned char X,unsigned char Y,unsigned char Addr)
{
     unsigned char i;
	 LCD_set_XY(X,Y);
	 for(i = 0;i < 24;i++)
	 {
	      if(i == 12)
		      LCD_set_XY(X,Y+1);
		  LCD_write_byte(chinese_12[Addr].data[i],1);
	 }
}


//显示汉字字符串
void LCD_DispCHstr(unsigned char X,unsigned char Y,unsigned char *pstr)
{
     unsigned char i;
	 unsigned char Addr = 0;
	 unsigned char count = 0;
	 while(*pstr)
	 {
	      for(i = 0;i < chinese_12_len;i++)
	      {
	           if((chinese_12[i].value[0] == *pstr) && (chinese_12[i].value[1] == *(pstr+1)))
		       {
		             Addr = i;
		         	 break;
		       } 
	      }
	 
	      LCD_WriteCHchar(X+count*12,Y,Addr);
		  count++;
		  
		  pstr++;
		  pstr++;
	 }
}

