
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
// #include "stb_image.h"
typedef struct
{
 int w,a,d,s;                     //button state on off
}ButtonKeys; ButtonKeys Keys;
float playerX, playerY;
float frame1,frame2,fps;
int coordy,coordx;
void drawPlayer()
{
    glColor3f(.2, .4, .6);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(playerX, playerY);
    glEnd();
}
int mapX=32,mapY=16,mapCubeSize=32;
int map[512]={0,1,1,1,1,1,1,1,1,1,1,1,1};
void renderWorld()
{
 int x,y,xo,yo;
 for(y=0;y<mapY;y++)
 {
  for(x=0;x<mapX;x++)
  {
   if(map[y*mapX+x]==1){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}
   xo=x*mapCubeSize; yo=y*mapCubeSize;
   glBegin(GL_QUADS); 
     glVertex2i( 0          +xo+1, 0          +yo+1); 
     glVertex2i( 0          +xo+1, mapCubeSize+yo-1); 
     glVertex2i( mapCubeSize+xo-1, mapCubeSize+yo-1);  
     glVertex2i( mapCubeSize+xo-1, 0          +yo+1); 
          //   glVertex2i(xo,yo);
          //   glVertex2i(xo,yo+mapCubeSize);
          //   glVertex2i(xo+mapCubeSize,yo+mapCubeSize);
          //   glVertex2i(xo+mapCubeSize,yo);
   glEnd();
  } 
 } 
}
void keyDown(char key, int x, int y)
{
    if(key=='d'){ Keys.d=1;} 	
    if(key=='a'){ Keys.a=1;} 
    if(key=='w'){ Keys.w=1;}
    if(key=='s'){ Keys.s=1;}
    printf("%.0f %.0f\n", playerX, playerY);
    glutPostRedisplay();
    if (playerX > 1020){playerX = 0;}
    if (playerX < 0){playerX = 1020;}
    if (playerY > 508){playerY = 0;}
    if (playerY < 0){playerY = 508;}
}
void keyUp(unsigned char key,int x,int y)                                    //keyboard button pressed up
{
 if(key=='d'){ Keys.d=0;} 	
 if(key=='a'){ Keys.a=0;} 
 if(key=='w'){ Keys.w=0;}
 if(key=='s'){ Keys.s=0;}
 glutPostRedisplay();
}
void init()
{
    glClearColor(0.3, 0.1, 0.1, 0);
    gluOrtho2D(0, 1024, 512, 0);
    playerX = 400, playerY = 200; // setting player position
}

void display()
{   coordx=(playerX/mapCubeSize);
    coordy=(playerY/mapCubeSize);
   int coord = coordy*mapX+coordx;
    if (map[coord]==1){

    }
    else{
        if(Keys.a==1){ playerX-=4;} 	
        if(Keys.d==1){ playerX+=4; } 
        if(Keys.s==1){ playerY+=4; } 	
        if(Keys.w==1){ playerY-=4; } 
        }
    printf("%i %i\n", coordx, coordy);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderWorld();
    drawPlayer();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(1920/4,1080/4);
    glutCreateWindow("allah");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
}