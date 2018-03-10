#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void INIT_INTERUPT(){

    DDRD &=~(1<<PD2);
    PORTD|=(1<<PD2);
    MCUCR|=(1<<ISC01);
    GICR|=(1<<INT0);

    sei();
}
//not sure this will work
void run_interupt(){

    ISR(INT0_vect){
       PORTA =0x00;
    }

}
