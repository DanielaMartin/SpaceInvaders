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
	
struct shape;

void move_shape(gfx_shape shp, int x, int y);
shape make_shape(gfx_shape shape, int x, int y);
void draw_shape(shape shp);
void alien_invade(shape aliens[]);
void shoot(gfx_shape ship, shape[] aliens);

//	This function will be used to
void display();


#endif /* INCFILE1_H_ */