#include <windows.h>
#include "bong.h"
#include <math.h>
//#include "resource.h"
extern float paddlexex;
extern float paddlewidthex;
extern int fps;
extern int gameRound;
extern int resWidth;
extern int resHeight;

extern ball MainBall;
extern int scores[2];
extern bool gHelp;

extern GLfloat aTex;
//static GLuint texName2[];
extern unsigned char *bitmap;
extern unsigned char *texture;
extern unsigned char *hlpBmp;
extern unsigned int ti;
extern unsigned int iTexture;
extern BITMAPINFOHEADER biHead;
extern BITMAPINFOHEADER biHeadBck;
extern BITMAPINFOHEADER biHeadTxt;
extern BITMAPINFOHEADER hlpHead;
static GLuint texName;
static GLuint texName2;
static GLuint texName3;

GLfloat lLeftX, lRightX,uRightX,uLeftX,lLeftY, lRightY,uRightY,uLeftY;
extern HDC hDC;


void GameMenu(){
    
}




void glsetup(){
glShadeModel(GL_SMOOTH);
    //wglMakeCurrent(hDC, hRC);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D( 0, resWidth , resHeight , 0);
glDisable(GL_DITHER);
glClearColor(0,0,0,0);
glLineWidth(2);
glPointSize(PART_SIZE);

glTexEnvf(GL_TEXTURE_ENV,  GL_TEXTURE_ENV_MODE, GL_DECAL);
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
glGenTextures(1,&texName);
glGenTextures(1,&texName2);


if(bitmap!= NULL){
glBindTexture(GL_TEXTURE_2D, texName);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NONE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NONE);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, biHeadBck.biWidth,biHeadBck.biHeight,0,GL_RGB, GL_UNSIGNED_BYTE, bitmap);

gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB, biHeadBck.biWidth,biHeadBck.biHeight,GL_RGB, GL_UNSIGNED_BYTE, bitmap);

glBindTexture(GL_TEXTURE_2D, texName);
}


glBindTexture(GL_TEXTURE_2D, texName2);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, biHeadTxt.biWidth,biHeadTxt.biHeight,0,GL_RGB, GL_UNSIGNED_BYTE, bitmap);



gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB, biHeadTxt.biWidth,biHeadTxt.biHeight,GL_RGB, GL_UNSIGNED_BYTE, texture);


glBindTexture(GL_TEXTURE_2D, texName3);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, hlpHead.biWidth,hlpHead.biHeight,0,GL_RGB, GL_UNSIGNED_BYTE, hlpBmp);
gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB, hlpHead.biWidth,hlpHead.biHeight,GL_RGB, GL_UNSIGNED_BYTE, hlpBmp);


glBindTexture(GL_TEXTURE_2D, texName2);



//glEnable(GL_TEXTURE_2D);
}








void render(){
extern bool gamePaused;
extern menuButton gameMenuButtons[20];

glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
glLoadIdentity();
glMatrixMode(GL_PROJECTION);
//glPushMatrix();
glLoadIdentity();
//gluOrtho2D(MainBall.x-(.5*resWidth), MainBall.x+(.5*resWidth) , MainBall.y+(.5*resHeight) , MainBall.y-(.5*resHeight));
gluOrtho2D(0, MAPBARRIER,MAPBARRIER,0);



glViewport(0,0,resWidth,resHeight);

//draw background
if(bitmap!=NULL){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);
    }

if(gHelp == true){glBindTexture(GL_TEXTURE_2D,texName3);}

if(MAPBARRIER == NULL){MAPBARRIER = resWidth;}

glColor3f(0,0,0);
    glBegin(GL_QUADS);
    
    glTexCoord2f(0,1);
        glVertex2i(0,0);
    glTexCoord2f(1,1);
        glVertex2i(MAPBARRIER,0);
    glTexCoord2f(1,0);
        glVertex2i(MAPBARRIER,MAPBARRIER);
    glTexCoord2f(0,0);
        glVertex2i(0,MAPBARRIER);

    glEnd();
//glDisable(GL_TEXTURE_2D);
    
    if(gHelp){SwapBuffers(hDC);return;}


//glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texName2);
    ///////////////////////////

    
    drawGameObjects();

//glDisable(GL_TEXTURE_2D);
    




    glLoadIdentity();
    gluOrtho2D(0,resWidth,resHeight,0);
    

    if(!gamePaused){
//glLoadIdentity();
    glColor3f(.5,.5,.5);
//	glBegin(GL_QUADS);
    //	glVertex2i(0,0);
    //	glVertex2i(150,0);
    //	glVertex2i(150,35);
    //	glVertex2i(0,35);
    //glEnd();
    //glColor3f(1,.75,1);
    glColor3f(1,1,1);
    glRasterPos2i(15,20);
    switch(gameRound)
    {
    case 1:ShowText("Round 1");break;
    case 2:ShowText("Round 2");break;
    case 3:ShowText("Round 3");break;
    }
    
    char scorestring[1000];
    glColor3f(0,0,1);
    sprintf(scorestring,"%i",scores[BLUE]);
    glRasterPos2i(15,45);
    ShowText(scorestring);
    glColor3f(1,0,0);
    sprintf(scorestring,"%i",scores[RED]);
    glRasterPos2i(15,70);
    ShowText(scorestring);


    if(gameRound > 1)
    {
        extern int redsWon;

    glColor3f(1,1,1);

    glRasterPos2i(15,90);
    {extern int modifier;
    sprintf(scorestring, "You won %d out of 3 rounds",(gameRound-modifier-redsWon));
    }	
    

    ShowText(scorestring);
    
    }

    //sprintf(scorestring,"fps: %i",fps);
    //glRasterPos2i((resWidth-120),50);
    //ShowText(scorestring);

    }


extern HFONT font;
extern HFONT bigFont;

//use for menu and messages
SelectObject(hDC,bigFont);	


    
    
glLoadIdentity();
gluOrtho2D(0, resWidth,resHeight,0);

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texName2);


glColor3f(.5,.5,.5);

glBegin(GL_QUADS);	


for(int i = 0; i < 20; i++){

    if(gameMenuButtons[i].visible){
     glTexCoord2f(.5,.4);
        glVertex2i(gameMenuButtons[i].x,gameMenuButtons[i].y );
     glTexCoord2f(0,.4);
        glVertex2i(gameMenuButtons[i].x+gameMenuButtons[i].width,gameMenuButtons[i].y );
     glTexCoord2f(0,.6);
        glVertex2i(gameMenuButtons[i].x+gameMenuButtons[i].width,gameMenuButtons[i].y+gameMenuButtons[i].height );
     glTexCoord2f(.5,.6);
        glVertex2i(gameMenuButtons[i].x,gameMenuButtons[i].y+gameMenuButtons[i].height);
    
    }

}

//go back to regular font;
glEnd();
glDisable(GL_TEXTURE_2D);


glColor3f(.5,.5,.7);

if(!gamePaused){
extern message gMessage;
if(gMessage.active){
    glRasterPos2i(gMessage.x,gMessage.y);
    ShowText(gMessage.msg);
}}

glColor3f(0,.5,0);


for(int i = 0; i < 20; i++){
    if(gameMenuButtons[i].visible){
        if(gameMenuButtons[i].description != NULL){	
        glRasterPos2i(gameMenuButtons[i].x,gameMenuButtons[i].y + .5*(float)gameMenuButtons[i].height);
        ShowText(gameMenuButtons[i].description);
        }
    }
}


SelectObject(hDC, font);


//glDisable(GL_TEXTURE_2D);
SwapBuffers(hDC);

}










void ShowText(char* string){

extern unsigned int base;

extern HFONT bigFont;

wglUseFontBitmaps(hDC, 32, 96, base);
glPushAttrib(GL_LIST_BIT);
glListBase(base-32);
glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);
glPopAttrib();
}










void drawObject(int x, int y, int width, int height){



    glBegin(GL_QUADS);	
    glTexCoord2f(uLeftX,uLeftY);
    
    glVertex2i(x-width,y-height);
    
    glTexCoord2f(uRightX,uRightY);
    
    glVertex2i(x+width,y-height);
    
    glTexCoord2f(lRightX,lRightY);
    
    glVertex2i(x+width,y+height);
    
    glTexCoord2f(lLeftX,lLeftY);
    
    glVertex2i(x-width,y+height);
glEnd();
glColor3f(1,1,1);



}




void drawGameObjects(){

extern particle particles[25];
extern double rTime;
static float essencescroll = 0.0;
extern bool gamePaused;
if(gamePaused == true){return;}


essencescroll = essencescroll + .01*rTime;

//if(essencescroll > .15){essencescroll = 0;}



glColor3f(1,1,1);


//texture coordinates adjusted per object
uLeftX = 0;
uLeftY = .6;
uRightX = .5;
uRightY = .6;
lRightX = .5;
lRightY =.4;
lLeftX = 0;
lLeftY = .4;
    

for(int i = 0; i <3000;i++){
    glColor3f(1,1,1);
    if(blocks[i].round){
        if(blocks[i].round == gameRound || blocks[i].round == 4){
            if(blocks[i].broken == false){
                drawObject(blocks[i].x, blocks[i].y, blocks[i].width, blocks[i].height);
            }
        }
    }
}
    
//texture coordinates adjusted per object
uLeftX = .5;
uLeftY = .6;
uRightX = 1;
uRightY = .6;
lRightX = 1;
lRightY =.4;
lLeftX = .5;
lLeftY = .4;

    
for(int i = 0; i <3000;i++)
{
    glColor3f(.5,.5,.5);
    if(bricks[i].round == gameRound || bricks[i].round == 4)
    {
        drawObject(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height);
    }
}

float ANG = THIRTYDEGREES;

float ballcolorcoord = 0;

for(int i = 0; i <500;i++)
{
    if(balls[i].round == gameRound || balls[i].round == 4)
    {
        switch(balls[i].belongsTo)
        {
            case RED: glColor3f(1,0,0);ballcolorcoord = .625; break;
            case BLUE : glColor3f(0,0,1);ballcolorcoord = .375;break;
            default : glColor3f(1,1,1);ballcolorcoord = .125;break;
        }
        glPushMatrix();
        glTranslatef(balls[i].x,balls[i].y,0.0f);
        glBegin(GL_POLYGON);
            for (int j = 0; j <12; j++){
                glTexCoord2f((ballcolorcoord)+.125*cos(ANG), (1-.1)-.1*sin(ANG));
                glVertex2i(balls[i].radius*cos(ANG), balls[i].radius*sin(ANG));
                ANG = ANG+THIRTYDEGREES;
            }
        glEnd();
        glPopMatrix();
    }

}

if(MainBall.round == gameRound || MainBall.round == 4){
//drawObject(balls[i].x,balls[i].y,BALLSIZE,BALLSIZE);
switch(MainBall.belongsTo){
    case RED: glColor3f(1,0,0);ballcolorcoord = .625; break;
    case BLUE : glColor3f(0,0,1);ballcolorcoord = .375;break;
    default : glColor3f(1,1,1);ballcolorcoord = .125;break;
}

        glPushMatrix();
        glTranslatef(MainBall.x,MainBall.y,0);
        glBegin(GL_POLYGON);
            for (int j = 0; j <12; j++){
                glTexCoord2f((ballcolorcoord)+.125*cos(ANG), (1-.1)-.1*sin(ANG));
                glVertex2i(MainBall.radius*cos(ANG), MainBall.radius*sin(ANG));
                ANG = ANG+THIRTYDEGREES;
            }
        glEnd();
        glPopMatrix();

}


glColor3f(1,0,0);
for(int i = 0; i < 3000; i++){
    if(redessences[i].round){
        if(redessences[i].round == gameRound || redessences[i].round == 4){
        glPushMatrix();
        glTranslatef(redessences[i].x,redessences[i].y,0);
        glBegin(GL_POLYGON);
            for (int j = 0; j <12; j++){
                glTexCoord2f(essencescroll+.75+.1*cos(ANG), .7+.1*sin(ANG));
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
                glTexCoord2f(essencescroll+.25+.1*cos(ANG), .3+.1*sin(ANG));		
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
                glTexCoord2f((.875)+.125*cos(ANG), (1-.1)-.1*sin(ANG));
                glVertex2i(bouncers[i].radius*cos(ANG), bouncers[i].radius*sin(ANG));
                ANG = ANG+THIRTYDEGREES;
            }
        glEnd();
        glPopMatrix();
        }
    }
}

//glEnable(GL_TEXTURE_2D);

//texture coordinates adjusted per object
uLeftX = 0;
uLeftY = .2;
uRightX = .5;
uRightY = .2;
lRightX = .5;
lRightY =0;
lLeftX = 0;
lLeftY = 0;



if(redpaddle.x){
    glColor3f(1,0,0);
    drawObject(redpaddle.x,redpaddle.y,PADDLEWIDTH,PADDLEHEIGHT);}



//texture coordinates adjusted per object
uLeftX = .5;
uLeftY = .2;
uRightX = 1;
uRightY = .2;
lRightX = 1;
lRightY =0;
lLeftX = .5;
lLeftY = 0;


if(bluepaddle.x){
    glColor3f(0,0,1);
    drawObject(bluepaddle.x,bluepaddle.y,PADDLEWIDTH,PADDLEHEIGHT);}

glDisable(GL_TEXTURE_2D);
char temps[100];

extern score scorenums[25];
for ( int i = 0; i < 25; i ++)
{
    if(scorenums[i].active == true)
    {
        if(scorenums[i].color == RED)
        {
            glColor3f(1,0,0);
        }
        else
        {
            glColor3f(0,0,1);
        }

        sprintf(temps,"+%i",scorenums[i].value);

        glRasterPos2i(scorenums[i].x,scorenums[i].y);
        ShowText(temps);
    }
}



glBegin(GL_POINTS);
for( int i = 0; i < 25; i++)
{
    if(particles[i].active == true)
    {
        for(int j = 0; j < 10; j++)
        {
            glColor3f(particles[i].colors[j][0],particles[i].colors[j][1],particles[i].colors[j][2]);
            glVertex2i(particles[i].parts[j][0], particles[i].parts[j][1]);
        }
    }
}
glEnd();



}



