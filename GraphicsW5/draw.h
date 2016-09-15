#ifndef DRAW_H
#define DRAW_H

#include "matrix.h"

#define MAX_STEPS 100

void draw_line(int x0, int y0, int x1, int y1, screen s, color c);

void add_point( struct matrix * points, double x, double y, double z);

void add_edge( struct matrix * points,
	       double x0, double y0, double z0,
	       double x1, double y1, double z1);

void add_polygons( struct matrix * points,
		   double x0, double y0, double z0,
		   double x1, double y1, double z1,
		   double x2, double y2, double z2);

void draw_lines( struct matrix * points, screen s, color c);

void draw_polygons( struct matrix * points, screen s, color c);

//advanced shapes
void add_circle( struct matrix * points, 
		 double cx, double cy, 
		 double r, double step );
void add_curve( struct matrix *points, 
		double x0, double y0,
		double x1, double y1,
		double x2, double y2,
		double x3, double y3,
		double step, int type );
void add_sphere( struct matrix * points, 
		      double cx, double cy, double r, 
		      int step );
void generate_sphere( struct matrix * points, 
			   double cx, double cy, double r, 
			   int step );
void add_torus( struct matrix * points, 
		     double cx, double cy, double r1, double r2, 
		     int step );
void generate_torus( struct matrix * points, 
			  double cx, double cy, double r1, double r2, 
		     int step );

//helper functions

/* do_i_draw_it
 * parameters: (x0,y0,z0) (x1,y1,z1) and (x2,y2,z2) are points P0 P1 P2 respectively
 * return: returns 1 if polygon of P0 P1 P2 is facing you, 0 if not
 * Backface culling method 
 */
int do_i_draw_it(double x0, double y0, double z0,
		 double x1, double y1, double z1,
		 double x2, double y2, double z2,
		 double view_x, double view_y, double view_z);

#endif
