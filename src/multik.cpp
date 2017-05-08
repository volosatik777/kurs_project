#include "multik.h"

double rotate_y=0; 
double rotate_x=0;

double mas_x=0.5f;
double mas_y=0.5f;
double mas_z=0.5f;

int max;
int start_x;
int end_x;
int start_y;
int end_y;
int start_z;
int end_z;
int *cube;
int number_of_bact_subst;
int N;
int bact;
int substance;

#define cube(x,y,z,t) cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]  

void DrawCube(GLfloat color, GLfloat size,GLfloat x,GLfloat y,GLfloat z)
{
     glBegin(GL_QUADS);
     glColor3f( color, 0.0, 0.0 );     
     // левая грань
     glVertex3f( -size / 2+x-0.5, -size / 2+y-0.5, -size / 2+z-0.5); 
     glVertex3f( -size / 2+x-0.5,  size / 2+y-0.5, -size / 2+z-0.5);
     glVertex3f( -size / 2+x-0.5,  size / 2+y-0.5,  size / 2+z-0.5);
     glVertex3f( -size / 2+x-0.5, -size / 2+y-0.5,  size / 2+z-0.5);
     // правая грань
     glVertex3f(  size / 2+x-0.5, -size / 2+y-0.5, -size / 2+z-0.5); 
     glVertex3f(  size / 2+x-0.5, -size / 2+y-0.5,  size / 2+z-0.5);
     glVertex3f(  size / 2+x-0.5,  size / 2+y-0.5,  size / 2+z-0.5);
     glVertex3f(  size / 2+x-0.5,  size / 2+y-0.5, -size / 2+z-0.5);
     // нижняя грань
     glVertex3f( -size / 2+x-0.5, -size / 2+y-0.5, -size / 2+z-0.5); 
     glVertex3f( -size / 2+x-0.5, -size / 2+y-0.5,  size / 2+z-0.5);
     glVertex3f(  size / 2+x-0.5, -size / 2+y-0.5,  size / 2+z-0.5);
     glVertex3f(  size / 2+x-0.5, -size / 2+y-0.5, -size / 2+z-0.5);
     // верхняя грань
     glVertex3f( -size / 2+x-0.5, size / 2+y-0.5, -size / 2+z-0.5); 
     glVertex3f( -size / 2+x-0.5, size / 2+y-0.5,  size / 2+z-0.5);
     glVertex3f(  size / 2+x-0.5, size / 2+y-0.5,  size / 2+z-0.5);
     glVertex3f(  size / 2+x-0.5, size / 2+y-0.5, -size / 2+z-0.5);
     // задняя грань
     glVertex3f( -size / 2+x-0.5, -size / 2+y-0.5, -size / 2+z-0.5); 
     glVertex3f(  size / 2+x-0.5, -size / 2+y-0.5, -size / 2+z-0.5);
     glVertex3f(  size / 2+x-0.5,  size / 2+y-0.5, -size / 2+z-0.5);
     glVertex3f( -size / 2+x-0.5,  size / 2+y-0.5, -size / 2+z-0.5);
     // передняя грань
     glVertex3f( -size / 2+x-0.5, -size / 2+y-0.5,  size / 2+z-0.5); 
     glVertex3f(  size / 2+x-0.5, -size / 2+y-0.5,  size / 2+z-0.5);
     glVertex3f(  size / 2+x-0.5,  size / 2+y-0.5,  size / 2+z-0.5);
     glVertex3f( -size / 2+x-0.5,  size / 2+y-0.5,  size / 2+z-0.5);
     glEnd();
}

void display()
{
 
  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Reset transformations
  glLoadIdentity();

  glScalef(mas_x, mas_y, mas_z);
  // Rotate when user changes rotate_x and rotate_y
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );

//  glEnable(GL_BLEND); // Вкл. Blending
//  glBlendFunc(GL_ONE, GL_ONE);
  
  glBegin(GL_LINES); 

  glColor3f( 1.0, 1.0, 1.0 );     
  // далее мы рисуем координатные 
  glVertex3f(-0.9, -0.9,-0.9); 
  glVertex3f(-0.9, -0.9, 0.9); 

  glVertex3f(-0.9, -0.9,-0.9); 
  glVertex3f(-0.9, 0.9, -0.9); 
  
  glVertex3f(-0.9, -0.9,-0.9); 
  glVertex3f(0.9, -0.9, -0.9); 
  
  glVertex3f(-0.9, -0.9,-0.9); 
  glVertex3f(-0.9, -0.9, 0.9); 

  glEnd();
 /* PrintText3D(0.9,-0.9,-0.9,"x");
  PrintText3D(-0.9,0.9,-0.9,"y");
  PrintText3D(-0.9,-0.9,0.9,"z");
 */
  int razm=3;
  GLfloat size = 1.0/razm;
  for(int x=start_x;x<=end_x;x++)
    for(int y=start_y;y<=end_y;y++)
      for(int z=start_z;z<=end_z;z++)
      {
          if(cube(x,y,z,number_of_bact_subst)>0){
            GLfloat xx=(GLfloat) x/razm;
            GLfloat yy=(GLfloat) y/razm;
            GLfloat zz=(GLfloat) z/razm;
            GLfloat color=(GLfloat) cube(x,y,z,number_of_bact_subst)/max+0.1;
            if(color>1)
                color=1;
            DrawCube(color,size,xx,yy,zz);
          }
      }

  glFlush();
  glutSwapBuffers();
 
}
 
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys( int key, int x, int y ) {
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;
 
  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;
 
  else if (key == GLUT_KEY_UP){
    rotate_x += 5;
  }
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;

  else if(key == GLUT_KEY_PAGE_DOWN){
      mas_x+=0.1f;
      mas_y+=0.1f;
      mas_z+=0.1f;
  }
  
  else if(key == GLUT_KEY_PAGE_UP){
      mas_x-=0.1f;
      mas_y-=0.1f;
      mas_z-=0.1f; 
  }

  else if (key== GLUT_KEY_F1) 
    exit;
    
  //  Request display update
  glutPostRedisplay();
 
}


int my_max()
{
   int local_max=0;
   for(int x=start_x;x<=end_x;x++)
    for(int y=start_y;y<=end_y;y++)
      for(int z=start_z;z<=end_z;z++)
      {
          if(cube(x,y,z,number_of_bact_subst)>local_max)
              local_max=cube(x,y,z,number_of_bact_subst);           
      }
    return local_max;
}
// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int multik(int argc, char*argv[],int s_x,int e_x,int s_y,int e_y,
        int s_z,int e_z,int *c,int number_of_b_s,int n,int b, int s)
{
  //  Initialize GLUT and process user parameters
  start_x=s_x;
  end_x=e_x;
  start_y=s_y;
  end_y=e_y;
  start_z=s_z;
  end_z=e_z;
  cube=c;
  number_of_bact_subst=number_of_b_s;
  N=n;
  bact=b;
  substance=s;
  max=my_max();

  glutInit(&argc,argv);
 
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Create window
  glutCreateWindow("Cube");
 
  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);
 
  // Callback functions
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
 
  //  Pass control to GLUT for events
  glutMainLoop();
 
  return 0;
}

