#include <stdio.h>
#include <stdlib.h>

#include <gl/gl.h>
#include <gl/glu.h>

#include <cmath>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define DEFAULT 1000
#define MINUPV 10
#define RED 0
#define BLUE 1
//#define GREEN 2
#define WHITE 3
#define NUMBALLS 9
#define PART_SIZE 5

//#define ALL 4
//#define BALLSIZE 8
#define BALLSIZE 8
#define PADDLEWIDTH 40
#define PADDLEHEIGHT 8
#define BLOCKWIDTH 20
#define BLOCKHEIGHT 10
#define GOALWIDTH 30
#define GOALHEIGHT 20
#define ESSENCERADIUS 20
#define BOUNCERRADIUS 20
#define THIRTYDEGREES .5236 //(30*3.14159)/180
#define BOUNCEVECTOR 1
#define DEFAULTHITS 1
#define PADDLEINCREASE 2

#define TOPSIDE 1
#define BOTTOMSIDE 2
#define LEFTSIDE 3
#define RIGHTSIDE 4
#define NONE 0
#define BUFFERDIST 2
#define MAXBALLSPEED 90
#define MINBALLSPEED 40
#define SPEED MAXBALLSPEED

#define NEWGAME 0
#define QUIT 1
#define OPTIONS 2
#define HELP 3
#define HIGHSCORES 4

struct particle{
double vtimecreated;
bool active;
int parts[10][2];
float colors[10][3];
};

struct score{
int value;
float x;
int y;
int color;
double vtimecreated;
bool active;
};



struct message{
char msg[100];
int x;
int y;
bool active;
};

struct menuButton{
int x;
int y;
int width;
int height;
char description[100]; //text the button will show
bool visible; //is it visible?
void (*pf)();  //pointer to the function that will be called when the button is clicked
};

struct goal{
int color;
int width;
int height;
int x;
int round;
int y;
};

struct brick{
bool breakable;
bool broken;
int x;
int y;
int width;
int round;
int height;
};

struct bouncer{
	int x;
	int y;
	int radius;
	int round;
	int multiplier;
};

struct essence{
	int x;
	int y;
	int color;
	int radius;
	int round;
	};

struct paddle{
	int x;
	int y;
	int color;
	int width;
	int height;
};

struct ball{
	float x;
	float y;
	float lx;
	float ly;
	float yVec;
	float xVec;
	int belongsTo;
	int mountedColor;
	int round;
	int radius;
	int angle;
	int speed;
};




void gameQuit();
void gameOptions();
void setupGame();
void UpdateGame();
void ShowText(char* string);
void quit();
void drawGameObjects();
void openfile();
void readFile(char *a);
void glsetup();
void drawObject(int x, int y, int width, int height);
void render();
void CallMenu();
paddle doai(paddle tPaddle);
ball circlecollision(ball tBall, int circlex, int circley, int circleradius, int pcolor);
ball objectCollision(ball tBall, float px, float py, float pwidth, float pheight);
ball doCollision(ball tBall);
void followballs();
void calcDistance(ball cBall, ball tBall);
ball ballpaddlecollision(ball tBall, paddle testPaddle, ball PaddleBall, paddle lastpad);
unsigned char *LoadBMP(char *filestring);
void makeParticle(int x, int y);
void makeScore(int x, int y, int color, int value);
void mNewGame();
void gameHelp();