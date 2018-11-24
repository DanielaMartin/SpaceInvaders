//
//	------------     MiniOS entry point     -------------
//

#include "minios/system.h"
#include "minios/hal/hal.h"
#include "space_inv.h"
#include <stddef.h>
#include <stdbool.h>
#include <asf.h>

#define ALIEN_NUM 15
#define ALIEN_UPDATE 5

bool gameover = false;
bool button_pressed = false;
tButtonNum seleced_button;

// shape instances
Shape* spaceship;
Shape* aliens [ALIEN_NUM];
Shape* bullets;

bool aliens_at_top = true;
uint16_t update_alien = 0;

void button_callback (tButtonNum);
void move_aliens (void);

int main(void)
{
	//Initializes the system
	system_init();		
//	sysclk_init();
//	board_init();
	
	// start button
	hal_button_start_int(button_callback);
	
	while (true)
	{
		gameover = false;
		//display start screen
		// press any button to start
		
		// wait for button to be pressed
		
		// initially display game state
		// create all the aliens
		// a block of 3*5 aliens at the top right corner of the screen
		// start at position (10,0)
		/*uint16_t x = 0;
		for (uint16_t i = 0; i < ALIEN_NUM; i++)
		{
			Shape Alien = make_shape(alien, (x + 10), i % 3);
			aliens[i] = &Alien;
			x = ((i % 3) == 2) ? x+1 : x;
		}*/
		Shape Alien = make_shape(alien, 10, 0);
		aliens[0] = &Alien;
		Shape Alien1 = make_shape(alien, 10, 1);
		aliens[1] = &Alien1;
		 Shape Alien2 = make_shape(alien, 10, 2);
		aliens[2] = &Alien2;
		Shape Alien3 = make_shape(alien, 11, 0);
		aliens[3] = &Alien3;
		Shape Alien4 = make_shape(alien, 11, 1);
		aliens[4] = &Alien4;
		Shape Alien5 = make_shape(alien, 11, 2);
		aliens[5] = &Alien5;
		Shape Alien6 = make_shape(alien, 12, 0);
		aliens[6] = &Alien6;
		Shape Alien7 = make_shape(alien, 12, 1);
		aliens[7] = &Alien7;
		Shape Alien8 = make_shape(alien, 12, 2);
		aliens[8] = &Alien8;
		Shape Alien9 = make_shape(alien, 13, 0);
		aliens[9] = &Alien9;
		Shape Alien10 = make_shape(alien, 13, 1);
		aliens[10] = &Alien10;
		Shape Alien11 = make_shape(alien, 13, 2);
		aliens[11] = &Alien11;
		Shape Alien12 = make_shape(alien, 14, 0);
		aliens[12] = &Alien12;
		Shape Alien13 = make_shape(alien, 14, 1);
		aliens[13] = &Alien13;
		Shape Alien14 = make_shape(alien, 14, 2);
		aliens[14] = &Alien14;
		
		// initialize the spaceship
		Shape Ship = make_shape(ship, 0, 2);
		spaceship = &Ship;
		
		// create a bullet and set it to not existing
		Shape Bullet = make_shape(bullet, 0, 0);
		bullets = &Bullet;
		bullets->exists = false;
		
		// display all the aliens and the space ship
		for (uint16_t i = 0; i < ALIEN_NUM; i++)
		{
			draw_shape(aliens[i]);
		}
		draw_shape(spaceship);
		
		
		while (!gameover)
		{
			// do a delay
			hal_delay(200);
			
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
						if (!bullets->exists)
						{
							// create a new bullet
							// set bullet position
							// it should be the position right to the current position of the spaceship 
						//	bullets = make_shape(bullet, (spaceship->x + 1), spaceship->y);
							bullets->exists = true;
							bullets->x = spaceship->x + 1;
							bullets->y = spaceship->y;
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
			
			// check if the bullet reached the end of the screen
			if (bullets->x == 15)
				// destroy the bullet
				bullets->exists = false;
			
			// advance bullets
			if (bullets->exists)
				move_shape_right(bullets);
				
			// move the aliens every second or third time
			if (update_alien == ALIEN_UPDATE)
				move_aliens();
			
			update_alien = (update_alien == ALIEN_UPDATE) ? 0 : update_alien + 1;
			
			bool collision_found = false;
			Shape* collided_alian = NULL;
			// check for collisions
			for (uint16_t i = 0; i < ALIEN_NUM; i++)
			{
				Shape* current_alien = aliens[i];
				if (bullets->exists && (current_alien->x == bullets->x) && (current_alien->y == bullets->y) && current_alien->exists)
				{
					collision_found = true;
					collided_alian = current_alien;
				}
			}
			
			if (collision_found)
			{
				collided_alian->exists = false;
				bullets->exists = false;
			}
			
			
			// display the new game stat
			// display all the aliens and the space ship
			// remove old game state
			hal_display_cls();
			
			for (uint16_t i = 0; i < 15; i++)
			{
				// if the alien is still alive
				if (aliens[i]->exists)
					draw_shape(aliens[i]);
			}
			//draw_shape(alien_test);
			draw_shape(spaceship);
			if (bullets->exists)
				draw_shape(bullets);
			
			// check if all the aliens are gone -> then game is over
		
		
		// game is over -> display gameover state
		// game is over when the aliens have reached the left side of the screen
		for (uint16_t i = 0; i < ALIEN_NUM; i++)
		{
			Shape* current_alien = aliens[i];
			if ((current_alien->x == 0) && current_alien->exists)
			{
				gameover = true;
			}
		}
		}
		// wait for button to be pressed for a new game state
		
		//display gameover screen
		hal_display_cls();
			
		// wait for button to be pressed
		while(!button_pressed)
		{
			hal_led_write(Led1, LedOn);
			hal_led_write(Led2, LedOn);
			hal_led_write(Led3, LedOn);
			hal_led_write(Led1, LedOff);
			hal_led_write(Led2, LedOff);
			hal_led_write(Led3, LedOff);
		}
		button_pressed = false;
	}
}

void button_callback (tButtonNum b)
{
	button_pressed = true;
	seleced_button = b;
}

void move_aliens ()
{
	//move all the aliens in a sort of zig zag movement
	bool move_down = aliens_at_top;
	for (uint16_t i = 0; i<ALIEN_NUM; i++)
	{
		if (move_down)
		{
			// move alien down
			move_shape_down(aliens[i]);
		} else {
			// else move it up
			move_shape_up(aliens[i]);
		}
		// and move the aliens to left
		move_shape_left(aliens[i]);
	}
	aliens_at_top = !move_down;
}

