/*
 * shape.c
 *
 * Created: 2018-11-10 5:15:54 PM
 *  Author: CaLePegasus
 */ 
#include "space_inv.h";
typedef struct shape {
	char body;
	uint16_t x;
	uint16_t y;
} Shape;
// test: try making shape
shape make_shape(gfx_shape shp, uint16_t x, uint16_t y) {	
	struct shape chshape;
	shape.x = x;
	shape.y = y;
	switch (shp) {
		case alien:
		chshape.body = '"';
		break;
		case ship:
		chshape.body = '!';
		break;
		case bullet:
		chshape.body = '$';
		break;
		default:
		break;
	}
	return chshape;
}
void draw_shape(shape shp) {
	
}

void move_shape_up(shape shp)
{
	
}

void move_shape_down(shape shp)
{
	
}

void move_shape_left(shape shp)
{
	
}

void move_shape_right(shape shp)
{
	
}