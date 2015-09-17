//==========================================================================
//	Project				: Sample code for control single servo motors using delays
//						  This project is using 16F877A with 20MHz
//						  Has been try succesfully using SK40B
//						  
//						  Please make sure the hardware is compatible with this code
//
//	Project description	: This source code is used to control a servo motor.
//						  Servo motor will continuosly turn from one position to another position 
//						  Delay is use to calculate the pulse width timing. 
//						  The delay timing is depend on the crystal.
//						  Difference timing for difference crystal.	
//
//	Date				: Feb 2009
//==========================================================================
// 
//	include
//==========================================================================
#include <pic.h>   					// this sample code is using 16F877A !!
								
//	configuration
//==========================================================================
__CONFIG ( 0x3F32 );				//configuration for the  microcontroller
											
//	define
//==========================================================================
#define servo	RB1

#define	MHZ	*1000L				/* number of kHz in a MHz */
#define	KHZ	*1					/* number of kHz in a kHz */

// Value x must not more that 255
#define	DelayUs(x)	{ unsigned char _dcnt; \
			  _dcnt = (((x)*(20MHZ))/(24MHZ))|1; \
			  while(--_dcnt != 0) \
				  continue; \
			  _dcnt = (((x)*    (20MHZ))/(24MHZ))|1; \
			  while(--_dcnt != 0) \
				  continue; }


//	function 						(every function must have a function prototype)
//==========================================================================

void DelayMs(unsigned char y); 	// Value y must not more that 255
									// delay ms
//	main function					(main fucntion of the program)
//==========================================================================
void main(void)
{
	unsigned int i,a;
	
	//set IO port for servo pin 
	TRISB = 0b00000001;			//servo motor is RB1
	PORTB = 0b00000000;			//clear port B

								//servo will loop infinity
	while(1)					//from one position to another position
	{
		//*******************************************************
		//
		//Delay determine the servo motors position
		//Try change the value for different position 
		//
		//Value in DelayUs and DelayMs function must not more than 255
		//Otherwise the timing will not accurate!!
		//
		//******************************************************
		
		for(i=0;i<50;i++)		//continues pulse for 50 times
		{
			servo=1;			//set servo pin high
			DelayUs(250);
			DelayUs(250);
			DelayUs(200);		//delay	250+250+200= 700us = 0.7ms	
								//These delay only valid using 20MHz!
		
			servo=0;			//set servo pin low
			DelayMs(19);		//remain --> 20ms-0.7ms=19.3ms
			DelayUs(250);
			DelayUs(50);		//19ms+0.250ms+0.050ms=19.3ms
								//These delay only valid using 20MHz!
		}
		
		//  _	                _                  _
		// | |	               | |                | |
		// | |	               | |                | |              	~~50 times              
		// | |_________________| |________________| |____________________
		// 0.7ms    19ms      0.7ms      19ms     0.7ms   19ms
		// |				   |
		// |<-------20ms------>|
		
		for(i=0;i<50;i++)		//continues pulse for 50 times
		{
			servo=1;			//set servo pin high
			DelayMs(2);			//delay	2ms	
								//These delay only valid using 20MHz!
								
			servo=0;			//set servo pin low
			DelayMs(18);		//delay 18ms
								//These delay only valid using 20MHz!
		}	
			
		//  ___	                ___                 ___
		// |   |               |   |               |   |
		// |   |               |   |               |   |              ~~50 times       
		// |   |_______________|   |_______________|   |____________________
		//  2ms       18ms      2ms      18ms       2ms		18ms
		// |				   |
		// |<-------20ms------>|
	}
		
}
	
//subroutine
//============================================================================	
void DelayMs(unsigned char y)
{
	unsigned char	i;
	do {
		i = 4;
		do {
			DelayUs(250);
		} while(--i);
	} while(--y);
}
