//
//	------------     MiniOS entry point     -------------
//

#include "minios/system.h"
#include "minios/hal/hal.h"
#include "minios/console/console.h"
#include "space_inv.h"

#define ALIEN_NUM 15
bool gameover = false;
bool button_pressed = false;
tButtonNum seleced_button;

// shape instances
Shape spaceship;
Shape aliens [ALIEN_NUM];
Shape bullets;


void button_callback (tButtonNum);

int main(void)
{
	//Initializes the system
	system_init();		
	
	/*//Execute the console
	console_begin( "\n\r" ); //Some serial console like putty use \n\r as newlines,
							 //others like Atmel's Terminal use only \n. Choose accordingly.

	while(1); //if main returns we want to stop here...
			  //else garbage gets executed.
			  //Q: why? (Hint: Picture machine code in memory)*/
	
	// start button
	hal_button_start_int(button_callback);
	
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
			if (button_pressed)
			{
				switch(seleced_button)
				{
					case Button1:
						// move the space ship up wards
						move_shape_up(spaceship);
						break;
					case  Button2:
						// shoot a bullet from the position of the space ship
						break;
					case Button3:
						// move the space ship down wards
						move_shape_down(spaceship);
						break;
					default:
						/*Error*/
						break;
				}
				button_pressed = false;
			}
			
			// display the new game stat
			// including move all existing bullets one step to the right
			// move every thing else every second or third time
		}
		
		// game is over -> display gameoverstate
		
		// wait for button to be pressed for a new game state
	}
}

void button_callback (tButtonNum b)
{
	button_pressed = true;
	seleced_button = b;
}

