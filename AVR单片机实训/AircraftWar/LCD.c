//ICC-AVR application builder : 2009-10-23 18:40:43
// Target : M16
// Crystal: 7.3728Mhz

#include <iom16v.h>
#include <macros.h>
#include "3310LCD.h"


#define CLR_SHCLK() PORTB &= ~(1<<1)//移位时钟 SCLK
#define SET_SHCLK() PORTB |= (1<<1)	//移位时钟 SCLK，上升沿

#define CLR_STCLK() PORTB &= ~(1<<0) //锁存时钟 RCLK
#define SET_STCLK() PORTB |= (1<<0)	//拉高锁存时钟，上升沿

#define CLR_DS()	PORTA &= ~(1<<0)//清零
#define SET_DS()	PORTA |= (1<<0)	//置位

#define key_input ((PIND&(1<<3))|(PINA&(1<<7)))
#define key_state_0 0
#define key_state_1 1
#define key_state_2 2
#define key_state_3 3
#define nokey 0
#define SW8 1
#define key1_short 2
#define key1_long 3

#define noflash 0
#define secflash 1
#define minflash 2

unsigned int t[9] = {0,956,865,759,716,638,568,506,470};
unsigned char d[9] = {0,105,116,132,140,157,176,198,209};

unsigned char note_n = 0;
unsigned int int_n = 1;
unsigned char sound_flag = 0;
unsigned char flag = 0;
#define period_rate 0.9216
#define note_rate 2






//梦中的婚礼
#define music1_Max_note 500
const unsigned char music1[music1_Max_note] = {
			3,2, 3,2, 3,2, 1,1, 3,1,   5,2,   5,2,   1,1,  5,1,  3,2,  6,2, 7,2, 7,1, 6,2, 5,2, 3,2, 5,1, 6,1, 4,1, 5,1,

 3,1,  1,1, 2,1, 7,2,  1,2,  5,1,   3,1,  6,2, 7,1,  7,1, 6,2,  5,1, 3,2, 5,2, 6,2, 4,2, 5,2,  3,2, 2,1, 1,1, 7,4,

 5,2, 4,1, 4,1, 3,2, 3,2, 5,1, 6,2, 1,2, 6,1,  1,1, 2,2,  5,1, 4,1, 4,2, 3,2,  3,2, 1,2, 1,2, 1,2,   5,1, 4,1, 4,1, 3,2, 3,1,
 
 
 
 
 0,4, 0,4, 0,4,  0,2, 6,1, 6,1, 7,1, 7,1, 1,1, 1,1, 7,1, 7,1, 6,1, 6,1, 3,1,3,1, 1,1, 1,1, 6,1, 6,1, 5,1,5,1, 4,1, 4,1, 3,1, 4,1, 5,1, 4,2, 4,4,
 
 0,1, 4,1, 4,1, 5,1, 5,1, 6,1, 6,1, 7,1, 7,1, 5,1, 5,1, 2,1, 2,1, 4,1, 4,1, 3,1, 3,1, 2,1, 3,1, 4,1, 3,2, 3,2, 3,1, 3,4,
 
 3,2, 6,1, 1,1, 3,1, 2,1, 3,2, 6,1, 1,1, 3,1, 2,1, 3,2, 6,1, 1,1, 4,1, 3,1, 4,2, 6,1, 1,1, 4,1, 3,1, 4,2, 4,1, 3,1, 4,1, 4,1, 5,2, 5,1, 6,1, 5,1, 6,1, 3,4,
 
 3,2, 6,1, 1,1, 3,1, 2,1, 3,2, 6,1, 1,1, 3,1, 2,1, 3,2, 6,1, 1,1, 4,1, 3,1, 4,2, 6,1, 1,1, 4,1, 3,1, 4,2, 4,1, 3,1, 4,1, 4,1, 5,2, 5,1, 6,1, 5,1, 6,1, 3,4,
 
 1,2, 3,1, 3,1, 4,1, 4,2, 2,1, 2,1, 7,1, 7,2, 2,1, 2,1, 3,1, 3,2, 1,1, 1,1, 6,1, 5,1, 6,2, 1,1, 1,1, 2,1, 2,2, 7,1, 3,1, 2,1, 3,4
 

			};
	



//星之所在			
#define music2_Max_note 600
const unsigned char music2[music2_Max_note]={
                                         4,2,  3,2,  4,2,  6,2,  3,4,  3,4,            2,2, 1,2, 2,2, 4,2, 1,4, 1,4,        7,2, 6,2, 7,2, 4,2, 3,4, 1,4,
 2,2, 3,2, 4,2, 6,2, 5,4, 5,4,           4,2,  3,2,  4,2,  6,2,  3,4,  1,4,            2,2, 3,2, 4,2, 5,2, 6,4, 6,4,        7,2, 6,2, 5,2, 4,2, 3,2, 6,2, 1,2, 3,2,
 2,4, 2,4, 2,4, 0,4,        4,2, 3,2, 4,2, 6,2, 3,4, 3,4,       2,2, 1,2, 2,2, 4,2, 1,4, 1,4,      7,2, 6,2, 7,2, 4,2, 3,4, 1,4,   2,2, 3,2, 4,2, 6,2, 5,4, 5,4, 
 4,2, 3,2, 4,2, 6,2, 3,4, 1,4,           2,2,  3,2,  4,2,  5,2,  6,4,  6,4,            7,2, 6,2, 5,2, 4,2, 3,2, 6,2, 1,2, 3,2,   2,4, 2,4, 2,4,
 6,4, 5,4,        1,4, 7,4, 6,4, 5,4,     3,4, 3,4, 0,2, 3,2, 4,2, 2,2, 2,4, 2,4, 2,4, 0,4,     7,4, 1,4, 2,2, 4,4,   
 3,4, 4,4, 5,2, 7,4, 6,2, 6,4, 6,4, 6,4, 0,4, 0,4, 0,4,0,4,0,4,
                                         4,2,  3,2,  4,2,  6,2,  3,4,  3,4,            2,2, 1,2, 2,2, 4,2, 1,4, 1,4,        7,2, 6,2, 7,2, 4,2, 3,4, 1,4,
 2,2, 3,2, 4,2, 6,2, 5,4, 5,4,           4,2,  3,2,  4,2,  6,2,  3,4,  1,4,            2,2, 3,2, 4,2, 5,2, 6,4, 6,4,        7,2, 6,2, 5,2, 4,2, 3,2, 6,2, 1,2, 3,2,
 2,4, 2,4, 2,4, 0,4,        4,2, 3,2, 4,2, 6,2, 3,4, 3,4,       2,2, 1,2, 2,2, 4,2, 1,4, 1,4,      7,2, 6,2, 7,2, 4,2, 3,4, 1,4,   2,2, 3,2, 4,2, 6,2, 5,4, 5,4, 
 4,2, 3,2, 4,2, 6,2, 3,4, 1,4,           2,2,  3,2,  4,2,  5,2,  6,4,  6,4,            7,2, 6,2, 5,2, 4,2, 3,2, 6,2, 1,2, 3,2,   2,4, 2,4, 2,4, 2,1, 3,1, 4,1, 5,1,
 6,4, 6,4, 6,4, 5,4,        1,4, 7,4, 6,4, 5,4,     3,4, 3,4, 0,2, 3,2, 4,2, 2,2, 2,4, 2,4, 2,4, 0,4,     7,4, 1,4, 2,2, 4,4,   
 3,4, 4,4, 5,2, 7,4, 6,2, 6,4, 6,4, 6,4, 0,4, 0,4, 0,4,0,4,0,4,      5,2, 4,2, 5,2, 7,2, 4,4, 4,4
                           };


						   
unsigned char music_sel = 2;						   

//定义字符表 		   														
unsigned char led_7[14] = {0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
		 	  			   0x80,0x90,0xff,0x7f,0xc6,0x00};
unsigned char disp_buff_min_number = 0;	
unsigned char disp_buff_sec_number = 0;				 
unsigned char disp_buff[4] = {0,0,0,0};
unsigned char post = 0;
unsigned char time_10ms_count = 0;
unsigned char time_10ms_ok = 0;
unsigned char time_300ms_count = 0;
unsigned char time_300ms_ok = 0;
unsigned int time_1s_count = 0;
unsigned char time_1s_ok = 0;
unsigned char isflash = noflash;
unsigned char flash_count = 0;

unsigned char layout0[2] = {1,0x08};
unsigned char layout1[2] = {1,0x08};
unsigned char layout2[2] = {1,0x08};
unsigned char layout3[2] = {1,0x08};
unsigned char layout4[2] = {1,0x08};
unsigned char layout5[2] = {1,0x08};
unsigned char plane_x = 40;
unsigned char plane_y = 5;
unsigned char plane_bullet_x = 0;
unsigned char plane_bullet_y = 0;


//CTC模式，8分频
void timer1_init(void)
{
	//TCCR1A = 0x40;
	//TCCR1B = 0x0A;	//CTC模式,8分频,start
	TCCR1B = 0x08;		//stop
}

#pragma interrupt_handler timer1_compa_isr:iv_TIM1_COMPA
void timer1_compa_isr(void)
{
	//compare occured TCNT1=OCR1A
	if(music_sel == 1)
	{
		if(note_n == music1_Max_note)	//重头开始播放音乐
		{
			note_n = 0;
			int_n = 1;
		}
		else
		{
			if(--int_n == 0)	//播放完一个音符
			{
				if(music1[note_n] == 0)	//无声音一段时间
				{
					sound_flag = 0;
					TCCR1B = 0x08;	//timer1停止工作
					PORTA |= (1 << 3);	//关闭蜂鸣器
					OCR1A = t[1] / period_rate;
					int_n = d[1] * note_rate;
					note_n++;
					int_n = int_n * music1[note_n];
					note_n++;
					TCCR1B = 0x0A;	//启动timer1，播放下一个音符
				}
				else
				{
					sound_flag = 1;
					TCCR1B = 0x08;	//timer1停止工作
					OCR1A = t[music1[note_n]] / period_rate;//取下一个音符
					int_n = d[music1[note_n]] * note_rate;//取该音符的基本节拍单位
					note_n++;
					int_n = int_n * music1[note_n];	//计算该音符的节拍值
					note_n++;
					TCCR1B = 0x0A;		//启动timer1，播放下一个音符
				}
			}
			else
			{
				if(sound_flag)
				{
					if(flag)
					{
						PORTA &= ~(1<<3);
						flag = 0;
					}
					else
					{
						PORTA |= (1<<3);
						flag = 1;
					}
				}
			}
		}
	}
	
	
	else
	{
		if(note_n == music2_Max_note)	//重头开始播放音乐
		{
			note_n = 0;
			int_n = 1;
		}
		else
		{
			if(--int_n == 0)	//播放完一个音符
			{
				if(music1[note_n] == 0)	//无声音一段时间
				{
					sound_flag = 0;
					TCCR1B = 0x08;	//timer1停止工作
					PORTA |= (1 << 3);	//关闭蜂鸣器
					OCR1A = t[1] / period_rate;
					int_n = d[1] * note_rate;
					note_n++;
					int_n = int_n * music2[note_n];
					note_n++;
					TCCR1B = 0x0A;	//启动timer1，播放下一个音符
				}
				else
				{
					sound_flag = 1;
					TCCR1B = 0x08;	//timer1停止工作
					OCR1A = t[music2[note_n]] / period_rate;//取下一个音符
					int_n = d[music2[note_n]] * note_rate;//取该音符的基本节拍单位
					note_n++;
					int_n = int_n * music2[note_n];	//计算该音符的节拍值
					note_n++;
					TCCR1B = 0x0A;		//启动timer1，播放下一个音符
				}
			}
			else
			{
				if(sound_flag)
				{
					if(flag)
					{
						PORTA &= ~(1<<3);
						flag = 0;
					}
					else
					{
						PORTA |= (1<<3);
						flag = 1;
					}
				}
			}
		}
	}
	
	
}




void delay_ms(unsigned int delay_i)
{
	unsigned char num;
	while(delay_i > 0)
	{
		for(num = 0;num < 187;num++)
		{
			asm("nop");
		}
		delay_i--;
	}
}

unsigned char read_key(void)
{
	static unsigned char key_state = 0,key_time;
	unsigned char key_press,key_return = nokey;

	key_press = key_input;//读取按键电平
	switch(key_state)
	{
		case key_state_0:
			if(key_press != 0x88)	//按键按下，转确认状态
				key_state = key_state_1;
			break;
		case key_state_1:
			if(key_press != 0x88)
			{
				if(key_press == 0x80)	//SW8按键按下，因为无长按，所以直接转状态3判定是否松开
				{
					key_state = key_state_3;
					key_return = SW8;
				}
				if(key_press == 0x08)	//key1按下，转状态2判定为长按还是短按
				{	
					key_state = key_state_2;
					key_time = 0;
				}
			}
			else				//按键无按下（抖动）
				key_state = key_state_0;
			break;
		case key_state_2:
			if(key_press == 0x88)	//按下时间不过1S，为短按
			{	
				key_state = key_state_0;
				key_time = 0;
				key_return = key1_short;
			}
			else if((++key_time) >= 100)	//按下时间超过1S，为长按
			{
				key_state = key_state_3;
				key_time = 0;
				key_return = key1_long;
			}
			break;
		case key_state_3:
			if(key_press == 0x88)	//无按键按下了
				key_state = 0;
			else if(((++key_time) >= 50)  && (key_press == 0x08))	//key1长按后每隔0.5S为下一次长按
			{
				key_time = 0;
				key_return = key1_long;
			}
			break;
	}
	return key_return;
}

void HC595_send_byte(unsigned char SndData)
{
    //完成595的驱动函数，实现通过595把串行数据发送到Q0——Q7
	unsigned char i;
	for(i=0;i<8;i++)
	{
	 	if((SndData&(1<<(7-i)))==0)
			CLR_DS();
		else
			SET_DS();
		CLR_SHCLK();
		SET_SHCLK();
	}
	CLR_STCLK();
	SET_STCLK();
}

void port_init(void)
{
 //添加GPIO初始化
	DDRA |= (1<<4)|(1<<5)|(1<<6);
	DDRB |= (1<<4)|(1<<5)|(1<<7);
 
	DDRA|=(1<<0);
	DDRA&=~(1<<7);
	PORTA|=(1<<7);
	DDRB|=(1<<0)|(1<<1);
	PORTB|=(1<<1);
	DDRD|=0xf0;
	PORTD&=0X0F;
	DDRD&=~(1<<3);
	PORTD|=(1<<3);
	
	DDRA |= (1 << 3);
	PORTA |= (1 << 3);
}

void timer0_init(void)
{
	TCCR0 = 0x00; //stop
	TCNT0 = 0x1A; //set count
	OCR0  = 0xE6;  //set compare
	TCCR0 = 0x03; //start timer
}

#pragma interrupt_handler timer0_ovf_isr:iv_TIM0_OVF
void timer0_ovf_isr(void)
{
	TCNT0 = 0x1A; //reload counter value
	PORTD|=0xf0;
	//正常计数时，正常送数，点亮对应的数码管
	//进行调时时，正常送数，每隔0.3秒点亮对应数码管，实现闪烁功能
	if(post == 1)
		HC595_send_byte(led_7[disp_buff[post]] & ~(1<<7));
	else
		HC595_send_byte(led_7[disp_buff[post]]);
	if(isflash == secflash && time_300ms_ok && (post == 2 || post == 3))
		PORTD |= 0XF0;
	else if(isflash == minflash && time_300ms_ok && (post == 0 || post == 1))
		PORTD |= 0XF0;
	else
		PORTD&=~(1<<(7-post));
	if(++post>=4)
		post=0;
	if(++time_10ms_count >= 5)
	{
		time_10ms_ok = 1;
		time_10ms_count = 0;
	}
	if(++time_300ms_count >= 150)
	{
		time_300ms_ok = ~time_300ms_ok;
		time_300ms_count = 0;
	}
	if(++time_1s_count >= 500)
	{
		time_1s_ok = 1;
		time_1s_count = 0;
	}
}
 

//UART0 initialize
// desired baud rate: 9600
// actual: baud rate:9600 (0.0%)
void uart0_init(void)
{
 UCSRB = 0x00; //disable while setting baud rate
 UCSRA = 0x00;
 UCSRC = BIT(URSEL) | 0x06;
 UBRRL = 0x2F; //set baud rate lo
 UBRRH = 0x00; //set baud rate hi
 UCSRB = 0x18;
}
//SPI initialize
// clock rate: 1843199hz
void spi_init(void)
{
 //SPI初始化
 SPCR |= (1<<6)|(1<<4);
}

//call this routine to initialize all peripherals
void init_devices(void)
{
 //stop errant interrupts until set up
 CLI(); //disable all interrupts
 port_init();
 spi_init();
 uart0_init();
 timer0_init();
 timer1_init();

 MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x01; //timer interrupt sources
 TIMSK |= 0x10;
 SEI(); //re-enable interrupts
 //all peripherals are now initialized
}

void UARTSend(unsigned char data)
{
    while ( !( UCSRA & (1<<UDRE)) );
    UDR = data;
}



void plane_left_move()
{
	LCD_set_XY(plane_x,plane_y);		//清除飞机残影
	LCD_write_byte(0x00,1);
	LCD_write_byte(0x00,1);
	LCD_write_byte(0x00,1);
	LCD_write_byte(0x00,1);
	if(plane_x > 0)
		plane_x--;
	LCD_set_XY(plane_x,plane_y);		//画出移动后的飞机
	LCD_write_byte(0xf8,1);
	LCD_write_byte(0x20,1);
	LCD_write_byte(0x20,1);
	LCD_write_byte(0xf8,1);
}

void plane_right_move()
{
	LCD_set_XY(plane_x,plane_y);
	LCD_write_byte(0x00,1);
	LCD_write_byte(0x00,1);
	LCD_write_byte(0x00,1);
	LCD_write_byte(0x00,1);
	if(plane_x < 80)
		plane_x++;
	LCD_set_XY(plane_x,plane_y);
	LCD_write_byte(0xf8,1);
	LCD_write_byte(0x20,1);
	LCD_write_byte(0x20,1);
	LCD_write_byte(0xf8,1);
}

unsigned char plane_is_die()
{
    if((plane_x == layout5[0]) || (plane_x == layout5[0] + 1) || (plane_x == layout5[0] + 2) || (plane_x == layout5[0] + 3) || (plane_x == layout5[0] + 4))
	    return 1;
	else if((plane_x + 3 == layout5[0]) || (plane_x + 3 == layout5[0] + 1) || (plane_x + 3 == layout5[0] + 2) ||(plane_x + 3 == layout5[0] + 3) || (plane_x + 4 == layout5[0] + 4))
		return 1;
	else
	    return 0;
	
}

void game_over()
{
    LCDFull(0x00);
	LCD_write_english_string(0,2," You are die!");
	LCD_write_english_string(0,3,"   ---  ---");
	LCD_write_english_string(0,4,"    |    |");
	LCD_write_english_string(0,5,"    WuWuWu");
	delay_ms(15000);
	LCDFull(0x00);
	main_menu();
}

void main_menu()
{
	LCDFull(0x00);
	LCD_DispCHstr(12,0,"一、计时器");
	LCD_DispCHstr(12,2,"二、音乐盒");
	LCD_DispCHstr(12,4,"三、游戏");
	LCD_DispCHstr(0,0,"》");
}

void sel1_menu()
{
	LCDFull(0x00);
	LCD_DispCHstr(24,2,"计时器");
}

void sel1_menu_work()
{
	unsigned char menu1_flag = 1;
	while(menu1_flag)
	{
		if(time_1s_ok)
		{
			flash_count++;
			if(flash_count >= 3)
			{
				isflash = noflash;
				flash_count = 0;
			}
			time_1s_ok = 0;
			if(isflash == noflash)
			{
				if(++disp_buff_sec_number >= 60)
				{
					disp_buff_sec_number = 0;
					if(++disp_buff_min_number >= 60)
					{
						disp_buff_min_number = 0;
					}
				}
				disp_buff[0] = disp_buff_min_number/10;
				disp_buff[1] = disp_buff_min_number%10;
				disp_buff[2] = disp_buff_sec_number/10;
				disp_buff[3] = disp_buff_sec_number%10;
			}
		}
		
		
		if(time_10ms_ok)
		{
			time_10ms_ok = 0;
			switch(read_key())
			{
				case SW8:
					flash_count = 0;
					if(isflash == noflash)
						isflash = secflash;
					else if(isflash == secflash)
						isflash = minflash;
					else 
						isflash = secflash;
					break;
				case key1_short:
					flash_count = 0;
					if(isflash == secflash)
					{
						if(++disp_buff_sec_number >= 60)
							disp_buff_sec_number = 0;
					}
					else if(isflash == minflash)
					{
						if(++disp_buff_min_number >= 60)
							disp_buff_min_number = 0;
					}
					disp_buff[0] = disp_buff_min_number/10;
					disp_buff[1] = disp_buff_min_number%10;
					disp_buff[2] = disp_buff_sec_number/10;
					disp_buff[3] = disp_buff_sec_number%10;
					break;
				case key1_long:
					menu1_flag = 0;
					disp_buff_min_number = 0;
					disp_buff_sec_number = 0;
					disp_buff[0] = 0;
					disp_buff[1] = 0;
					disp_buff[2] = 0;
					disp_buff[3] = 0;
					LCDFull(0x00);
					main_menu();
					break;
			}
		}
		
		
	}
}

void sel2_menu()
{
	LCDFull(0x00);
	LCD_DispCHstr(12,0,"正在播放：");
	LCD_DispCHstr(24,2,"星之所在");
}

void sel2_menu_work()
{
	unsigned char menu2_flag = 1;
	while(menu2_flag)
	{
		if(time_10ms_ok)
		{
			time_10ms_ok = 0;
			switch(read_key())
			{
				case SW8:
				if(TCCR1B == 0x08)
					TCCR1B = 0x0A;
				else
				{
					TCCR1B = 0x08;
					PORTA |= (1 << 3);
				}
				break;
				
				case key1_short:
				if(music_sel == 1)
				{
					music_sel = 2;
					LCDFull(0x00);
					LCD_DispCHstr(12,0,"正在播放：");
					LCD_DispCHstr(24,2,"星之所在");
				}
				else
				{
					music_sel = 1;
					LCDFull(0x00);
					LCD_DispCHstr(12,0,"正在播放：");
					LCD_DispCHstr(12,2,"梦中的婚礼");
				}
				note_n = 0;
				int_n = 1;
				break;
				
				case key1_long:
				menu2_flag = 0;
				TCCR1B = 0x08;
				PORTA |= (1 << 3);
				music_sel = 2;
				note_n = 0;
				int_n = 1;
				LCDFull(0x00);
				main_menu();
				break;
			}
		}
	}
}

unsigned char is_has_bullet()
{
	if((plane_bullet_y == 0) || (plane_bullet_x == 0))
		return 0;
	else
		return 1;
}

void plane_bullet_move()
{
	if((plane_bullet_x == 0) || (plane_bullet_y == 0))
	{
		LCD_set_XY(plane_bullet_x,plane_bullet_y);
		LCD_write_byte(0x00,1);
		plane_bullet_x = 0;
		plane_bullet_y = 0;
		return;
	}
	LCD_set_XY(plane_bullet_x,plane_bullet_y);
	LCD_write_byte(0x00,1);
	if(plane_bullet_y > 0)
		plane_bullet_y = plane_bullet_y - 1;
	LCD_set_XY(plane_bullet_x,plane_bullet_y);
	LCD_write_byte(0x08,1);
}

void plane_bullet_want_die()
{
	if(plane_bullet_y == 0)
	{
		if(plane_bullet_x == layout0[0] || (plane_bullet_x == layout0[0] + 1) || (plane_bullet_x == layout0[0] + 2) || (plane_bullet_x == layout0[0] + 3) || (plane_bullet_x == layout0[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,layout0[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout0[0] = 0;
		}
		else if(plane_bullet_x + 1 == layout0[0] || (plane_bullet_x + 1 == layout0[0] + 1) || (plane_bullet_x + 1 == layout0[0] + 2) || (plane_bullet_x + 1 == layout0[0] + 3) || (plane_bullet_x + 1 == layout0[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,plane_bullet_y);
			LCD_write_byte(0x00,1);
			LCD_set_XY(plane_bullet_x + 1,layout0[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout0[0] = 0;
		}
	}
	
	else if(plane_bullet_y == 1)
	{
		if(plane_bullet_x == layout1[0] || (plane_bullet_x == layout1[0] + 1) || (plane_bullet_x == layout1[0] + 2) || (plane_bullet_x == layout1[0] + 3) || (plane_bullet_x == layout1[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,layout1[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout1[0] = 0;
		}
		else if(plane_bullet_x + 1 == layout1[0] || (plane_bullet_x + 1 == layout1[0] + 1) || (plane_bullet_x + 1 == layout1[0] + 2) || (plane_bullet_x + 1 == layout1[0] + 3) || (plane_bullet_x + 1 == layout1[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,plane_bullet_y);
			LCD_write_byte(0x00,1);
			LCD_set_XY(plane_bullet_x + 1,layout1[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout1[0] = 0;
		}
	}
	
	else if(plane_bullet_y == 2)
	{
		if(plane_bullet_x == layout2[0] || (plane_bullet_x == layout2[0] + 1) || (plane_bullet_x == layout2[0] + 2) || (plane_bullet_x == layout2[0] + 3) || (plane_bullet_x == layout2[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,layout2[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout2[0] = 0;
		}
		else if(plane_bullet_x + 1 == layout2[0] || (plane_bullet_x + 1 == layout2[0] + 1) || (plane_bullet_x + 1 == layout2[0] + 2) || (plane_bullet_x + 1 == layout2[0] + 3) || (plane_bullet_x + 1 == layout2[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,plane_bullet_y);
			LCD_write_byte(0x00,1);
			LCD_set_XY(plane_bullet_x + 1,layout2[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout2[0] = 0;
		}
	}
	
	else if(plane_bullet_y == 3)
	{
		if(plane_bullet_x == layout3[0] || (plane_bullet_x == layout3[0] + 1) || (plane_bullet_x == layout3[0] + 2) || (plane_bullet_x == layout3[0] + 3) || (plane_bullet_x == layout3[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,layout3[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout3[0] = 0;
		}
		else if(plane_bullet_x + 1 == layout3[0] || (plane_bullet_x + 1 == layout3[0] + 1) || (plane_bullet_x + 1 == layout3[0] + 2) || (plane_bullet_x + 1 == layout3[0] + 3) || (plane_bullet_x + 1 == layout3[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,plane_bullet_y);
			LCD_write_byte(0x00,1);
			LCD_set_XY(plane_bullet_x + 1,layout3[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout3[0] = 0;
		}
	}
	
	else if(plane_bullet_y == 4)
	{
		if(plane_bullet_x == layout4[0] || (plane_bullet_x == layout4[0] + 1) || (plane_bullet_x == layout4[0] + 2) || (plane_bullet_x == layout4[0] + 3) || (plane_bullet_x == layout4[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,layout4[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout4[0] = 0;
		}
		else if(plane_bullet_x + 1 == layout4[0] || (plane_bullet_x + 1 == layout4[0] + 1) || (plane_bullet_x + 1 == layout4[0] + 2) || (plane_bullet_x + 1 == layout4[0] + 3) || (plane_bullet_x + 1 == layout4[0] + 4))
		{
			LCD_set_XY(plane_bullet_x,plane_bullet_y);
			LCD_write_byte(0x00,1);
			LCD_set_XY(plane_bullet_x + 1,layout4[0]);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			LCD_write_byte(0x00,1);
			plane_bullet_x = 0;
			plane_bullet_y = 0;
			layout4[0] = 0;
		}
	}
}


void sel3_menu()
{
	LCDFull(0x00);
	LCD_write_english_string(0,0,"  AircraftWar");
	LCD_write_english_string(0,2,"     ^ ^");
	LCD_write_english_string(0,3,"      -");
	LCD_write_english_string(0,4," anykeytoplay");
	LCD_write_english_string(0,5,"    By Chen");
}

void sel3_menu_work()
{
	unsigned char sel3_menu_work_flag = 1;
	unsigned char game_init = 0;
	unsigned char layout_number = 0;
	unsigned char i,j;
	unsigned char plane_die = 0;
	while(sel3_menu_work_flag)
	{
		if(time_1s_ok)
		{
			time_1s_ok = 0;
			if(plane_is_die())
			    plane_die = 1;
			
			if(!plane_die)
			{
			    if(game_init)
		    	{
				    LCDFull(0x00);					//清屏
					layout5[0] = layout4[0];		//障碍物下滑
				    layout4[0] = layout3[0];
				    layout3[0] = layout2[0];
				    layout2[0] = layout1[0];
				    layout1[0] = layout0[0];
				
				    layout0[0] = layout_number;		//伪随机生成障碍物
				    layout_number += 22;
				    if(layout_number >= 80)
					    layout_number = layout_number % 80;
				
				    LCD_set_XY(layout0[0],0);		//画障碍物
				    for(i = 0;i < 5;i++)
				        LCD_write_byte(layout0[1],1);
				    LCD_set_XY(layout1[0],1);
				    for(i = 0;i < 5;i++)
					    LCD_write_byte(layout1[1],1);
				    LCD_set_XY(layout2[0],2);
				    for(i = 0;i < 5;i++)
				    	LCD_write_byte(layout2[1],1);
				    LCD_set_XY(layout3[0],3);
				    for(i = 0;i < 5;i++)
				    	LCD_write_byte(layout3[1],1);
				    LCD_set_XY(layout4[0],4);
				    for(i = 0;i < 5;i++)
					    LCD_write_byte(layout4[1],1);
				    LCD_set_XY(layout5[0],5);
				    for(i = 0;i < 5;i++)
					    LCD_write_byte(layout5[1],1);
				
				    LCD_set_XY(plane_x,plane_y);	//画飞机，一个H字母
				    LCD_write_byte(0XF8,1);
					LCD_write_byte(0X20,1);
					LCD_write_byte(0X20,1);
					LCD_write_byte(0XF8,1);
					
					if(is_has_bullet())
					{
						plane_bullet_move();
						plane_bullet_want_die();
					}
			    }
			}
			else
			{
			    game_over();
				sel3_menu_work_flag = 0;
			}
		}
		if(time_10ms_ok)
		{
			time_10ms_ok = 0;
			switch(read_key())
			{
				case SW8:
					if(game_init == 0)
					{
						LCDFull(0x00);
						game_init = 1;
					}
					else
						plane_left_move();
					break;
				case key1_short:
					if(game_init == 0)
					{
						LCDFull(0x00);
						game_init = 1;
					}
					else
						plane_right_move();
					break;
				case key1_long:
					if(game_init == 0)
					{
					    LCDFull(0x00);
						game_init = 1;
					} 
					else
					{
						if(!is_has_bullet())
						{
							plane_bullet_x = plane_x + 1;
							plane_bullet_y = 5;
						}
					}
					break;
			}
		}
	}
}




void main(void)
{
	unsigned char menu_sel = 0;
	unsigned char i;
	
	init_devices();
	LCDInit();
	UARTSend(0x55);
	LCDFull(0x00);
	main_menu();		//主界面
	
	while(1)
	{
		if(time_10ms_ok)
		{
			time_10ms_ok = 0;
			switch(read_key())
			{
				case SW8:	//选择功能
					LCD_set_XY(0,menu_sel * 2);		//清除选择项
					for(i = 0;i < 12;i++)
						LCD_write_byte(0x00,1);
					LCD_set_XY(0,menu_sel * 2 + 1);
					for(i = 0;i < 12;i++)
						LCD_write_byte(0x00,1);
					
					if(menu_sel == 2)
						menu_sel = 0;
					else
						menu_sel++;
					
					LCD_DispCHstr(0,menu_sel * 2,"》");		//重新画选择项
				break;
				
				case key1_short:
					LCDFull(0x00);
					if(menu_sel == 0)
					{
						menu_sel = 0;
						sel1_menu();
						sel1_menu_work();
					}
					else if(menu_sel == 1)
					{
						menu_sel = 0;
						sel2_menu();
						sel2_menu_work();
					}
					else
					{
						menu_sel = 0;
						sel3_menu();
						sel3_menu_work();
					}
					break;
			}
		}
	}
}