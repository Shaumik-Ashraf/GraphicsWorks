//picmaker.c
//make pictures in pbm

#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<fcntl.h>

#define SQR(x) ((x)*(x))
#define SQRSUM(x, y) (SQR(x)+SQR(y))

double distance(int x1, int y1, int x2, int y2);
void mkpic0(int fd, char* buffer, int bufmax);
void mkpic1(int fd, char* buffer, int bufmax);
void mkpic2(int fd, char* buffer, int bufmax);
void mkpic3(int fd, char* buffer, int bufmax);
void mkpic4(int fd, char* buffer, int bufmax);
void mkpic5(int fd, char* buffer, int bufmax);
void mkpic6(int fd, char* buffer, int bufmax);
void mkpic7(int fd, char* buffer, int bufmax);

int main(int argc, char* argv[]) {

  int i, j, fd;
  char buffer[256];

  if( argc < 2 ) {
    fprintf(stderr, "Error, no file name arg\n");
    return(1);
  }
  
  if( (fd=open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644))<0 ) {
    perror("Error opening file: ");
    fprintf(stderr, "\n");
    return(1);
  } 

  //create header
  strcpy(buffer, "P3\n500 500 255\n");
  write(fd, buffer, strlen(buffer));
  memset(buffer, '\0', 256);
  
  mkpic7(fd, buffer, 256);
  
  close(fd);
  
  return(0);
}

double distance(int x1, int y1, int x2, int y2) {
	
	return( sqrt((double)( SQR(x2-x1) + SQR(y2-y1) )) );
	
}

void mkpic0(int fd, char* buffer, int bufmax) {

	int i, j;

	for(i=0; i<500; i++) {
	    for(j=0; j<500; j++) {
	      strcpy(buffer, "200 0 200 ");
	      write(fd, buffer, strlen(buffer));
	      memset(buffer, '\0', 256);
	    }
	    write(fd, "\n", 2);
	  }

}

void mkpic1(int fd, char* buffer, int bufmax) {

	int i, j;

	for(i=0; i<500; i++) {
	    for(j=0; j<500; j++) {
	      strcpy(buffer, "255 105 180 ");
	      write(fd, buffer, strlen(buffer));
	      memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}

}

void mkpic2(int fd, char* buffer, int bufmax) {
	
	int i, j;
	
	for(i=0; i<500; i++) {
		for(j=0; j<500; j++) {
			sprintf(buffer, "%i %i %i ", 0, 0, (int)(sin((double)i)*255) );
			write(fd, buffer, strlen(buffer));
			memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}
	
}

void mkpic3(int fd, char* buffer, int bufmax) {
	
	int i, j, b;
	
	for(i=0; i<500; i++) {
		for(j=0; j<500; j++) {
			sprintf(buffer, "%i %i %i ", (int)(cos((double)(j*0.07))*255), 0, (int)(sin((double)(i*0.7))*255) );
			write(fd, buffer, strlen(buffer));
			memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}
	
}

void mkpic4(int fd, char* buffer, int bufmax) {
	
	int i, j, r=0, g=0, b=0;
	
	for(i=0; i<500; i++) {
		for(j=0; j<500; j++) {
			
			if( (SQRSUM(i, j)) < SQR(1) ) {
				;
				r = 255;
			}
			
			/*
			if( SQRSUM(i, (j-500)) < 200 ) {
				r = 255;
			}
			
			if( SQRSUM((i-500), j) < 150 ) {
				b = 255;
			}
			*/
			
			sprintf(buffer, "%i %i %i ", r, g, b );
			write(fd, buffer, strlen(buffer));
			memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}
	
}

void mkpic5(int fd, char* buffer, int bufmax) {
	
	int i, j, r=0, g=0, b=0;
	
	for(i=0; i<500; i++) {
		for(j=0; j<500; j++) {
			
			r = (int)((float)i/500 * 255);
			if( i<200 && j<200 ) {
				g = (int)(((SQRSUM(200, 200) - (int)sqrt( (double)SQRSUM(i, j) )) / (double)SQRSUM(200, 200)) * 255);
			}
			else {
				g=0;
			}
			b = (int)((float)j/500 * 255);
			
			sprintf(buffer, "%i %i %i ", r, g, b );
			write(fd, buffer, strlen(buffer));
			memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}
	
}

void mkpic6(int fd, char* buffer, int bufmax) {
	
	int i, j, r=0, g=0, b=0;
	
	for(i=0; i<500; i++) {
		for(j=0; j<500; j++) {
			
			r = (int)((float)i/500 * 255);
			
			if( (int)distance(i, j, 0, 0) < 175 || (int)distance(i, j, 500, 0) < 150 || (int)distance(i, j, 0, 500) < 200 ) {
				g = (int)(((SQRSUM(200, 200) - (int)sqrt( (double)SQRSUM(i, j) )) / (double)SQRSUM(200, 200)) * 255);
			}
			else {
				g = 0;
			}
			
			b = (int)((float)j/500 * 255);
			
			sprintf(buffer, "%i %i %i ", r, g, b );
			write(fd, buffer, strlen(buffer));
			memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}
	
}

void mkpic7(int fd, char* buffer, int bufmax) {
	
	int i, j, r=0, g=0, b=0;
	
	for(i=0; i<500; i++) {
		for(j=0; j<500; j++) {
			
			r = (int)((float)i/500 * 255);
			
			if( (int)distance(i, j, 0, 0) < 200 ) {
				g = (int)(((200 - distance(i, j, 0, 0))/200)*255);
			}
			else if( (int)distance(i, j, 500, 0) < 175 ) {
				g = (int)(((175 - distance(i, j, 500, 0))/175)*255);
			}
			else if( (int)distance(i, j, 0, 500) < 200 ) {
				g = (int)(((200 - distance(i, j, 0, 500))/200)*255);
			}
			else {
				g = 0;
			}
			
			b = (int)((float)j/500 * 255);
			
			sprintf(buffer, "%i %i %i ", r, g, b );
			write(fd, buffer, strlen(buffer));
			memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}
	
}