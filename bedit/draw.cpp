#include <windows.h>
#include "editor.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>

#include "resource.h"
extern PIXELFORMATDESCRIPTOR pfd;
extern int gameRound;
extern int resWidth;
extern int resHeight;
extern int ypos;
extern int xpos;
extern paddle bluepaddle;
extern int cx;
extern int cy;
extern bool gridshowcoords;
extern goal redgoals[3000];
extern goal bluegoals[3000];
extern brick bricks[3000];
extern brick blocks[3000];
extern paddle rpaddles[4];
extern paddle bpaddles[4];
extern paddle redpaddle;//eventually add ability to add more paddles
extern bouncer bouncers[3000];
extern essence redessences[3000];
extern essence blueessences[3000];
extern int gridoffsetX;
extern int gridoffsetY;
extern int gridwidth;
extern ball balls[500];
extern int gridheight;
extern bool gridtoggle;
extern HGLRC hRC;
extern HDC hDC;
extern HGLRC hRCh;
extern HDC hdCh;
extern HWND hwndCh;
extern HWND hwnd;

void glsetup(){
//wglMakeCurrent(hDC, hRC);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(xpos-(.5*resWidth), (xpos+(.5*resWidth))-25 , (ypos+(.5*resHeight))-63 , (ypos-(.5*resHeight)));
glDisable(GL_DITHER);
glClearColor(0,0,0,0);
glLineWidth(2);
}






void render(){
extern HDC hDC;
//int a = 4;
int i;
char strBuffer [200];

//wglMakeCurrent(hdCh, hRCh);
//	glClearColor(0,0,0,0);
//	glClear(GL_COLOR_BUFFER_BIT);
//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

extern int MAPBARRIER;


			wglMakeCurrent(hdCh, hRCh);
			glClearColor(0,0,0,0);
			glClear(GL_COLOR_BUFFER_BIT);
			
			glPushMatrix();
				gluOrtho2D(0,MAPBARRIER,MAPBARRIER,0);	
				
				drawGameObjects();
				glColor3f(1,0,0);
				glPointSize(5);
				glBegin(GL_POINTS);
				glVertex2i(xpos,ypos);
				glEnd();
			glPopMatrix();

			
			SwapBuffers(hdCh);
			wglMakeCurrent(hDC, hRC);




//wglMakeCurrent(hDC, hRC);
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
glLoadIdentity();

glMatrixMode(GL_PROJECTION);
glPushMatrix();
	glLoadIdentity();
	
	//glsetup();
	gluOrtho2D(xpos-(.5*resWidth), (xpos+(.5*resWidth)),(ypos+(.5*resHeight)),(ypos-(.5*resHeight)));
	//gluOrtho2D(0,MAPBARRIER,MAPBARRIER,0);
	


drawGameObjects();

glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

int cWidth;
int cHeight;
extern int object;
switch(object){
case ID_PADDLE_RED:
case ID_PADDLE_BLUE:
case ID_PADDLE_BLUEEXTRA:
case ID_PADDLE_REDEXTRA:
	cWidth = PADDLEWIDTH;
	cHeight = PADDLEHEIGHT;
	break;
case ID_OBJECT_BLOCK:
case ID_OBJECT_BRICK:
	cWidth = BLOCKWIDTH;
	cHeight = BLOCKHEIGHT;
	break;
case ID_OBJECT_BALL142:
	cWidth = BALLSIZE;
	cHeight = cWidth;
	break;
case ID_ESSENCE_BLUE:
case ID_ESSENCE_RED:
	cWidth = ESSENCERADIUS;
	cHeight = ESSENCERADIUS;
	break;
case ID_OBJECT_BOUNCER:
	cWidth = BOUNCERRADIUS;
	cHeight = cWidth;
	break;
case ID_GOAL_RED:
case ID_GOAL_BLUE:
	cWidth = GOALWIDTH;
	cHeight = GOALHEIGHT;
	break;
}


//draw grid
/////////////////////////////////////////////////////////////
if(gridtoggle == true){
glColor3f(.3,.3,.3);
glLineWidth(1);
glBegin(GL_LINES);
	for(i = (0);i < (MAPBARRIER+gridwidth);i = (i+gridwidth)){
		glVertex2i(i+gridoffsetX,0);
		glVertex2i(i+gridoffsetX,MAPBARRIER);
	}

for(i = (0);i < (MAPBARRIER+gridheight);i = (i+gridheight)){
	glVertex2i(0,i+gridoffsetY);
	glVertex2i(MAPBARRIER,i+gridoffsetY);
}
glEnd();
}
//////////////////////////////////////////////////
//mapbarrier outline
glColor3f(1,1,1);
	glBegin(GL_LINES);
	glVertex2i(0,0);
	glVertex2i(MAPBARRIER,0);
	glVertex2i(MAPBARRIER,0);
	glVertex2i(MAPBARRIER,MAPBARRIER);
	glVertex2i(MAPBARRIER,MAPBARRIER);
	glVertex2i(0,MAPBARRIER);
	glVertex2i(0,MAPBARRIER);
	glVertex2i(0,0);
	glEnd();

//crusorsquare
glPolygonMode(GL_FRONT, GL_LINE);
glColor3f(0,1,0);
drawObject(xpos-(resWidth/2)+cx,ypos-(resHeight/2)+cy, cWidth, cHeight);

//text
if(gridshowcoords==true){

	//if cursor is outside box print coords in red
	if(xpos-(resWidth/2)+cx<=0 || xpos-(resWidth/2)+cx>=MAPBARRIER||ypos-(resHeight/2)+cy<=0||ypos-(resHeight/2)+cy>=MAPBARRIER){
		glColor3f(1,0,0);
	}
	else{
		glColor3f(1,1,1);
	}
	
	
	
	glRasterPos2i (-370+xpos,-270+ypos);
	//glRasterPos2i (xpos,ypos);
	sprintf(strBuffer, "\t  %i,%i\n", xpos-(resWidth/2)+cx,ypos-(resHeight/2)+cy );

	ShowText(strBuffer);
}

glPopMatrix();


SwapBuffers(hDC);




}

//

void ShowText(char* string){
extern unsigned int base;
wglUseFontBitmaps(hDC, 32, 96, base);
glPushAttrib(GL_LIST_BIT);
glListBase(base-32);
glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);
glPopAttrib();
}


void drawObject(int x, int y, int width, int height){
glBegin(GL_QUADS);
	glVertex2i(x-width,y-height);
	glVertex2i(x+width,y-height);
	glVertex2i(x+width,y+height);
	glVertex2i(x-width,y+height);
glEnd();
glColor3f(1,1,1);
glBegin(GL_LINES);
	glVertex2i(x,y-height);
	glVertex2i(x,y+height);
	glVertex2i(x-width, y);
	glVertex2i(x+width, y);
glEnd();
}




void drawGameObjects(){
if(redpaddle.x){
	glColor3f(1,0,0);
	drawObject(redpaddle.x,redpaddle.y,PADDLEWIDTH,PADDLEHEIGHT);}
if(bluepaddle.x){
	glColor3f(0,0,1);
	drawObject(bluepaddle.x,bluepaddle.y,PADDLEWIDTH,PADDLEHEIGHT);}
//drawObject(bluepaddle.x,bluepaddle.y,PADDLEWIDTH,PADDLEHEIGHT);


for(int i = 0; i <3; i++){
	glColor3f(1,0,0);
	if(rpaddles[i].x){
	drawObject(rpaddles[i].x,rpaddles[i].y,PADDLEWIDTH,PADDLEHEIGHT);
	}
}


for(int i = 0; i <3; i++){
	glColor3f(0,0,1);
	if(bpaddles[i].x){
	drawObject(bpaddles[i].x,bpaddles[i].y,PADDLEWIDTH,PADDLEHEIGHT);
	}
}



for(int i = 0; i <3000;i++){
	glColor3f(.5,.5,.5);
	if(bricks[i].round == gameRound || bricks[i].round == 4){

		drawObject(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height);
		
	}
}

for(int i = 0; i <3000;i++){
	glColor3f(1,1,1);
	if(blocks[i].round){
		if(blocks[i].round == gameRound || blocks[i].round == 4){
		drawObject(blocks[i].x, blocks[i].y, blocks[i].width, blocks[i].height);
		}
	}
}




for(int i = 0; i <3000;i++){
	glColor3f(0,0,1);
	if(bluegoals[i].round){
		if(bluegoals[i].round == gameRound || bluegoals[i].round == 4){
		drawObject(bluegoals[i].x, bluegoals[i].y, bluegoals[i].width, bluegoals[i].height);
		}
	}
}

for(int i = 0; i <3000;i++){
	glColor3f(1,0,0);
	if(redgoals[i].round){
		if(redgoals[i].round == gameRound ||  redgoals[i].round == 4){
		drawObject(redgoals[i].x, redgoals[i].y, redgoals[i].width, redgoals[i].height);
		}
	}
}



float ANG = THIRTYDEGREES;
glColor3f(1,1,1);


for(int i = 0; i <500;i++){
	if(balls[i].round == gameRound || balls[i].round == 4){
		//drawObject(balls[i].x,balls[i].y,BALLSIZE,BALLSIZE);
		glPushMatrix();
		glTranslatef(balls[i].x,balls[i].y,0);
		glBegin(GL_POLYGON);
			for (int j = 0; j <12; j++){
				glVertex2i(balls[i].radius*cos(ANG), balls[i].radius*sin(ANG));
				ANG = ANG+THIRTYDEGREES;
			}
		glEnd();
		glPopMatrix();
	}

}

glColor3f(1,0,0);
for(int i = 0; i < 3000; i++){
	if(redessences[i].round){
		if(redessences[i].round == gameRound || redessences[i].round == 4){
		glPushMatrix();
		glTranslatef(redessences[i].x,redessences[i].y,0);
		glBegin(GL_POLYGON);
			for (int j = 0; j <12; j++){
				glVertex2i(redessences[i].radius*cos(ANG), redessences[i].radius*sin(ANG));
				ANG = ANG+THIRTYDEGREES;
			}
		glEnd();
		glPopMatrix();
		}
	}
}

glColor3f(0,0,1);
for(int i = 0; i < 3000; i++){
	if(blueessences[i].round){
		if(blueessences[i].round == gameRound || blueessences[i].round == 4){
		glPushMatrix();
		glTranslatef(blueessences[i].x,blueessences[i].y,0);
		glBegin(GL_POLYGON);
			for (int j = 0; j <12; j++){
				glVertex2i(blueessences[i].radius*cos(ANG), blueessences[i].radius*sin(ANG));
				ANG = ANG+THIRTYDEGREES;
			}
		glEnd();
		glPopMatrix();
		}
	}
}


glColor3f(.5,.5,.5);
for(int i = 0; i < 3000; i++){
	if(bouncers[i].round){
		if(bouncers[i].round == gameRound || bouncers[i].round == 4){
		glPushMatrix();
		glTranslatef(bouncers[i].x,bouncers[i].y,0);
		glBegin(GL_POLYGON);
			for (int j = 0; j <12; j++){
				glVertex2i(bouncers[i].radius*cos(ANG), bouncers[i].radius*sin(ANG));
				ANG = ANG+THIRTYDEGREES;
			}
		glEnd();
		glPopMatrix();
		}
	}
}
}