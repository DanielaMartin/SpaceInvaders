/*
 * shape.c
 *
 * Created: 2018-11-10 5:15:54 PM
 *  Author: CaLePegasus
 */ 
#include "space_inv.h";

// test: try making shape
Shape make_shape(gfx_shape shp, uint16_t x, uint16_t y) {	
	Shape chshape;
	chshape.x = x;
	chshape.y = y;
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
	chshape.exists = true;
	return chshape;
}
void draw_shape(Shape shp) {
	
}

void move_shape_up(Shape shp)
{
	
}

void move_shape_down(Shape shp)
{
	
}

void move_shape_left(Shape shp)
{
	
}

void move_shape_right(Shape shp)
{
	
}