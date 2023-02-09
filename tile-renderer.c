#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
// #include "stb_image.h"
#include <unistd.h> //for windows #include<windows.h>


typedef struct
{
 int a,d,space;                   //button state on off
}ButtonKeys; ButtonKeys Keys;


int playerX, playerY;
int coordy,coordx;
int vel=0;
int mapX=32,mapY=16,mapCubeSize=32;
int map[512]={};
unsigned int microseconds=17000;
bool collision(int direction);
void loadMap()
{
    FILE *File;
    File = fopen("test_map.csv", "r");
    int i;
    {
    for (i = 0; i < 512; i++)
    {
        fscanf(File, "%d,", &map[i]);
    }
    fclose(File);
}}
void drawPlayer()
{
    glColor3f(1, .1, .2);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(playerX, playerY);
    glEnd();
}
void renderWorld()
{
 loadMap();
 int x,y,xo,yo;
 for(y=0;y<mapY;y++)
 {
  for(x=0;x<mapX;x++)
  {
   if(map[y*mapX+x]==0){ glColor3f(.2,.4,1);} else{ glColor3f(.2,1,.5);}
   xo=x*mapCubeSize; yo=y*mapCubeSize;
   glBegin(GL_QUADS); 
     glVertex2i( 0          +xo+1, 0          +yo+1); 
     glVertex2i( 0          +xo+1, mapCubeSize+yo-1); 
     glVertex2i( mapCubeSize+xo-1, mapCubeSize+yo-1);  
     glVertex2i( mapCubeSize+xo-1, 0          +yo+1); 
            // glVertex2i(xo,yo);
            // glVertex2i(xo,yo+mapCubeSize);
            // glVertex2i(xo+mapCubeSize,yo+mapCubeSize);
            // glVertex2i(xo+mapCubeSize,yo);
   glEnd();
  } 
 } 
}
void keyDown(char key, int x, int y)
{
    if(key=='d'){ Keys.d=1;} 	
    if(key=='a'){ Keys.a=1;} 
    if(key==32){Keys.space=1;}   
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
 if(key==32){Keys.space=0;}
 glutPostRedisplay();
}
void init()
{
    glClearColor(0.3, 0.3, 0.3, 0);
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
void display(){}
void gravity(){
    if(collision(3)|| vel<0)
    {  
        if(vel<0){for(int i=0;i > vel+2;i--){if(!collision(2)){vel=0;}else{playerY-=1;}}}
        if (vel>=0){for(int i=0;i < vel+2;i++){if(!collision(3)){vel=0;}else{playerY+=1;}}}
        vel+=3;
        usleep(microseconds);

    }
    if(!collision(3)){vel=0;}

}
void idle()
{
        gravity();
        if(Keys.a==1 && collision(0))
        { playerX-=4;} 	
        if(Keys.d==1 && collision(1))
        { playerX+=4; } 
        if(Keys.space==1&& !collision(3))
        {vel= -26;}
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderWorld();
        drawPlayer();
        glutSwapBuffers();
        usleep(microseconds);

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
    glutIdleFunc(idle);
    glutMainLoop();
}
