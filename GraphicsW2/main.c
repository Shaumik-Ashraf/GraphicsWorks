#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"


int main() {

  screen s;
  struct matrix *edges;
  struct matrix *transform;
  struct matrix *temp;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);
  ident(transform);

  //testing
  add_edge(edges, 1, 1, 0, XRES/2, 1, 0 );
  add_edge(edges, XRES/2, 1, 0, XRES/2, YRES/2, 0 );
  add_edge(edges, XRES/2, YRES/2, 0, 1, YRES/2, 0 );
  add_edge(edges, 1, YRES/2, 0, 1, 1, 0 );
  
  printf("Square:\n");
  print_matrix(edges);
  
  //ident(transform);
  temp = make_translate(100,100,0);
  matrix_mult( transform, temp );
  free_matrix(temp);
  printf("\nDEBUG: transform matrix\n"); print_matrix(transform);
  matrix_mult(edges, transform);
  
  printf("\n\nPrevious Square after T(1,1,0)\n");
  print_matrix(edges);
  
  free_matrix( transform );
  free_matrix( edges );
}  
