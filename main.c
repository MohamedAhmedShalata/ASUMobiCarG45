#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <AVR/interrupt.h>
#include <inttypes.h>
#include <avr/sleep.h>
#define th1 128
#define th2 128
#define th3 128
#define th4 128
#define th5 128

#define LCD_E  PB2  // PORTD.5
#define LCD_RS PB0    //PORTD.4
#define LCD_RD PB7    // PORTB.7
#define LCD_WR PB1    // PORTB.6

#define LCD_CLR 0x01  // clear LCD
#define LCD_8BIT 0x38 // 8-bit mode
#define LCD_INC 0x06  //Increment, display freeze
#define LCD_MOV 0x10  //Cursor move, not shift
#define LCD_ALL  0x0F // LCD On, LCD display on, cursor on and blink on
#define LCD_ON           0x08      // turn lcd/cursor on
#define LCD_ON_DISPLAY   0x04      // turn display on
#define LCD_ON_CURSOR    0x02      // turn cursor on
#define LCD_ON_BLINK     0x01      // cursor blink
#define LCD_LINE1  0x80        // cursor Pos on line 1 (or with column)
#define LCD_LINE2  0xC0        // cursor Pos on line 2 (or with column)

unsigned char LCD_getaddr(void)
{
	unsigned char address;
	
	PORTB &= ~((1<<LCD_RS)|(1<<LCD_E));
	PORTB &= ~(1<<LCD_RD);
	PORTB |= (1<<LCD_WR);
	DDRC = 0;
	PORTB |= (1<<LCD_E);
	asm volatile ("nop");
	asm volatile ("nop");
	address = PINC;
	PORTB &= ~(1<<LCD_E);
	PORTB |= (1<<LCD_RD);
	PORTB &= ~(1<<LCD_WR);
	DDRC = 0xFF;
	return address;
}
void LCD_wait(void)
{
	while((LCD_getaddr() & 0x80) == 0x80)
	{
	}
}

void LCD_putchar(unsigned char data)
{
	LCD_wait();
	DDRC = 0xFF;
	PORTB |= ((1<<LCD_RS)|(1<<LCD_E));
	PORTC = data;
	asm volatile ("nop");
	asm volatile ("nop");
	asm volatile ("nop");
	asm volatile ("nop");
	PORTB &= ~(1<<LCD_E);
	DDRC = 0;
}
void LCD_command(unsigned char command){
	
	LCD_wait();
	DDRC = 0xFF;
	PORTB &= ~(1<<LCD_RS);
	PORTB |= (1<<LCD_E);
	PORTC = command;
	asm volatile ("nop");
	asm volatile ("nop");
	asm volatile ("nop");
	asm volatile ("nop");
	PORTB &= ~(1<<LCD_E);
	DDRC = 0;
}
void LCD_init(void)
{
	DDRB |= ((1<<LCD_RS)|(1<<LCD_E));
	PORTB &= ~((1<<LCD_RS)|(1<<LCD_E));
	DDRB |= ((1<<LCD_RD)|(1<<LCD_WR));
	PORTB &= ~(1<<LCD_WR);
	DDRC = 0xFF;
	_delay_ms(50);
	LCD_command(LCD_CLR);
	LCD_command(LCD_8BIT);
	LCD_command(LCD_INC);
	LCD_command(LCD_MOV);
	//LCD_command(LCD_ALL);     // can call all instead of next line
	LCD_command(LCD_ON | LCD_ON_DISPLAY );//| LCD_ON_CURSOR | LCD_ON_BLINK
}

void LCD_write(char* dstring)
{


	while(*dstring)
	{
		LCD_putchar(*dstring++);
	}
}


void pwm_init(void){
	TCCR0 = 0x6c;
	OCR0 = 0;
	TCCR2 = 0x6c;
	OCR2 = 0;
}
void port_init(){
	DDRC = 0xFF;
	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRA = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTB = 0x00;
	}void ADC_init(void){
	ADCSRA|=(1<<ADPS2);
	ADMUX|=(1<<ADLAR);
	ADMUX|=(1<<REFS0);
	//ADCSRA|=(1<<ADIE);
	ADCSRA|=(1<<ADEN);
	//sei();
	ADCSRA|=(1<<ADSC);
}


int main( void )
{
	int s1=0,s2=0,s3=0,s4=0,s5=0;
	LCD_init();
	pwm_init();
	port_init();
	ADC_init();
	unsigned char ch=0;
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xE0)|ch;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	s1=ADCH;

	ch++;
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xE0)|ch;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	s2=ADCH;
	
	ch++;
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xE0)|ch;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	s3=ADCH;
	
	ch++;
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xE0)|ch;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	s4=ADCH;
	
	ch++;
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xE0)|ch;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	s5=ADCH;
	while (1)
	{
		if(s1<th1 && s2<th2 &&s3>th3 && s4<th4 &&s5<th5)
		{
			PORTD = 0x05;//0101 right motor forword and left motor forword  FORWORD
			OCR0 = 255;
			OCR2 = 255;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2 | 0);
			LCD_write("FORWORD MOTION");
			_delay_ms(500);
		}
		//01110
		else if(s1<th1 && s2>=th2 && s3>=th3 && s4>=th4 && s5<th5)
		{
			PORTD = 0x05;//0101 right motor forword and left motor forword  FORWORD
			OCR0 = 255;
			OCR2 = 255;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2 | 0);
			LCD_write("FORWORD MOTION");
		}
		//00111
		else if(s1<th1 && s2<th2 && s3>=th3 && s4>=th4 && s5>=th5)
		{
			PORTD = 0x0d;//1101 right motor dynamic break left motor forword 90 DIG RIGHT
			OCR0 = 255;
			OCR2 = 255;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2 | 0);
			LCD_write("90* RIGHT TURN");
		}
		//11100
		else if(s1>=th1 && s2>=th2 && s3>=th3 && s4<th4 && s5<th5)
		{
			PORTD = 0x07;//0111 left motor dynamic break right motor forword  90 DIG LEFT
			OCR0 = 255;
			OCR2 = 255;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2 | 0);
			LCD_write("90* LEFT TURN");
		}

		//10100
		else if(s1>=th1 && s2<th2 && s3>=th3 && s4<th4 && s5<th5)
		{
			PORTD = 0x06;//0110 right motor forword and left motor backword  U TURN LEFT
			OCR0 = 255;
			OCR2 = 255;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2 | 0);
			LCD_write("LEFT U TURN");
		}

		//00101
		else if(s1<th1 && s2<th2 && s3>=th3 && s4<th4 && s5>=th5)
		{
			PORTD = 0x09;//1001 right motor backword and left motor forword  U TURN RIGHT
			OCR0 = 255;
			OCR2 = 255;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2 | 0);
			LCD_write("RIGHT U TURN");
		}
		//00110
		else if(s1<th1 && s2<th2 && s3>=th3 && s4>=th4 && s5<th5)
		{
			PORTD = 0x05;//0101 FORWORD BUT DIFFERENT SPEED ANGLE 135 DIG
			OCR0 = 255;
			OCR2 = 100;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2 | 0);
			LCD_write(" RIGHT 135* ");
		}

		//01100
		else if(s1<th1 && s2>=th2 && s3>=th3 && s4<th4 && s5<th5)
		{
			PORTD = 0x05;//0101 FORWORD BUT DIFFERENT SPEED ANGLE 135 DIG
			OCR0 = 100;
			OCR2 = 255;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2 | 0);
			LCD_write(" LEFT 135* ");
		}
		//11111
		else if(s1>=th1 && s2>=th2 && s3>=th3 && s4>=th4 && s5>=th5)
		{
			PORTD = 0x0F;//1001 right motor backword and left motor forword  U TURN RIGHT
			OCR0 = 255;
			OCR2 = 255;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2 | 0);
			LCD_write("FINAL STATE");
		}
		//00000
		else if(s1<th1 && s2<th2 && s3<th3 && s4<th4 && s5<th5)
		{
			PORTD = 0x0F;// 1111 stop by dynamic braking..   STOP
			OCR0 = 255;
			OCR2 = 255;
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS IN");
			LCD_command(LCD_LINE2| 0);
			LCD_write("STOP MODE");
		}
		// REST CONDITIONS WE WILL PUT ACCORDING TO THE AREENA
		else
		{
			LCD_command(LCD_LINE1);
			LCD_write("BOT IS ");
			LCD_command(LCD_LINE2);
			LCD_write("SEARCHING");
		}
	};
	return 0;
}﻿