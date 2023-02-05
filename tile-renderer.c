#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
// #include "stb_image.h"
typedef struct
{
 int w,a,d,s;                     //button state on off
}ButtonKeys; ButtonKeys Keys;
int playerX, playerY;
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
 map[76] = 1;
 int x,y,xo,yo;
 for(y=0;y<mapY;y++)
 {
  for(x=0;x<mapX;x++)
  {
   if(map[y*mapX+x]==1){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}
   xo=x*mapCubeSize; yo=y*mapCubeSize;
   glBegin(GL_QUADS); 
    //  glVertex2i( 0          +xo+1, 0          +yo+1); 
    //  glVertex2i( 0          +xo+1, mapCubeSize+yo-1); 
    //  glVertex2i( mapCubeSize+xo-1, mapCubeSize+yo-1);  
    //  glVertex2i( mapCubeSize+xo-1, 0          +yo+1); 
            glVertex2i(xo,yo);
            glVertex2i(xo,yo+mapCubeSize);
            glVertex2i(xo+mapCubeSize,yo+mapCubeSize);
            glVertex2i(xo+mapCubeSize,yo);
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
    printf("%i %i\n", playerX, playerY);
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
    playerX = 399, playerY = 199; // setting player position
}
int cornerCoords[8];
int corner()
{
    cornerCoords[0]=playerX-4;cornerCoords[1]=playerY-4;//TL
    cornerCoords[2]=playerX+4;cornerCoords[3]=playerY-4;//TR
    cornerCoords[4]=playerX-4;cornerCoords[5]=playerY+4;//BL
    cornerCoords[6]=playerX+4;cornerCoords[7]=playerY+4;//BR
}
int dotCoord(int coordX, int coordY){
    // printf("%d,%d  %d,%d\n%d,%d  %d,%d\n#========\n",
    // cornerCoords[0],cornerCoords[1],
    // cornerCoords[2],cornerCoords[3],
    // cornerCoords[4],cornerCoords[5],
    // cornerCoords[6],cornerCoords[7] 
    // );
    int y=coordY/mapCubeSize;
    int x=coordX/mapCubeSize;
    int cornerpos = y*mapX+x;
    return(cornerpos);
}
bool collision(int direction){
    corner();
    /* 
    direction:
        0=left
        1=right
        2=top
        3=bottom
    */
   if(direction==0)
   {
    if(map[dotCoord(cornerCoords[0]-2,cornerCoords[1]+1)]== 0 && (map[dotCoord(cornerCoords[4]-2,cornerCoords[5]-1)]==0)){return true;}
    else{return false;}
   }
   if(direction==1)
   {
    if(map[dotCoord(cornerCoords[2]+1,cornerCoords[3]+1)]== 0 && (map[dotCoord(cornerCoords[6]+1,cornerCoords[7]-1)]==0)){return true;}
    else{return false;}
   }
   if(direction==2)
   {
    if(map[dotCoord(cornerCoords[0]+1,cornerCoords[1]-1)]== 0 && (map[dotCoord(cornerCoords[2]-1,cornerCoords[3]-1)]==0)){return true;}
    else{return false;}
   }
   if(direction==3)
   {
    if(map[dotCoord(cornerCoords[4]+1,cornerCoords[5]+1)]== 0 && (map[dotCoord(cornerCoords[6]-1,cornerCoords[7]+1)]==0)){return true;}
    else{return false;}
   }
   



}
void display()
{
        if(Keys.a==1 && collision(0))
        { playerX-=4;} 	
        if(Keys.d==1 && collision(1))
        { playerX+=4; } 
        if(Keys.s==1 && collision(3))
        { playerY+=4; } 	
        if(Keys.w==1 && collision(2))
        { playerY-=4; } 
    // printf("%i %i\n", coordx, coordy);
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
    glutCreateWindow("test");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
}