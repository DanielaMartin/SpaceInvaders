//
//	------------     MiniOS entry point     -------------
//

#include "minios/system.h"
#include "minios/hal/hal.h"
#include "space_inv.h"
#include <stddef.h>
#include <stdbool.h>
#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALIEN_NUM 15
#define ALIEN_UPDATE 5

tLedState led_state = LedOff;
bool gameover = false;
bool button_pressed = false;
tButtonNum seleced_button;

// shape instances
Shape* spaceship;
Shape* aliens [ALIEN_NUM];
Shape* bullets;

bool aliens_at_top = true;
uint16_t update_alien = 0;
uint16_t score = 0;

void button_callback (tButtonNum);
void move_aliens (void);
void print_string (uint8_t*);

int main(void)
{
	//Initializes the system
	system_init();		
	
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
		Shape *Alien = malloc(15*sizeof(Shape));
		uint16_t k=0;
		for (uint16_t i=10; i<15; i++) {
			for (uint16_t j=0; j<3; j++) {
				Alien[k] = make_shape(alien, i, j);
				aliens[k] = &Alien[k];
				k++;
			}
		}
		aliens_at_top = true;
		
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
		
		// set the score to 0
		score = 0;
		
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
				move_aliens();//bug here?
			
			update_alien = (update_alien == ALIEN_UPDATE) ? 0 : update_alien + 1;
			
			bool collision_found = false;
			Shape* collided_alien = NULL;
			// check for collisions
			for (uint16_t i = 0; i < ALIEN_NUM; i++)
			{
				Shape* current_alien = aliens[i];
				if (bullets->exists && (current_alien->x == bullets->x) && (current_alien->y == bullets->y) && current_alien->exists)
				{
					collision_found = true;
					collided_alien = current_alien;
				}
			}
			
			if (collision_found)
			{
				collided_alien->exists = false;
				bullets->exists = false;
				score += 10;
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
		free(Alien);
		//display gameover screen
		hal_display_cls();
		uint8_t string [20];
		sprintf(string, "Score: %d", score);
		print_string(string);
			
		// wait for button to be pressed
		while(!button_pressed)
		{
			hal_led_write(Led1, !led_state);
			hal_led_write(Led2, !led_state);
			hal_led_write(Led3, !led_state);
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

void print_string (uint8_t* string)
{
	for (uint i = 0; i < strlen(string); i++)	
	{
		hal_display_putc(string[i]);
	}
}

