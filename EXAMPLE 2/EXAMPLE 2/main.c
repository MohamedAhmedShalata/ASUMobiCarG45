
#define F_CPU 10000000UL
#include <avr/io.h>


int main(void)
{
   DDRA = 0b00000111;
   DDRB = 0b00000000;
   PORTB = 0b11111111;
    while (1) 
    {
		if (PINB == 0b11111110)  {PORTA = 0b00000001;}           //button 1 pressed
			
			else if (PINB == 0b11111101)  {PORTA = 0b00000011;}  //button 2 pressed
				
				else if (PINB == 0b11111011)  {PORTA = 0b00000111;}  //button 3 pressed
					
					else {PORTA = 0b00000000;}
    }
 return 0;
				}
 

