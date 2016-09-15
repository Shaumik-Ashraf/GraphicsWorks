#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== my helper function!! ===========
  Inputs: struct matrix* points => edge matrix
		double (*param_x)(double) => parametric equation function to generate x coordinates
		struct matrix* param_x_arg => matrix of stuff to be passed to param functions
		double (*param_y)(double) => parametric equation function to generate y coordinates
		struct matrix* param_y_arg => matrix of stuff to be passed to param functions
		double step => da step
		
  Returns:
		
		runs paramtric equation for 0<=t<1 in step increments generating points added to points edge matrix
		
		I made this bc I'm prbly gunna mess this up and am hoping to isolate the failure
shaumik ashraf
======================*/
void add_parametric(struct matrix* points, 
			double (*param_x)(double, struct matrix*),
			struct matrix* param_x_arg,
			double (*param_y)(double, struct matrix*),
			struct matrix* param_y_arg,
			double step) {

	double x, y;
	double t;
	
	for(t=0.00000; t<1.00000000; t+=step) {
		x = param_x(t, param_x_arg);
		y = param_y(t, param_y_arg);
		
		add_point(points, x, y, 0);
	}

}

/*======== void add_circle() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double y
	    double step  
  Returns: 


  03/16/12 19:53:52
  jdyrlandweaver
  ====================*/
void add_circle( struct matrix * points, 
		 double cx, double cy, 
		 double r, double step ) {
  /* TRY BOTH!!
  double x, y;
  double t;

  for(t=0; t<1.00000; t+=step) {
    x = cx + r*cosf( t*M_PI );
    y = cy + r*sinf( t*M_PI );
  }

  add_point(points, x, y, 0);
  */
  struct matrix* x_arg = new_matrix(1, 2);
  struct matrix* y_arg = new_matrix(1, 2);
  
  x_arg->m[0][0] = cx;
  x_arg->m[0][1] = r;
  
  y_arg->m[0][0] = cy;
  y_arg->m[0][1] = r;
  
  add_parametric(points, circle_param_x, x_arg, circle_param_y, y_arg, step);
  
}

//center_x_and_radius format: [cx, r]
double circle_param_x(double t, struct matrix* center_x_and_radius) {
	return( center_x_and_radius->m[0][0] + center_x_and_radius->m[0][1] * cosf( t*M_PI ) );
}

//center_y_and_radius format: [cy, r]
double circle_param_y(double t, struct matrix* center_y_and_radius) {
	return( center_y_and_radius->m[0][0] + center_y_and_radius->m[0][1] * sinf( t*M_PI ) );
} //and now i'm finding this to be a dumb idea

/*======== void add_curve() ==========
Inputs:   struct matrix *points
         double x0
         double y0
         double x1
         double y1
         double x2
         double y2
         double x3
         double y3
         double step
         int type  
Returns: 

Adds the curve bounded by the 4 points passsed as parameters
of type specified in type (see matrix.h for curve type constants)
to the matrix points

03/16/12 15:24:25
jdyrlandweaver
====================*/
void add_curve( struct matrix *points, 
		double x0, double y0, 
		double x1, double y1, 
		double x2, double y2, 
		double x3, double y3, 
		double step, int type ) {

	struct matrix* xcoefs = generate_curve_coefs(x0, x1, x2, x3, type);
	struct matrix* ycoefs = generate_curve_coefs(y0, y1, y2, y3, type);
	
	if( type==HERMITE_MODE ) {
		add_parametric(points, hermite_curve_param_x, xcoefs, hermite_curve_param_y, ycoefs, step);
	}
	else {
		add_parametric(points, bezier_curve_param_x, xcoefs, bezier_curve_param_y, ycoefs, step);
	}
	
}

//xcoefs format: [a, b, c, d] for at^3+bt^2+ct+d
double bezier_curve_param_x(double t, struct matrix* xcoefs) {
	return( xcoefs->m[0][1]*t*t*t + xcoefs->m[0][2]*t*t + xcoefs->m[0][3]*t + xcoefs->m[0][4] );
}

//ycoefs format: [a, b, c, d] for at^3+bt^2+ct+d
double bezier_curve_param_y(double t, struct matrix* ycoefs) {
	return(  ycoefs->m[0][1]*t*t*t + ycoefs->m[0][2]*t*t + ycoefs->m[0][3]*t + ycoefs->m[0][4]  );
}

//xcoefs format: [a, b, c, d] for at^3+bt^2+ct+d
double hermite_curve_param_x(double t, struct matrix* xcoefs) {
	return(  xcoefs->m[0][1]*t*t*t + xcoefs->m[0][2]*t*t + xcoefs->m[0][3]*t + xcoefs->m[0][4]  );
}

//ycoefs format: [a, b, c, d] for at^3+bt^2+ct+d
double hermite_curve_param_y(double t, struct matrix* ycoefs) {
	return(  ycoefs->m[0][1]*t*t*t + ycoefs->m[0][2]*t*t + ycoefs->m[0][3]*t + ycoefs->m[0][4]  );
}

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  
  if ( points->lastcol == points->cols )
    grow_matrix( points, points->lastcol + 100 );

  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;

  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point( points, x0, y0, z0 );
  add_point( points, x1, y1, z1 );
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {

  int i;
 
  if ( points->lastcol < 2 ) {
    
    printf("Need at least 2 points to draw a line!\n");
    return;
  }

  for ( i = 0; i < points->lastcol - 1; i+=2 ) {

    draw_line( points->m[0][i], points->m[1][i], 
	       points->m[0][i+1], points->m[1][i+1], s, c);
  } 	       
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
 
  int x, y, d, dx, dy;

  x = x0;
  y = y0;
  
  //swap points so we're always draing left to right
  if ( x0 > x1 ) {
    x = x1;
    y = y1;
    x1 = x0;
    y1 = y0;
  }

  //need to know dx and dy for this version
  dx = (x1 - x) * 2;
  dy = (y1 - y) * 2;

  //positive slope: Octants 1, 2 (5 and 6)
  if ( dy > 0 ) {

    //slope < 1: Octant 1 (5)
    if ( dx > dy ) {
      d = dy - ( dx / 2 );
  
      while ( x <= x1 ) {
	plot(s, c, x, y);

	if ( d < 0 ) {
	  x = x + 1;
	  d = d + dy;
	}
	else {
	  x = x + 1;
	  y = y + 1;
	  d = d + dy - dx;
	}
      }
    }

    //slope > 1: Octant 2 (6)
    else {
      d = ( dy / 2 ) - dx;
      while ( y <= y1 ) {

	plot(s, c, x, y );
	if ( d > 0 ) {
	  y = y + 1;
	  d = d - dx;
	}
	else {
	  y = y + 1;
	  x = x + 1;
	  d = d + dy - dx;
	}
      }
    }
  }

  //negative slope: Octants 7, 8 (3 and 4)
  else { 

    //slope > -1: Octant 8 (4)
    if ( dx > abs(dy) ) {

      d = dy + ( dx / 2 );
  
      while ( x <= x1 ) {

	plot(s, c, x, y);

	if ( d > 0 ) {
	  x = x + 1;
	  d = d + dy;
	}
	else {
	  x = x + 1;
	  y = y - 1;
	  d = d + dy + dx;
	}
      }
    }

    //slope < -1: Octant 7 (3)
    else {

      d =  (dy / 2) + dx;

      while ( y >= y1 ) {
	
	plot(s, c, x, y );
	if ( d < 0 ) {
	  y = y - 1;
	  d = d + dx;
	}
	else {
	  y = y - 1;
	  x = x + 1;
	  d = d + dy + dx;
	}
      }
    }
  }
}

