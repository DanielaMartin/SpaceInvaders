/*
 * IncFile1.h
 *
 * Created: 2018-11-06 12:27:34 PM
 *  Author: CaLePegasus
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

enum gfx_shape{alien, ship, bullet};
enum alien_shape {type1, type2, type3};
	
struct shape(pos position, gfx_shape shp);
struct pos(gfx_shape shape, uint32_t x, uint32_t y);

void move_shape(gfx_shape shape, pos new_pos);
void draw_shape(gfx_shape shape);
void alien_invade(shape[] aliens);
void shoot(gfx_shape ship, shape[] aliens);
void 

//	This function will be used to
void display();


#endif /* INCFILE1_H_ */