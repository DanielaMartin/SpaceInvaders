//
//	------------     MiniOS entry point     -------------
//

#include "minios/system.h"
#include "minios/hal/hal.h"
#include "minios/console/console.h"

int main(void)
{
	//Initializes the system
	system_init();		
	
	//Execute the console
	console_begin( "\n\r" ); //Some serial console like putty use \n\r as newlines,
							 //others like Atmel's Terminal use only \n. Choose accordingly.

	while(1); //if main returns we want to stop here...
			  //else garbage gets executed.
			  //Q: why? (Hint: Picture machine code in memory)
}

