#include <stdio.h>
#include <stdlib.h>
#include <commdlg.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR  CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR  CALLBACK DlgProcGoTo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR  CALLBACK DlgProcOpt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR  CALLBACK DlgProcObject(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MiniMapProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

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

#include <BongGameObjects.h>
#include <BongMapLegacy.h>

struct SelectedObjectState
{
    goal* selectedgoal = NULL;
    brick* selectedbrick = NULL;
    paddle* selectedpaddle = NULL;
    bouncer* selectedbouncer = NULL;
    essence* selectedessence = NULL;
    ball* selectedball = NULL;

    SelectedObjectState() {}
    SelectedObjectState(goal& igoal) : selectedgoal(&igoal) {}
    SelectedObjectState(brick& ibrick) : selectedbrick(&ibrick) {}
    SelectedObjectState(paddle& ipaddle) : selectedpaddle(&ipaddle) {}
    SelectedObjectState(bouncer& ibouncer) : selectedbouncer(&ibouncer) {}
    SelectedObjectState(essence& iessence) : selectedessence(&iessence) {}
    SelectedObjectState(ball& iball) : selectedball(&iball) {}
};

void placeObject(BongMapLegacy& mapData, int object, int xClick, int yClick);

