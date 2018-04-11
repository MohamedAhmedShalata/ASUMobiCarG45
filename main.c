/*
 * line follower with 3 sensors.c
 *
 * Created: 09/04/2018 09:16:05 ص
 * Author : MohameD AhmeD
 */ 

 #define F_CPU 16000000UL
  #include <avr/io.h>

 void controlMotor (char m)
 {
  

    if (m=='F')
    {
	PORTC=0b00001010;
    }
	 if (m=='L')
	 {
	PORTC=0b00001001;
	 }
	 if (m=='R')
	 {
	 PORTC=0b00000110;
 	 }
	 
 }
 int main (void)
 {

 
 DDRB =0x00;
  DDRC=0xff;
   char F,L,R;

 while (1)
 {
	 // pB0 for right sensor
	 // pB1 for middle sensor
	 // pB2 for left sensor

	 if ((PINB &(1<<PB0)) && !(PINB &(1<<PB1)) && (PINB &(1<<PB2))){
		 controlMotor(F);
	 }
	 if (!(PINB &(1<<PB0)) && !(PINB &(1<<PB1)) && !(PINB &(1<<PB2))){
		 controlMotor(F);
	 }
	 if ((PINB &(1<<PB0)) && (PINB &(1<<PB1)) && (PINB &(1<<PB2))){
		 controlMotor(F);
	 }
	 if ((PINB &(1<<PB0)) && (PINB &(1<<PB1)) && !(PINB &(1<<PB2)))
	 {
		 controlMotor(L);
	 }
	 if ((PINB &(1<<PB0)) && !(PINB &(1<<PB1)) && !(PINB &(1<<PB2)))
	 {
		 controlMotor(L);
	 }
	 if (!(PINB &(1<<PB0)) && (PINB &(1<<PB1)) && (PINB &(1<<PB2)))
	 {
		 controlMotor(R);
	 }
	 if (!(PINB &(1<<PB0)) && !(PINB &(1<<PB1)) && (PINB &(1<<PB2)))
	 {
		 controlMotor(R);
	 }
 }
 }