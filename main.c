
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0b11111111;
    while (1) 
    {
		PORTA = 0b00000001;
		_delay_ms(2000);
		PORTA = 0b00000010;
		_delay_ms(2000);
		PORTA = 0b00000000;
		_delay_ms(2000);
    }
	return 0;
}

