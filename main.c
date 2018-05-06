#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>

void init_PWM(void);
void PWM_PD7(unsigned char pulse_width);

int main(void)
{	
init_PWM();
	DDRB = 0;
	PORTB = 0xFF;
	DDRA = 0x0F;
	uint8_t pressed = 10;
	while(1)
	{
	  
	if((PINB == 0b11111011) || (PINB == 0b11100000)) // go forward
		{
		pressed = 0;
		PWM_PD7(150);
		
		PORTA |=(1<<PA1) | (1<<PA3);
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA0 );
		}
else if ((PINB == 0b11111100) || (PINB == 0b11111110)|| (PINB == 0b11111101))  // go RIGHT
		{
		pressed = 1;
		PWM_PD7(150);
			
		PORTA |= ( 1 << PA1 ) | ( 1 << PA2 );
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA3 );
		
		}
		
else if ((PINB == 0b11100111) || (PINB == 0b11101111)|| (PINB == 0b11110111)) // go Left
		{
		pressed = 2;
		PWM_PD7(150);
					
        PORTA |= ( 1 << PA0 ) | ( 1 << PA3 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		}
else if (PINB == 0b11111111)  // 
		{
		 if(pressed == 0)
		 {  
			PWM_PD7(150);
					
			PORTA |=(1<<PA2) | (1<<PA0);
			PORTA &= ~( 1 << PA1 );
			PORTA &= ~( 1 << PA3 );

		 }
	else if(pressed == 1)
			{
			PWM_PD7(150);
					
		PORTA |= ( 1 << PA1 ) | ( 1 << PA2 );
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA3 );
			}
	else if(pressed == 2)
			{
			PWM_PD7(150);
					
		PORTA |= ( 1 << PA0 ) | ( 1 << PA3 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
			
			
			}
		else
			pressed = 10;
		}
		
		
	}
	return 0;
}


void init_PWM(void)
	{

		//DDRB  |=(1<<PB3	);
		DDRD  |=(1<<PD7); //(1<<PD4)|(1<<PD5)|

		//TCCR0 |=(1<<WGM00)|(1<<COM01)|(1<<CS01)|(1<<CS00); // TCNT0(counter) & OCR0(analog value) (1<<COM00)||(1<<WGM01) 
		TCCR2 |=(1<<WGM20)|(1<<COM21)|(1<<CS22);  // TCNT2(counter) & OCR2(analog value) |(1<<COM20)|(1<<CS21) 
		//TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM10); // TCNT1(counter) & CR1AL(analog value) (1<<COM1B0)|(1<<COM1A0)|

			//Start PWM
		//TCCR1B|=(1<<CS11)|(1<<CS10); //TCNT1(counter) & CR1BL(analog value)
		//TCNT0  =0;
		TCNT2  =0;
		//TCNT1  =0;

	}

/*void PWM_PB3(unsigned char pulse_width)
	{
		OCR0   = pulse_width;
	}
*/

void PWM_PD7(unsigned char pulse_width)
	{
		OCR2   = pulse_width;
	}

