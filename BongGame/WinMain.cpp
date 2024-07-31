/**************************************************************
**BONG														 **
**Game and EditorCode by and copyright 2006 Christopher Pugh **
***************************************************************/

#define fullscreen 1

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>
#include "bong.h"
#include "resource.h"
#include <time.h>

int redsWon;

score scorenums[25];
bool gHelp = false;
ball PaddleBall;
ball PaddleBallRed;
ball rPaddleBall[4];
ball bPaddleBall[4];
bool gamePaused = false;

GLfloat aTex = 0;
unsigned char* texture;
unsigned char* bitmap;
unsigned char* bitmap2;
unsigned char* dftBmp;
unsigned char* hlpBmp;
unsigned int ti = 2;
unsigned int iTexture;
BITMAPINFOHEADER hlpHead;
BITMAPINFOHEADER biHead;
BITMAPINFOHEADER biHeadBck;
BITMAPINFOHEADER biHeadTxt;
BITMAPINFOHEADER dftHead;

message gMessage;

int lastBroken = WHITE;
float moveamount;
int resWidth = 1024;
int resHeight = 768;

HWND hwnd;
HGLRC hRC;
HDC hDC;
unsigned int base;
HFONT font;
HFONT bigFont;
HINSTANCE hInstanceG;

bool started = false;

int cursorX, cursorY;

particle particles[25];
int scores[2];
goal redgoals[3000];
goal bluegoals[3000];
brick bricks[3000];
brick blocks[3000];
paddle redpaddle;
paddle bluepaddle;

paddle redpaddlelast;
paddle bluepaddlelast;

bouncer bouncers[3000];
essence redessences[3000];
essence blueessences[3000];
ball balls[500];
ball MainBall;
int MAPBARRIER = 0;
int gameRound = 1;
char imgString[100];
char musString[100];

menuButton gameMenuButtons[20];


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    static PIXELFORMATDESCRIPTOR pfd = {
                  sizeof(PIXELFORMATDESCRIPTOR),
                  1, //version
                  PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,
                  32,//colormode
                  0,0,0,0,0,0,//colorbits
                  0,//alpha buffer
                  0,//shift bit
                  0,//accum buffer
                  0,0,0,0,//accum bits
                  16,//zbuffer size
                  0,//stencil
                  0,//aux
                  PFD_MAIN_PLANE,//main drawing plane
                  0,//reserved
                  0,0,0//layer masks
    };

    switch (message) {

    case WM_CREATE:

        hDC = GetDC(hwnd);
        SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
        hRC = wglCreateContext(hDC);
        wglMakeCurrent(hDC, hRC);

        glsetup();

        base = glGenLists(96);
        bigFont = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Snap ITC");
        font = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Snap ITC");
        SelectObject(hDC, font);
        wglUseFontBitmaps(hDC, 32, 96, base);

        return 0;


    case WM_MOUSEMOVE:
        extern bool passed;
        cursorX = LOWORD(lParam);
        cursorY = HIWORD(lParam);



        if (gamePaused) { return 0; }

        moveamount = MAPBARRIER * ((float)LOWORD(lParam) / (float)resWidth);
        PaddleBall.xVec = moveamount - PaddleBall.x;//PaddleBall.x - PaddleBall.lx;
        PaddleBall.yVec = 0; //PaddleBall.y - PaddleBall.ly;
        PaddleBall.radius = bluepaddle.height;
        PaddleBall.belongsTo = WHITE;

        //SetCursorPos(0,0);
        return 0;

    case WM_LBUTTONDOWN:

        if (gHelp)
        {
            gameHelp();
        }

        if (!gamePaused)
        {
            started = true;
        }
        else
        {

            for (int i = 0; i < 20; i++) {
                if (gameMenuButtons[i].visible) {
                    if (gameMenuButtons[i].pf != NULL) {
                        if (cursorX > gameMenuButtons[i].x && cursorX < gameMenuButtons[i].width + gameMenuButtons[i].x) {
                            if (cursorY > gameMenuButtons[i].y && cursorY < gameMenuButtons[i].y + gameMenuButtons[i].height) {
                                gameMenuButtons[i].pf();
                            }
                        }
                    }
                }
            }
        }

        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:

            if (gHelp) {
                gameHelp();
            }

            if (bluepaddle.x != NULL)
            {
                CallMenu();
            }

            break;
        }
        break;

    case WM_DESTROY:
        //ReleaseCapture();
        wglMakeCurrent(hDC, hRC);
        wglDeleteContext(hRC);
        UnregisterClass("BongEditor", hInstanceG);
        PostQuitMessage(0);

        return 0;

    case WM_SIZE:
        resHeight = HIWORD(lParam);
        resWidth = LOWORD(lParam);
        return 0;

    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    int i, j;
    DWORD dwMode;

    MSG msg;
    WNDCLASS wndclass1;

    wndclass1.style = CS_HREDRAW | CS_VREDRAW;
    wndclass1.lpfnWndProc = WndProc;
    wndclass1.cbClsExtra = 0;
    wndclass1.cbWndExtra = 0;
    wndclass1.hInstance = hInstance;
    wndclass1.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wndclass1.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
    wndclass1.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass1.lpszMenuName = "BongEditor";
    wndclass1.lpszClassName = "BongEditor";
    RegisterClass(&wndclass1);


    DEVMODE devmode;
    memset(&devmode, 0, sizeof(devmode));
    devmode.dmSize = sizeof(devmode);
    devmode.dmPelsHeight = resHeight;
    devmode.dmPelsWidth = resWidth;
    devmode.dmBitsPerPel = 32;
    devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

    if (fullscreen) { dwMode = WS_POPUP | WS_EX_TOPMOST; }
    else { dwMode = WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST; }


    hwnd = CreateWindow("BongEditor", //window class name
        "Bong",//caption
        dwMode,
        0, //x position
        0, //y position
        resWidth, //x size
        resHeight, //y size
        NULL, //parent handle
        NULL, //menu handle
        hInstance, //instance
        NULL); //creation paramaters


    //SetCapture(hwnd);

    if (fullscreen) {
        ChangeDisplaySettings(&devmode, CDS_FULLSCREEN);
    }


    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);


    srand(time(0));

    for (i = 0; i < 25; i++) {
        for (j = 0; j < 10; j++) {
            particles[i].colors[j][0] = ((float)(rand() % 10)) / 10;
            particles[i].colors[j][1] = ((float)(rand() % 10)) / 10;
            particles[i].colors[j][2] = ((float)(rand() % 10)) / 10;
        }
    }

    sprintf(&gameMenuButtons[HIGHSCORES].description[0], "  Top Scores");
    sprintf(&gameMenuButtons[HELP].description[0], "      Help");
    sprintf(&gameMenuButtons[OPTIONS].description[0], "    Options");
    sprintf(&gameMenuButtons[NEWGAME].description[0], "  New Game");
    sprintf(&gameMenuButtons[QUIT].description[0], "      Quit");


    gameMenuButtons[NEWGAME].height = ((float)100 / (float)1024) * resHeight;
    gameMenuButtons[OPTIONS].height = ((float)100 / (float)1024) * resHeight;
    gameMenuButtons[QUIT].height = ((float)100 / (float)1024) * resHeight;
    gameMenuButtons[HIGHSCORES].height = ((float)100 / (float)1024) * resHeight;
    gameMenuButtons[HELP].height = ((float)100 / (float)1024) * resHeight;


    gameMenuButtons[HELP].width = ((float)425 / (float)1280) * resWidth;
    gameMenuButtons[NEWGAME].width = ((float)425 / (float)1280) * resWidth;
    gameMenuButtons[OPTIONS].width = ((float)425 / (float)1280) * resWidth;
    gameMenuButtons[QUIT].width = ((float)425 / (float)1280) * resWidth;
    gameMenuButtons[HIGHSCORES].width = ((float)425 / (float)1280) * resWidth;


    gameMenuButtons[NEWGAME].pf = mNewGame;
    gameMenuButtons[OPTIONS].pf = gameOptions;
    gameMenuButtons[QUIT].pf = gameQuit;
    gameMenuButtons[HIGHSCORES].pf = NULL;
    gameMenuButtons[HELP].pf = gameHelp;


    gameMenuButtons[OPTIONS].visible =
        gameMenuButtons[QUIT].visible =
        gameMenuButtons[NEWGAME].visible =
        gameMenuButtons[HIGHSCORES].visible =
        gameMenuButtons[HELP].visible = false;

    gameMenuButtons[NEWGAME].x = (resWidth / 2) - ((float).5 * (float)gameMenuButtons[NEWGAME].width);
    gameMenuButtons[OPTIONS].x = (resWidth / 2) - ((float).5 * (float)gameMenuButtons[NEWGAME].width);
    gameMenuButtons[QUIT].x = (resWidth / 2) - ((float).5 * (float)gameMenuButtons[NEWGAME].width);
    gameMenuButtons[HIGHSCORES].x = (resWidth / 2) - ((float).5 * (float)gameMenuButtons[NEWGAME].width);
    gameMenuButtons[HELP].x = (resWidth / 2) - ((float).5 * (float)gameMenuButtons[NEWGAME].width);

    gameMenuButtons[NEWGAME].y = .145 * resHeight;//145;
    gameMenuButtons[OPTIONS].y = .32 * resHeight;//320;
    gameMenuButtons[HIGHSCORES].y = .495 * resHeight;//495;
    gameMenuButtons[HELP].y = .67 * resHeight;//670;
    gameMenuButtons[QUIT].y = .845 * resHeight;//845;


    ///////////////////////
    bitmap = dftBmp = LoadBMP("TitleScreen.bmp");

    if (bitmap != NULL)
    {
        dftHead = biHeadBck = biHead;
    }


    hlpBmp = LoadBMP("Help.bmp");
    hlpHead = biHead;

    texture =
        LoadBMP("template.bmp");
    biHeadTxt = biHead;

    glsetup();
    ShowCursor(FALSE);
    CallMenu();


    BOOL done = false;

    while (!done) // Loop That Runs Until done=TRUE

    {
        UpdateGame();
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // Is There A Message Waiting?
        {
            if (msg.message == WM_QUIT) // Have We Received A Quit Message?
            {
                done = TRUE;
            }
            else // If Not, Deal With Window Messages
            {
                TranslateMessage(&msg); // Translate The Message
                DispatchMessage(&msg); // Dispatch The Message
            }
        }
        else  // If There Are No Messages
        {
            ;

        }
    }


    return (int)msg.wParam;
}



void gameQuit() {
    wglMakeCurrent(hDC, hRC);
    wglDeleteContext(hRC);
    UnregisterClass("BongEditor", hInstanceG);
    PostQuitMessage(0);
}


