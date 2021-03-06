
#ifndef	_3310LCD_H_
#define	_3310LCD_H_
//  Mega16  port B pinout for LCD.


#define LCD_DC                 (1<<6)  
#define LCD_CE                 (1<<4) 
#define LCD_RST                (1<<5)

#define SPI_MOSI               (1<<5) 
#define SPI_CLK                (1<<7)  

void LCDInit(void);
void LCDFull(unsigned char data);
void LCD_write_english_string(unsigned char X,unsigned char Y,char *s);             

void LCD_write_char(unsigned char c);

void LCD_WriteCHchar(unsigned char X,unsigned char Y,unsigned char Addr);
void LCD_DispCHstr(unsigned char X,unsigned char Y,unsigned char *pstr);

#endif	 	



