#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void DrawCube(GLfloat color, GLfloat size,GLfloat x,GLfloat y,GLfloat z);


void display();

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys( int key, int x, int y );
// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int multik(int argc, char*argv[],int start_x,int end_x,int start_y,int end_y,   
         int start_z,int end_z,int *cube,int number_of_bact_subst,               
             int N,int bact,int substance);  
