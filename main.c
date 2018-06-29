/*
 * infinity 2 phase 3.c
 *
 * Created: 30/06/2018 12:09:49 ص
 * Author : MohameD AhmeD
 */ 
#define F_CPU 8000000UL
#define  PI 3.14159265359
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>


void InitPWM(){
	
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);
}

void pulse(uint8_t duty){
	OCR0=duty;	
}
void Forward(void){
	PORTA |=(1<<PA1) | (1<<PA3);
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA0 );
}

void Left(void){
	PORTA |=(1<<PA1) | (1<<PA2);
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA3 );
}

void Right(void){
	PORTA |=(1<<PA0) | (1<<PA3);
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA1 );
}

void Backward(void){ 
	PORTA |=(1<<PA0) | (1<<PA2);
	PORTA &= ~( 1 << PA3 );
	PORTA &= ~( 1 << PA1 );
}

void Stop(void){
	
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
}

uint16_t GoStraight(uint8_t distance){	
return distance /0.0925;
}

uint16_t Rotation(uint8_t Angle){
	return Angle *3.334;
}



void Regtangle(void){
for(uint8_t i = 0 ; i < 4 ;i++ ){
	PORTA |=(1<<PA1) | (1<<PA3);
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA0 );
	_delay_ms(GoStraight(42));
	
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(500);
	
	PORTA |=(1<<PA1) | (1<<PA2);
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(Rotation(100));
	
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(500);
}
	}
	
	
void Circle(void){
for (uint8_t i = 0 ; i <35 ; i++)
{
	PORTA |=(1<<PA1) | (1<<PA3); //front 
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA0 );
	_delay_ms(GoStraight(7));
	
	PORTA &= ~( 1 << PA0 ); // stop
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(10);
	
	PORTA |=(1<<PA1) | (1<<PA2); //left
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(Rotation(18));
	
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(10);
}
}

 
 

void Infinty2(void){
	uint8_t y = 15 ;
	
	for (uint8_t i = 0; i < 9; i++)   //Start with quarter circle from right of the area
	{
		
		PORTA |=(1<<PA1) | (1<<PA3);
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA0 );
		_delay_ms(GoStraight(7));
		
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(10);
		
		PORTA |=(1<<PA1) | (1<<PA2);
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(Rotation(18));
		
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(10);
		
	}
	// then rotate 30 degree left to be ready  to take straight line
	PORTA |=(1<<PA1) | (1<<PA2);
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(Rotation(30));
	
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(10);
	// taking straight line
	 for (uint8_t i = 0 ; i <35 ; i++)
	 {
		 PORTA |=(1<<PA1) | (1<<PA3); //front
		 PORTA &= ~( 1 << PA2 );
		 PORTA &= ~( 1 << PA0 );
		 _delay_ms(GoStraight(15));
		 
		 PORTA &= ~( 1 << PA0 ); // stop
		 PORTA &= ~( 1 << PA1 );
		 PORTA &= ~( 1 << PA2 );
		 PORTA &= ~( 1 << PA3 );
		 _delay_ms(10);
		 
		 PORTA |=(1<<PA1) | (1<<PA2); //left
		 PORTA &= ~( 1 << PA0 );
		 PORTA &= ~( 1 << PA3 );
		 _delay_ms(Rotation(16));
		 
		 PORTA &= ~( 1 << PA0 );
		 PORTA &= ~( 1 << PA1 );
		 PORTA &= ~( 1 << PA2 );
		 PORTA &= ~( 1 << PA3 );
		 _delay_ms(10);
		  y++;
		  if (y==110)
		  {
			  break ;
		  }
		 }
		y=15;
		 
	 
	 
	
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(10);
	// turn right with 30 degree  to be ready to take half circle
	PORTA |=(1<<PA0) | (1<<PA3);
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	_delay_ms(Rotation(30));
	
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(10);
	// taking the half circle
	for (uint8_t i = 0; i < 9; i++)
	{
		
		PORTA |=(1<<PA1) | (1<<PA3);
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA0 );
		_delay_ms(GoStraight(7));
		
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(10);
		
		PORTA |=(1<<PA0) | (1<<PA3);
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		_delay_ms(Rotation(16));
		
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(10);
	}
	
	//turn right with 30 degree to be ready to take the striaght line
	PORTA |=(1<<PA0) | (1<<PA3);
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	_delay_ms(Rotation(30));
	
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(10);
	// taking the straight line
	  for (uint8_t i = 0 ; i <35 ; i++)
	  {
		  PORTA |=(1<<PA1) | (1<<PA3); //front
		  PORTA &= ~( 1 << PA2 );
		  PORTA &= ~( 1 << PA0 );
		  _delay_ms(GoStraight(15));
		  
		  PORTA &= ~( 1 << PA0 ); // stop
		  PORTA &= ~( 1 << PA1 );
		  PORTA &= ~( 1 << PA2 );
		  PORTA &= ~( 1 << PA3 );
		  _delay_ms(10);
		  
		  PORTA |=(1<<PA0) | (1<<PA3); // turn right 
		  PORTA &= ~( 1 << PA2 );
		  PORTA &= ~( 1 << PA1 );
		  
		  PORTA &= ~( 1 << PA0 );
		  PORTA &= ~( 1 << PA1 );
		  PORTA &= ~( 1 << PA2 );
		  PORTA &= ~( 1 << PA3 );
		  _delay_ms(10);
		    y++;
		    if (y==110)
		    {
			    break ;
		    }
	  }
	
	  
  
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(10);
	// turn left with 30 degree to be ready to take the quarter circle 
	PORTA |=(1<<PA1) | (1<<PA2);
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(Rotation(30));
	
	PORTA &= ~( 1 << PA0 );
	PORTA &= ~( 1 << PA1 );
	PORTA &= ~( 1 << PA2 );
	PORTA &= ~( 1 << PA3 );
	_delay_ms(10);
	// taking the quarter circle
	for (uint8_t i = 0; i < 9; i++)
	{
		
		PORTA |=(1<<PA1) | (1<<PA3);
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA0 );
		_delay_ms(GoStraight(7));
		
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(10);
		
		PORTA |=(1<<PA1) | (1<<PA2);
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(Rotation(18));
		
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(10);
		
	}
}





int main(void)
{   
	 
	InitPWM();
	DDRA = 0xFF;
	DDRB |= (1<<PB3);
		
    /* Replace with your application code */
    while (1) 
    {
		PORTA |= (1<<PA4);
		_delay_ms(1000);
		pulse(215);
		Infinty2();
		
  /*    for (Theta = (PI/36) ; Theta < 2*PI ; Theta= Theta + (PI/36))
      {
	     r =  50 * ((sqrt(cos(2* Theta))) - (sqrt(cos((Theta-(PI/36))*2))));
	
	      PORTA |=(1<<PA1) | (1<<PA3);
	      PORTA &= ~( 1 << PA2 );
	      PORTA &= ~( 1 << PA0 );
	      _delay_ms(GoStraight(r));
	
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA3 );
			_delay_ms(10);
	
		PORTA |=(1<<PA1) | (1<<PA2);
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(Rotation(5));
	
		PORTA &= ~( 1 << PA0 );
		PORTA &= ~( 1 << PA1 );
		PORTA &= ~( 1 << PA2 );
		PORTA &= ~( 1 << PA3 );
		_delay_ms(10);
	
	}  
	*/
		
			PORTA &= ~( 1 << PA0 );
			PORTA &= ~( 1 << PA1 );
			PORTA &= ~( 1 << PA2 );
			PORTA &= ~( 1 << PA3 );
			pulse(0);
			PORTA &= ~(1<<PA4);
			_delay_ms(11000);
	}
}
/* for straight distance
delayTime = 60 /0.0925; // speed cm/ms
_delay_ms(delayTime);
*/

/*for rotation
delayTimeRotation = 90 * 3.33334;
_delay_ms(delayTimeRotation);
*/