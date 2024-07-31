#include <stdio.h>
#include <stdlib.h>
#include <commdlg.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR  CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR  CALLBACK DlgProcGoTo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR  CALLBACK DlgProcOpt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR  CALLBACK DlgProcObject(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MiniMapProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


#define DEFAULT 1000

#define RED 0
#define BLUE 1
#define GREEN 2
#define WHITE 3

#define ALL 4
#define BALLSIZE 8

#define PADDLEWIDTH 25
#define PADDLEHEIGHT 8
#define BLOCKWIDTH 20
#define BLOCKHEIGHT 10
#define GOALWIDTH 30
#define GOALHEIGHT 20
#define ESSENCERADIUS 20
#define BOUNCERRADIUS 20
#define THIRTYDEGREES (30*3.14159)/180
#define BOUNCEVECTOR 1
#define DEFAULTHITS 1

void open2();
void roundcoordinate();
void ShowText(char* string);
void about();
void toomany();
void newMap();
void quit();
void help();
void grid();
void minimap();
void drawGameObjects();
void mapoptions();
void goTo();
void open();
void save();
void saveas();
void rightclick();
void glsetup();
void drawObject(int x, int y, int width, int height);
void render();



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
