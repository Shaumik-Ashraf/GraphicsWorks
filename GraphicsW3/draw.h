#ifndef DRAW_H
#define DRAW_H

#include "matrix.h"

void draw_line(int x0, int y0, 
	       int x1, int y1, 
	       screen s, color c);
void add_point( struct matrix * points, 
		double x0, double y0, double z0); 
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1);
void draw_lines( struct matrix * points, screen s, color c);

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
		
//my additions - shaumik ashraf
void add_parametric(struct matrix* points, 
			double (*param_x)(double, struct matrix*),
			struct matrix* param_x_arg,
			double (*param_y)(double, struct matrix*),
			struct matrix* param_y_arg,
			double step);

//some predefined parametrix equations...
//center_x_and_radius format: [cx, r]
double circle_param_x(double t, struct matrix* center_x_and_radius);
//center_y_and_radius format: [cy, r]
double circle_param_y(double t, struct matrix* center_y_and_radius);
//xcoefs format: [a, b, c, d] for at^3+bt^2+ct+d
double bezier_curve_param_x(double t, struct matrix* xcoefs);
//ycoefs format: [a, b, c, d] for at^3+bt^2+ct+d
double bezier_curve_param_y(double t, struct matrix* ycoefs);
//xcoefs format: [a, b, c, d] for at^3+bt^2+ct+d
double hermite_curve_param_x(double t, struct matrix* xcoefs);
//ycoefs format: [a, b, c, d] for at^3+bt^2+ct+d
double hermite_curve_param_y(double t, struct matrix* ycoefs);

#endif
