/*
 * IncFile1.h
 *
 * Created: 2018-11-06 12:27:34 PM
 *  Author: CaLePegasus
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <stdint-gcc.h>	//defs for size-specific primitive data types
#include <stdbool.h>

typedef uint32_t gfx_shape;
typedef uint32_t alien_shape;

enum gfx_shape{alien = 0, ship, bullet};
enum alien_shape {type1 = 0, type2, type3};
	
typedef struct shape {
	char body;
	uint16_t x;
	uint16_t y;
	bool exists;
} Shape;

void move_shape(gfx_shape shp, uint16_t x, uint16_t y);
Shape make_shape(gfx_shape shp, uint16_t x, uint16_t y);
void draw_shape(Shape* shp);
void alien_invade(Shape* aliens[]);
void shoot(gfx_shape ship, Shape aliens []);

void move_shape_up(Shape* shp);
void move_shape_down(Shape* shp);
void move_shape_left(Shape* shp);
void move_shape_right(Shape* shp);

//	This function will be used to
void display();


#endif /* INCFILE1_H_ */