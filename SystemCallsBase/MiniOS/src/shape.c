/*
 * shape.c
 *
 * Created: 2018-11-10 5:15:54 PM
 *  Author: CaLePegasus
 */ 
#include "space_inv.h";
struct shape {
	char body;
	char position[][];
}
shape make_shape(gfx_shape shp, char pos[][]) {	
	struct shape chshape;
	shape.position = pos;
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