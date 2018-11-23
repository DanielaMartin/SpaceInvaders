/*
 * shape.c
 *
 * Created: 2018-11-10 5:15:54 PM
 *  Author: CaLePegasus
 */ 
#include "space_inv.h";
#include "minios/hal/hal.h";
#include "asf.h"
#include <stdint-gcc.h>

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
void draw_shape(Shape* shp) {
	if (shp->exists)
	{
		ssd1306_set_page_address(shp->y);
		ssd1306_set_column_address(shp->x * 8);
		hal_display_putc(shp->body);
	}
}

void move_shape_down(Shape* shp) {
	uint16_t y = shp->y;
	// add one to the y axis
	y++;
	// check if it is still in bounds
	if (y <= 3) 
		shp->y = y;
}

void move_shape_up(Shape* shp) {
	uint16_t y = shp->y;
	// check if it is still in bounds
	if (y == 0)
		return;
	// subtract one to the y axis
	y --;
	shp->y = y;
}

void move_shape_left(Shape* shp)
{
	uint16_t x = shp->x;
	// subtract one from the x axis
	x --;
	// check if it is still in bounds
	if (x >= 0) 
		shp->x = x;
}

void move_shape_right(Shape* shp)
{
	uint16_t x = shp->x;
	// add one to the x axis
	x ++;
	// check if it is still in bounds
	if (x <= 15) 
		shp->x = x;
}