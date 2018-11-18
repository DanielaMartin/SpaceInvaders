//
//	------------     MiniOS entry point     -------------
//

#include "minios/system.h"
#include "minios/hal/hal.h"
#include "minios/console/console.h"
#include "space_inv.h"
#include <stddef.h>
#include <stdbool.h>

#define ALIEN_NUM 15
//#define NULL 0

bool gameover = false;
bool button_pressed = false;
tButtonNum seleced_button;

// shape instances
Shape spaceship;
Shape aliens [ALIEN_NUM];
Shape bullets;
bool hasBullet = false;



void button_callback (tButtonNum);

int main(void)
{
	//Initializes the system
	system_init();		
	
	// start button
	hal_button_start_int(button_callback);
	
	while (true)
	{
		//display start screen
		// press any button to start
		
		// wait for button to be pressed
		
		// initially display game state
		// create all the aliens
		// a block of 3*5 aliens at the top right corner of the screen
		// start at position (10,0)
		uint16_t x = 0;
		for (uint16_t i = 0; i < 15; i++)
		{
			//TODO: check if this really works
			aliens[i] = make_shape(alien, x + 10, i % 4);
			x = (i % 4 == 3) ? x+1 : x;
		}
		
		// initialize the spaceship
		spaceship = make_shape(ship, 0, 2);
		
		// display all the aliens and the space ship
		for (uint16_t i = 0; i < 15; i++)
		{
			draw_shape(aliens[i]);
		}
		draw_shape(spaceship);
		
		
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
						// is there a bullet already? if yes do not shoot.
						// if no shoot
						if (!hasBullet)
						{
							// create a new bullet
							// set bullet position
							// it should be the position right to the current position of the spaceship 
							bullets = make_shape(bullet, (spaceship.x + 1), spaceship.y);
							hasBullet = true;
						}
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
			
			// advance bullets
			if (hasBullet)
				move_shape_right(bullets);
			
			// check for collisions
			
			// display the new game stat
			// including move all existing bullets one step to the right
			// move every thing else every second or third time
			
			// check if all the aliens are gone -> then game is over
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

