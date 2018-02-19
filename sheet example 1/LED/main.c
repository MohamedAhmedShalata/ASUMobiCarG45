/*
 */
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

    DDRA=0b00000001;


    while(1) {
        PORTA=0b00000001;
       _delay_ms(200);
        PORTA=0b00000000;
       _delay_ms(700);
    }


    return 0;
}
