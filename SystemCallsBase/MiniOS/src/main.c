//
//	------------     MiniOS entry point     -------------
//

#include "minios/system.h"
#include "minios/hal/hal.h"
#include "minios/console/console.h"

bool gameover = false;

int main(void)
{
	/*//Initializes the system
	system_init();		
	
	//Execute the console
	console_begin( "\n\r" ); //Some serial console like putty use \n\r as newlines,
							 //others like Atmel's Terminal use only \n. Choose accordingly.

	while(1); //if main returns we want to stop here...
			  //else garbage gets executed.
			  //Q: why? (Hint: Picture machine code in memory)*/
	
	while (true)
	{
		//display start screen
		// press any button to start
		
		// wait for button to be pressed
		
		// initially display game state
		
		while (!gameover)
		{
			// do a delay
			hal_delay(2000);
			
			// was a button pressed 
			// if yes handle it
			
			// display the new game stat
		}
		
		// game is over -> display gameoverstate
		
		// wait for button to be pressed for a new game state
	}
}

